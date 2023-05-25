/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     USART	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
/*  Librarys Includes   */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Error_States.h"
/*  USART Includes  */
#include "USART_config.h"
#include "USART_private.h"
#include "USART_interface.h"

/*********Asynchronous Send********/
static void (*USART_FunctionPTR)(void) = NULLPTR;
static u8 *USART_pu8Reading = NULL;

static u8 USART_State = USART_IDLE;
/************************************/
static u8 USART_u8ISRSource;
/***********Buffer send*********/
volatile u8 *tx_buffer;
volatile u16 tx_buffer_size;
volatile u16 tx_buffer_index;
/*************************/
volatile u8 *rx_buffer;
volatile u16 rx_buffer_size;
volatile u16 rx_buffer_index;
static void (*rx_function_ptr)(void) = NULLPTR;

ES_t USART_Init(USART_t *Copy_USART){
    ES_t Local_enuErrorstate = ES_NOK;
    if(NULLPTR == Copy_USART){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
    u8 Local_u8Value=0;

    /*  Normal Speed    */
    CLR_BIT(UCSRA,UCSRA_U2X);
	CLR_BIT(UCSRA,UCSRA_MPCM);

	SET_BIT(Local_u8Value,UCSRC_URSEL);  //Choose UCSRC Reg

    if(Copy_USART->USART_Synchronization == USART_ASYNCH){
        CLR_BIT(Local_u8Value,UCSRC_UMSEL);     //Asynch
    }
    else if(Copy_USART->USART_Synchronization == USART_SYNCH){
        SET_BIT(Local_u8Value,UCSRC_UMSEL);     //Synch
    }

    /*      Choose Parity Mode      */
    if(Copy_USART->USART_Parity == USART_NOPARITY){
    CLR_BIT(Local_u8Value,UCSRC_UPM1);
    CLR_BIT(Local_u8Value,UCSRC_UPM0);
    }
    else if(Copy_USART->USART_Parity == USART_EVEN_PARITY){
    SET_BIT(Local_u8Value,UCSRC_UPM1);
    CLR_BIT(Local_u8Value,UCSRC_UPM0);
    }
    else if(Copy_USART->USART_Parity == USART_ODD_PARITY){
    SET_BIT(Local_u8Value,UCSRC_UPM1);
    SET_BIT(Local_u8Value,UCSRC_UPM0);
    }

    /*      Choose Stop Bits        */
    if(Copy_USART->USART_StopBits == USART_1STOPBITS){
    CLR_BIT(Local_u8Value,UCSRC_USBS);
    }
    else if(Copy_USART->USART_StopBits == USART_2STOPBITS){
    SET_BIT(Local_u8Value,UCSRC_USBS);
    }
    /*      Choose 8 Bit Data       */
    SET_BIT(Local_u8Value,UCSRC_UCSZ1);
	SET_BIT(Local_u8Value,UCSRC_UCSZ0);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
    UCSRC =Local_u8Value;
	SET_BIT(UCSRB,UCSRB_TXEN);    //transmitter enable
	SET_BIT(UCSRB,UCSRB_RXEN);    //receiver   enable

    /*      Choose BaudRate     */
    u16 ubrr_value = ( F_CPU / (16*Copy_USART->USART_BaudRate)) - 1;
    UBRRL = (u8) ubrr_value;
    UBRRH = (u8) (ubrr_value >> 8);
    Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}
ES_t USART_SendCharSynch(u8 Copy_u8Value){
    ES_t Local_enuErrorstate = ES_NOK;
    if(USART_State == USART_BUSY){
        Local_enuErrorstate = ES_BUSY_FUNCTION;
    }
    else{
        USART_State = USART_BUSY;
        u32 Local_u32Counter =0;
        while((GET_BIT(UCSRA,UCSRA_UDRE) == 0) && Local_u32Counter != USART_TIMEOUT){
            Local_u32Counter++;
        }
        if(Local_u32Counter == USART_TIMEOUT){
            //Loop is broken because of Time out
            Local_enuErrorstate = ES_TIMEOUT;
        }else{
            USART_State = USART_IDLE;
            UDR = Copy_u8Value;
            Local_enuErrorstate = ES_OK;
        }
    }
    return Local_enuErrorstate;
}

ES_t USART_SendBufferSynch(u8* Copy_pu8Buffer, u8 Copy_u8BufferSize){
    ES_t Local_enuErrorstate = ES_NOK;
    if(NULLPTR == Copy_pu8Buffer){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
        u8 Local_u8Index = 0;
        USART_State = USART_BUSY;
        while(Local_u8Index < Copy_u8BufferSize){
            u32 Local_u32Counter = 0;
            while((GET_BIT(UCSRA,UCSRA_UDRE) == 0) && (Local_u32Counter != USART_TIMEOUT)){
                Local_u32Counter++;
            }
            if(Local_u32Counter == USART_TIMEOUT){
                //Loop is broken because of Time out
                Local_enuErrorstate = ES_TIMEOUT;
                USART_State = USART_IDLE;
                break;
            }
            UDR = Copy_pu8Buffer[Local_u8Index];
            Local_u8Index++;
        }
        if(Local_u8Index == Copy_u8BufferSize){
            USART_State = USART_IDLE;
            Local_enuErrorstate = ES_OK;
        }
    }
    return Local_enuErrorstate;
}


ES_t USART_SendCharASynch(u8 *Copy_pu8Reading, void(*LocalPtr)(void)){
    ES_t Local_enuErrorstate = ES_NOK;
    if(NULLPTR == Copy_pu8Reading || NULLPTR == LocalPtr){
        Local_enuErrorstate =ES_NULL_POINTER;
    }
    else{
        if(USART_State == USART_BUSY){
            Local_enuErrorstate = ES_BUSY_FUNCTION;
        }else{
            USART_u8ISRSource = SINGLE_CHAR_SEND;
            USART_State = USART_BUSY;
            USART_pu8Reading = Copy_pu8Reading;
            USART_FunctionPTR = LocalPtr;
            /*  Enable UDRE Interrupt   */
            SET_BIT(UCSRB,UCSRB_UDRIE);
            Local_enuErrorstate = ES_OK;
        }
    }
    return Local_enuErrorstate;
}

ES_t USART_SendBufferAsynch(u8* Copy_pu8Buffer, u8 Copy_u8BufferSize){
    ES_t Local_enuErrorstate = ES_NOK;
    if(NULLPTR == Copy_pu8Buffer){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
        if(USART_State == USART_BUSY){
            Local_enuErrorstate = ES_BUSY_FUNCTION;
        }
        else{
            USART_u8ISRSource = BUFFER_SEND;
            tx_buffer = Copy_pu8Buffer;
            tx_buffer_size = Copy_u8BufferSize;
            tx_buffer_index = 0;
            /*  Enable UDRE Interrupt   */
            SET_BIT(UCSRB,UCSRB_UDRIE);
        }
    }
    return Local_enuErrorstate;
}


ES_t USART_ReceiveCharSynch(u8 *pu8Data){
    ES_t Local_enuErrorstate = ES_NOK;
    if (pu8Data == NULLPTR) {
        Local_enuErrorstate = ES_NULL_POINTER;
    } else {
        USART_State = USART_BUSY;
        u32 Local_u32Counter = 0;
        while ((GET_BIT(UCSRA, UCSRA_RXC) == 0) && (Local_u32Counter != USART_TIMEOUT)) {
            Local_u32Counter++;
        }
        if (Local_u32Counter == USART_TIMEOUT) {
            Local_enuErrorstate = ES_TIMEOUT;
        } else {
            USART_State = USART_IDLE;
            *pu8Data = UDR;
            Local_enuErrorstate = ES_OK;
        }
    }
    return Local_enuErrorstate;
}

ES_t USART_ReceiveCharASynch(u8 *Copy_pu8Reading, void(*LocalPtr)(void)){
    ES_t Local_enuErrorstate = ES_NOK;
    if(NULLPTR == Copy_pu8Reading || NULLPTR == LocalPtr){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
        if(USART_State == USART_BUSY){
            Local_enuErrorstate = ES_BUSY_FUNCTION;
        }else{
            USART_u8ISRSource = SINGLE_CHAR_RECEIVE;
            USART_State = USART_BUSY;
            USART_pu8Reading = Copy_pu8Reading;
            USART_FunctionPTR = LocalPtr;
            /*  Enable RXC Interrupt   */
            SET_BIT(UCSRB,UCSRB_RXCIE);
            Local_enuErrorstate = ES_OK;
        }
    }
    return Local_enuErrorstate;
}

ES_t USART_ReceiveBufferSynch(u8* Copy_pu8Buffer, u16 Copy_u16Length){
    ES_t Local_enuErrorstate = ES_NOK;
    if(NULLPTR == Copy_pu8Buffer){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
        for(u16 Local_u16Counter =0; Local_u16Counter < Copy_u16Length; Local_u16Counter++){
            u32 Local_u32TimeoutCounter =0;
            while((GET_BIT(UCSRA,UCSRA_RXC) == 0) && Local_u32TimeoutCounter != USART_TIMEOUT){
                Local_u32TimeoutCounter++;
            }
            if(Local_u32TimeoutCounter == USART_TIMEOUT){
                Local_enuErrorstate = ES_TIMEOUT;
                break;
            }
            else{
                *(Copy_pu8Buffer+Local_u16Counter) = UDR;
                Local_enuErrorstate = ES_OK;
            }
        }
    }
    return Local_enuErrorstate;
}


ES_t USART_ReceiveBufferASynch(u8 *buffer, u8 size, void(*LocalPtr)(void)){
    ES_t Local_enuErrorstate = ES_NOK;
    if(NULLPTR == buffer || NULLPTR == LocalPtr){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
        if(USART_State == USART_BUSY){
            Local_enuErrorstate = ES_BUSY_FUNCTION;
        }
        else{
            USART_u8ISRSource = BUFFER_RECEIVE;
            rx_buffer = buffer;
            rx_buffer_size = size;
            rx_buffer_index = 0;
            rx_function_ptr = LocalPtr;
            /*  Enable RXC Interrupt   */
            SET_BIT(UCSRB,UCSRB_RXCIE);
            Local_enuErrorstate = ES_OK;
        }
    }
    return Local_enuErrorstate;
}





ISR(__vector_14){
    if(USART_u8ISRSource == SINGLE_CHAR_SEND){
        if(*USART_pu8Reading != '\0'){
            UDR = *USART_pu8Reading;

            if(NULLPTR != USART_FunctionPTR){
                USART_FunctionPTR();
            }
            /*  Disable Interrupt   */
            CLR_BIT(UCSRB,UCSRB_UDRIE);
        }
        else{
            USART_State = USART_IDLE;
        }
    }
    else if(USART_u8ISRSource == BUFFER_SEND){
        if(tx_buffer_index < tx_buffer_size){
            UDR = *(tx_buffer+tx_buffer_index);
            tx_buffer_index++;
        }
        else{
            /*  Enable UDRE Interrupt   */
            SET_BIT(UCSRB,UCSRB_UDRIE);
        }
    }
}

ISR(__vector_13){
    if(USART_u8ISRSource == SINGLE_CHAR_RECEIVE){
        *USART_pu8Reading = UDR;

        if(NULLPTR != USART_FunctionPTR){
            USART_FunctionPTR();
        }
        USART_State = USART_IDLE;
        /*  Disable Interrupt   */
        CLR_BIT(UCSRB,UCSRB_RXCIE);
    }
    else if(USART_u8ISRSource == BUFFER_RECEIVE){
        *(rx_buffer + rx_buffer_index) = UDR;
        rx_buffer_index++;

        if(rx_buffer_index == rx_buffer_size){
            if(NULLPTR != rx_function_ptr){
                rx_function_ptr();
            }
            USART_State = USART_IDLE;
            /*  Disable Interrupt   */
            CLR_BIT(UCSRB,UCSRB_RXCIE);
        }
    }
}
