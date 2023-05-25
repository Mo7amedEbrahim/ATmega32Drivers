/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        **************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     TMR1	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
/*		LIB includes			*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Error_States.h"
/*		TMR1 files Includes		*/
#include "TMR1_interface.h"
#include "TMR1_config.h"
#include "TMR1_register.h"
#include "TMR1_private.h"
static void (*TMR1_OVFCallBackFunction)(void) = NULLPTR;
static void (*TMR1_CTCCallBackFunction)(void) = NULLPTR;

ES_t TMR1_Init(TMR1_t *Copy_Timer1){
    ES_t Local_enuErrorstate = ES_NOK;
    if(NULLPTR == Copy_Timer1){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
        /*  Choose Mode */
        TMR1_MODE_MASK();
        switch(Copy_Timer1 ->TIMER1_Mode){
            case TMR1_NORMAL_MODE:
                CLR_BIT(TCCR1A, TCCR1A_WGM10);
                CLR_BIT(TCCR1A, TCCR1A_WGM11);
                CLR_BIT(TCCR1B, TCCR1B_WGM12);
                CLR_BIT(TCCR1B, TCCR1B_WGM13);
                /* Enable overflow interrupt */
                SET_BIT(TIMSK, TIMSK_TOIE1);
                break;
            case TMR1_CTC_MODE:
                 /* Choose CTC mode */
                CLR_BIT(TCCR1A, TCCR1A_WGM10);
                CLR_BIT(TCCR1A, TCCR1A_WGM11);
                SET_BIT(TCCR1B, TCCR1B_WGM12);
                CLR_BIT(TCCR1B, TCCR1B_WGM13);
                /* Enable output compare match interrupt */
                SET_BIT(TIMSK, TIMSK_OCIE1A);
                /* Set the value of the Output Compare Register A */
                //OCR1A = Copy_Timer1->TMR1_OCR1A;
                break;
            case TMR1_FAST_PWM_ICR:
				/* Fast PWM Non Inverting */
				SET_BIT(TCCR1A,TCCR1A_COM1A1);
				CLR_BIT(TCCR1A,TCCR1A_COM1A0);
				/* Choose FAST PWM Mode */
				CLR_BIT(TCCR1A, TCCR1A_WGM10);
                SET_BIT(TCCR1A, TCCR1A_WGM11);
                SET_BIT(TCCR1B, TCCR1B_WGM12);
                SET_BIT(TCCR1B, TCCR1B_WGM13);
				
        }
        /*      Choose Clock source     */
        TMR1_CLK_MASK();
        TMR1_CLK_SELECT(Copy_Timer1->TIMER1_Prescaler);

    }
}

ES_t TMR1_SetICR(u16 Copy_u16TOP){
	ICR1 = Copy_u16TOP;
	return ES_OK;
}

ES_t TMR1_SetChannelACompMatch(u16 Copy_u16CompareMatch){
	OCR1A = Copy_u16CompareMatch;
	return ES_OK;
}
ES_t TMR1_OvfSetCallBack(TMR1_t *Copy_Timer1){
    ES_t Local_enuErrorstate = ES_NOK;
    if(NULLPTR == Copy_Timer1){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
        //TMR1_OVFCallBackFunction = Copy_Timer1->TMR1_ActionFunction;
        Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}

ES_t TMR1_CTCSetCallBack(TMR1_t *Copy_Timer1){
    ES_t Local_enuErrorstate = ES_NOK;
    if(NULLPTR == Copy_Timer1){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
       //TMR1_CTCCallBackFunction = Copy_Timer1->TMR1_ActionFunction;
        Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}





//OVF ISR
ISR(__vector_9){
    if(TMR1_OVFCallBackFunction == NULLPTR){
        /*  Do Nothing  */
    }
    else{
    TMR1_OVFCallBackFunction();
    }
}
//CTC ISR
ISR(__vector_7){
    if(TMR1_CTCCallBackFunction == NULLPTR){
        /*  Do Nothing  */
    }
    else{
    TMR1_CTCCallBackFunction();
    }
}



