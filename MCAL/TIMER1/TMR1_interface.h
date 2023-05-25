/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     TMR1	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _TMR1_CONFIG_H
#define _TMR1_CONFIG_H



typedef struct{
    u8 TIMER1_Mode;
    u8 TIMER1_Prescaler;
    u8 TIMER1_Channel;
}TMR1_t;

ES_t TMR1_Init(TMR1_t *Copy_Timer1);
ES_t TMR1_SetICR(u16 Copy_u16TOP);
ES_t TMR1_SetChannelACompMatch(u16 Copy_u16CompareMatch);
ES_t TMR1_OvfSetCallBack(TMR1_t *Copy_Timer1);
ES_t TMR1_CTCSetCallBack(TMR1_t *Copy_Timer1);
ES_t TMR1_SetDutyCycle(u8 Copy_u8DutyCycle);







#endif