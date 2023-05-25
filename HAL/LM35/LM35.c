/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   HAL			      ***************************/
/*************                SWC :     LM35	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/

/*  MCAL Includies  */
#include "../../MCAL/ADC/ADC_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "LM35.h"

ES_t LM35_ReadTempSynch(u8 Copy_u8Channel,u16 *Copy_Reading){
    ES_t Local_enuErrorstate = ES_NOK;
    if(NULLPTR == Copy_Reading){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
    u16 ADC_Result;
    /*      Get Reading    */
    ADC_StartConversionSynch(Copy_u8Channel,&ADC_Result);
    /*  Convert ADC to Voltage  */
    #if (REF_VOLT == AVCC || REF_VOLT == AREF) && DATAREG == LEFT_ADJUST
    *Copy_Reading=(ADC_Result * 5 * 100) / (256 * 1);
	#elif (REF_VOLT == AVCC || REF_VOLT == AREF) && DATAREG == RIGHT_ADJUST
    *Copy_Reading=(ADC_Result * 5 * 100) / (1024 * 1);
    #elif REF_VOLT == INTERNAL_256	&& DATAREG == LEFT_ADJUST
    *Copy_Reading=(ADC_Result * 2.56 * 100) / (256 * 1);
	#elif REF_VOLT == INTERNAL_256	&& DATAREG == RIGHT_ADJUST
    *Copy_Reading=(ADC_Result * 2.56 * 100) / (1024 * 1);
    #endif
    Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}

ES_t LM35_ReadTempASynch(u8 Copy_u8Channel,u16 *Copy_Reading,void(*LocalPtr)(void)){
    ES_t Local_enuErrorstate = ES_NOK;
    if(NULLPTR == Copy_Reading){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
    u16 ADC_Result;
    /*      Get Reading    */
    ADC_StartConversionASynch(Copy_u8Channel,&ADC_Result,LocalPtr); // No Notification Function
    /*  Convert ADC to Voltage  */
    #if (REF_VOLT == AVCC || REF_VOLT == AREF) && DATAREG == LEFT_ADJUST
    *Copy_Reading=(ADC_Result * 5 * 100) / (256 * 1);
	#elif (REF_VOLT == AVCC || REF_VOLT == AREF) && DATAREG == RIGHT_ADJUST
    *Copy_Reading=(ADC_Result * 5 * 100) / (1024 * 1);
    #elif REF_VOLT == INTERNAL_256	&& DATAREG == LEFT_ADJUST
    *Copy_Reading=(ADC_Result * 2.56 * 100) / (256 * 1);
	#elif REF_VOLT == INTERNAL_256	&& DATAREG == RIGHT_ADJUST
    *Copy_Reading=(ADC_Result * 2.56 * 100) / (1024 * 1);
    #endif
    Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}
