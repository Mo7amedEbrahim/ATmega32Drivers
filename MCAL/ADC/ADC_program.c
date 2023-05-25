/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     ADC	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
/*  Librarys Includes   */
/*		LIB includes			*/


#include "../../LIB/BIT_MATH.h"
/*  ADC Files   */
#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_register.h"
#include "ADC_private.h"


/*          Global Variables        */
/*****************************************************/
/*               Single ASYNCH          */
/*  Pointer to function to use CallBack     */
static void (*ADC_FunctionPTR)(void) = NULLPTR;
/*  Global pointer to catch the reading */
static u16 *ADC_pu16Reading = NULLPTR;
/*****************************************************/
/*               Chain  ASYNCH          */
static volatile Chain_t *g_CurrentChain = NULL;
static u8 ADC_u8ChainIndex  = NULL;
/*****************************************************/
static u8 ADC_u8ISRSource;
static u8 ADC_State = IDLE;
/*****************************************************/


/******************APIs Implementation*******************/

/**
*@brief Initialize the ADC module
This function initializes the ADC module by choosing the reference voltage,
 the data register, and the prescaler.
 It also enables the ADC module.
*@return ES_t
ES_OK: The ADC module was successfully initialized
ES_NOK: An error occurred during initialization
*/
ES_t ADC_Init(void){
    ES_t Local_enuErrorstate = ES_NOK;
    /*      Choose Reference Voltage    */
    #if REF_VOLT == AREF
    ADC_VOLT_USE_AREF();
    #elif REF_VOLT == AVCC
    ADC_VOLT_USE_AVCC();
    #elif REF_VOLT == INTERNAL_256
    ADC_VOLT_USE_INTERNAL();
    #endif
    /*      Choose Data Register    */
    #if DATAREG == LEFT_ADJUST
    SET_BIT(ADMUX,ADMUX_ADLAR);
    #elif DATAREG == RIGHT_ADJUST
    CLR_BIT(ADMUX,ADMUX_ADLAR);
    #endif
    /*      Choose Prescaler        */
    ADC_MASK_PRESCALER();
    ADC_CHOOSE_PRESCALER();
    /*      Enable ADC      */
    ENABLE_ADC();
    Local_enuErrorstate = ES_OK;
    return Local_enuErrorstate;
}




/**
*@brief De-initialize the ADC module
This function de-initializes the ADC module by disabling it and its interrupt.
*@return ES_t
ES_OK: The ADC module was successfully de-initialized
ES_NOK: An error occurred during de-initialization
*/
ES_t ADC_DeInit(void){
    ES_t Local_enuErrorstate = ES_NOK;
    DISABLE_ADC();
    ADC_DISABLE_INTERRUPT();
    Local_enuErrorstate = ES_OK;
    return Local_enuErrorstate;
}




/**
*@brief Start synchronous ADC conversion
This function starts a synchronous ADC conversion on the specified channel 
and stores the result in the specified memory location.
*@param[in] Local_u8Channel: the channel to be converted
*@param[out] Copy_pu16Reading: a pointer to the memory location where the conversion result will be stored
*@return ES_t
ES_OK: The ADC conversion was successful
ES_NULL_POINTER: The pointer to the memory location where the conversion result will be stored is null
ES_BUSY_FUNCTION: The ADC module is busy
ES_TIMEOUT: The ADC conversion timed out
*/
ES_t ADC_StartConversionSynch(u8 Local_u8Channel, u16 *Copy_pu16Reading){
    ES_t Local_enuErrorstate = ES_NOK;
    if(ADC_State == IDLE){
        if(NULLPTR == Copy_pu16Reading){
            Local_enuErrorstate = ES_NULL_POINTER;
        }
        else{
            ADC_State = BUSY;
	        u32 Local_u32Counter=0;
            /*      Select Channel      */
            ADC_MASK_CHANNEL();
            ADC_CHOOSE_CHANNEL(Local_u8Channel);
            /*      Start Conversion    */
            ADC_START_CONVERSION();
            //Wait while finish Conversion
            while((ADC_READ_FLAG() == 0) && (Local_u32Counter != ADC_TIMEOUT)){
    	    Local_u32Counter++;
            }
            if(Local_u32Counter == ADC_TIMEOUT){
                //Loop is broken because of Time out
                Local_enuErrorstate = ES_TIMEOUT;
            }
            else{
                ADC_State = IDLE;
                //Loop is broken because of Conversion Complete
                //Clear Conversion Complete Flag
                ADC_CLEAR_FLAG();
                #if DATAREG == LEFT_ADJUST
    	        *Copy_pu16Reading = ADCH;
                #elif DATAREG == RIGHT_ADJUST
    	        //We must read ADCL before ADCH as mentioned in page 215 in DataSheet
    	        *Copy_pu16Reading = ADCL + ((u16)ADCH << 8);
                #endif
                Local_enuErrorstate = ES_OK;
            }
        }
    }
    else{
        Local_enuErrorstate = ES_BUSY_FUNCTION;
    }
    return Local_enuErrorstate;
}


