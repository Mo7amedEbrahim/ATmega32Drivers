/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   RTOS_stack			      ***************************/
/*************                SWC :     TMR2	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
/*		Libraries Includes		*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Error_States.h"
/*      TMR2 Includes   */
#include "TMR2_interface.h"
#include "TMR2_private.h"
#include "TMR2_config.h"

static void (*TMR2_CTCCallbackFuncPTR)(void) = NULLPTR;

ES_t TMR2_init(u8 Copy_u8OCR2){
    //  Choose CTC Mode
    CLR_BIT(TCCR2,TCCR2_WGM20);
    SET_BIT(TCCR2,TCCR2_WGM20);
    //Choose OCR2
    OCR2 = Copy_u8OCR2;
    // Choose Prescaler
    TMR2_CLK_MASK();
    TMR2_CLK_SELECT(TMR2_PRESCALER);
    //Enable CTC Interrupt
    SET_BIT(TIMSK,TIMSK_OCIE2);
    return ES_OK;
}

ES_t TMR2_CTCSetCallBack(void (*LocalFunc)(void)){
    ES_t Local_enuErrorstate = ES_NOK;
    if(LocalFunc == NULLPTR){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
        TMR2_CTCCallbackFuncPTR = LocalFunc;
        Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}

ISR(__vector_4){
    if(TMR2_CTCCallbackFuncPTR == NULLPTR){
        /*  Do Nothing  */
    }
    else{
    TMR2_CTCCallbackFuncPTR();
    }
}
