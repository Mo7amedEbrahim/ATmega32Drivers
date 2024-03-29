/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     TMR2	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef TMR2_INTERFACE_H_
#define TMR2_INTERFACE_H_



void TMR2_voidInit(void);
void TMR2_voidSetTimerReg(u16 Copy_u16Value);
u16 TMR2_u16GetTimerReg(void);



#endif /* TMR2_INTERFACE_H_ */