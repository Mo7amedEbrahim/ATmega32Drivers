/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     TMR1	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _TMR1_PRIVATE_H
#define _TMR1_PRIVATE_H

/*  Choose Mode */
#define TMR1_NORMAL_MODE        0
#define TMR1_CTC_MODE           1
#define TMR1_FAST_PWM_ICR       2

/*  Choose Channel  */
#define TMR1_CHANNEL_A          0
#define TMR1_CHANNEL_B          1


/*  Choose PreScaler    */
#define TMR1_NO_CLK_SRC         0
#define TMR1_DIV_BY_8           1
#define TMR1_DIV_BY_64          2
#define TMR1_DIV_BY_256         3
#define TMR1_DIV_BY_1024        4
#define TMR1_EXTERNAL_FALLING   5
#define TMR1_EXTERNAL_RISING    6


#define TMR1_MODE_MASK()                        do{                     \
                                                    TCCR1A &= 0b11111100;\
                                                    TCCR1B &= 0b11100111;\
                                                    }while(0)

#define TMR1_CLK_MASK()                        (TCCR1B &=0b11111000)
#define TMR1_CLK_SELECT(TIMER1_PRESCALER)      (TCCR1B |=TIMER1_PRESCALER)





#endif