ES_t ADC_StartConversionASynch(u8 Local_u8Channel, u16 *Copy_pu16Reading, void(*LocalPtr)(void)){
    ES_t Local_enuErrorstate = ES_NOK;
    if(ADC_State == IDLE){
        if(Copy_pu16Reading == NULLPTR){
            Local_enuErrorstate = ES_NULL_POINTER;
        }
        else{
            /*  ADC State is Busy   */
            ADC_State = BUSY;
            /*      ISR Source is Single channel     */
            ADC_u8ISRSource = SINGLE_CHANNEL_ASYNCH;
                /*Initialize the reading variable globally to read in ISR*/
            ADC_pu16Reading = Copy_pu16Reading;
                /*Initialize the Callback Notfication Function globally to read in ISR*/
            ADC_FunctionPTR = LocalPtr;
                /*      Select Channel      */
            ADC_MASK_CHANNEL();
            ADC_CHOOSE_CHANNEL(Local_u8Channel);
                /*      Start Conversion    */
            ADC_START_CONVERSION();
                /*      Enable Interrupt Feature    */
            ADC_ENABLE_INTERRUPT();
                /*Used in Chain Conversion*/
            ADC_u8ChainIndex = 0;
            Local_enuErrorstate = ES_OK;
        }
    }
    else{
        Local_enuErrorstate = ES_BUSY_FUNCTION;
    }
    return Local_enuErrorstate;
}

ES_t ADC_StartChainAsynch(Chain_t *Copy_Chain){
    ES_t Local_enuErrorstate = ES_NOK;
    if(Copy_Chain == NULLPTR){
        Local_enuErrorstate =ES_NULL_POINTER;
    }
    else{
        if(ADC_State == BUSY){
            Local_enuErrorstate = ES_BUSY_FUNCTION;
        }
        else{
            /*  ADC State is Busy   */
            ADC_State = BUSY;
            /*      ISR Source is Chain     */
            ADC_u8ISRSource = CHAIN_ASYNCH;
            /*Local to Global*/
            g_CurrentChain = Copy_Chain;
            ADC_u8ChainIndex = 0;
            /*  Enable Interrupt */
            ADC_ENABLE_INTERRUPT();
            /*  Set Required Channel*/
            ADC_MASK_CHANNEL();
            ADC_CHOOSE_CHANNEL(g_CurrentChain->Channel[ADC_u8ChainIndex]);
            ADC_START_CONVERSION();
            
            Local_enuErrorstate = ES_OK;
        }
    }
    return Local_enuErrorstate;
}



ISR(__vector_16){
    if(ADC_u8ISRSource == SINGLE_CHANNEL_ASYNCH){
    /*  Read ADC Result     */
        #if DATAREG == LEFT_ADJUST
    	*ADC_pu16Reading = ADCH;
        #elif DATAREG == RIGHT_ADJUST
    	//We must read ADCL before ADCH as mentioned in page 215 in DataSheet
    	*ADC_pu16Reading = ADCL + ((u16)ADCH << 8);
        #endif
        /*  ADC Is IDLE */
        ADC_State = IDLE;
    /*  Invoke CallBack Notification Function   */
        ADC_FunctionPTR();
    /*  Disable Interrupt    */
        ADC_DISABLE_INTERRUPT();
    }
    else if(ADC_u8ISRSource == CHAIN_ASYNCH){
        /*  Read ADC Result     */
        #if DATAREG == LEFT_ADJUST
        g_CurrentChain->Result[ADC_u8ChainIndex] = ADCH;
        #elif DATAREG == RIGHT_ADJUST
    	//We must read ADCL before ADCH as mentioned in page 215 in DataSheet
        g_CurrentChain->Result[ADC_u8ChainIndex] = ADCL + ((u16)ADCH << 8);
        #endif
        /*  Increment Chain Index   */
        ADC_u8ChainIndex++;
        /*      Check if the chain finished or not      */
        if(ADC_u8ChainIndex >= g_CurrentChain->Size){
            /*      Chain is finished       */
            ADC_State = IDLE;
            /*  Disable Interrupt    */
            ADC_DISABLE_INTERRUPT();
            /*  Call Notification Function  */
            if(g_CurrentChain->NotifyFunction != NULL){
                g_CurrentChain->NotifyFunction();
            }
        }
        else{
            /*      Chain is not finished       */
            /*      Set the new Channel     */
            ADC_MASK_CHANNEL();
            ADC_CHOOSE_CHANNEL(g_CurrentChain->Channel[ADC_u8ChainIndex]);
            ADC_START_CONVERSION();
        }
    }
}
