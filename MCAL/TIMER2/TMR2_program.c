/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     TMR2	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Error_States.h"
#include "TMR2_interface.h"
#include "TMR2_register.h"





void TMR2_voidInit(void){
    //Normal Mode
    CLR_BIT(TCCR2,3);
    CLR_BIT(TCCR2,6);
    //Prescaler 1024
    SET_BIT(TCCR2,0);
    SET_BIT(TCCR2,2);
    SET_BIT(TCCR2,1);
}
void TMR2_voidSetTimerReg(u16 Copy_u16Value){
    TCNT2 = Copy_u16Value;
}
u16 TMR2_u16GetTimerReg(void){
    return TCNT2;
}