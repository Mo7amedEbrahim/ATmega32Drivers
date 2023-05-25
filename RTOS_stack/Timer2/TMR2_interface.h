/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   RTOS_stack			      ***************************/
/*************                SWC :     TMR2	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _TMR2_INTERFACE_H_
#define _TMR2_INTERFACE_H_

#define TIMER2_NO_PRESCALER 0b001
#define TIMER2_PRESCALER_8 0b010
#define TIMER2_PRESCALER_32 0b011
#define TIMER2_PRESCALER_64 0b100
#define TIMER2_PRESCALER_128 0b101
#define TIMER2_PRESCALER_256 0b110
#define TIMER2_PRESCALER_1024 0b111

ES_t TMR2_init(u8 Copy_u8OCR2);
ES_t TMR2_CTCSetCallBack(void (*LocalFunc)(void));


#endif
