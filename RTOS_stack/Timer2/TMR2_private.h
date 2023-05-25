/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        **************************/
/*************                LAYER :   RTOS_stack			      ***********************/
/*************                SWC :     TMR2	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _TMR2_PRIVATE_H_
#define _TMR2_PRIVATE_H_


#define TCCR2               *((volatile u8 *)0x45)
#define TCCR2_CS20          0
#define TCCR2_CS21          1
#define TCCR2_CS22          2
#define TCCR2_WGM21         3
#define TCCR2_COM21         4
#define TCCR2_COM21         5
#define TCCR2_WGM20         6
#define TCCR2_FOC2          7


#define TCNT2               *((volatile u8 *)0x44)
#define OCR2                *((volatile u8 *)0x43)

#define TIMSK               *((volatile u8 *)0x59)
#define TIMSK_TOIE2         6
#define TIMSK_OCIE2         7

#define TIFR                *((volatile u8 *)0x58)
#define TIFR_TOV2          6
#define TIFR_OCF2          7

#define TMR2_CLK_MASK()                         (TCCR2 &= 0b11111000)
#define TMR2_CLK_SELECT(TMR2_PRESCALER)         (TCCR2 |= TMR2_PRESCALER)



#endif