/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     ADC	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _ADC_INTERFACE_H
#define _ADC_INTERFACE_H
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Error_States.h"

typedef struct{
	u8 *Channel;
	u16 *Result;
	u8 Size;
	void(*NotifyFunction)(void);
}Chain_t;


/*  APIs    Prototype   */
ES_t ADC_Init(void);
ES_t ADC_DeInit(void);
ES_t ADC_StartConversionSynch(u8 Local_u8Channel, u16 *Copy_pu16Reading);
ES_t ADC_StartConversionASynch(u8 Local_u8Channel, u16 *Copy_pu16Reading, void(*LocalPtr)(void));
ES_t ADC_StartChainAsynch(Chain_t *Copy_Chain);	//ReEnterant function


/*
	TODO : * Dealing with AutoTrigger | After Timer	
*/

/*			UPDATES	
	* Dealing with Interrupt
	* Problem with AVCC Solved
	* Dealing with ADCL and Get 10 Bit Resolution
	* Implement Chain Conversion
*/


#endif
