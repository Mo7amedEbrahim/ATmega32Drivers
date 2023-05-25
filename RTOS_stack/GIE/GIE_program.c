/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   RTOS_stack			      ***************************/
/*************                SWC :     GIE	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
/*		Libraries Includes		*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Error_States.h"
/*		GIE files Includes		*/
#include "GIE_register.h"
#include "GIE_interface.h"


ES_t GIE_Enable(void){
	ES_t Local_enuErrorstate = ES_NOK;
	SET_BIT(SREG,SREG_GIE);
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}

ES_t GIE_Disable(void){
	ES_t Local_enuErrorstate = ES_NOK;
	CLR_BIT(SREG,SREG_GIE);
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}
