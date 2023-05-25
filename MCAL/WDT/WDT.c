/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     WDT	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#include "WDT.h"

ES_t WDT_Enable(void){
    ES_t Local_enuErrorstate = ES_NOK;
    SET_BIT(WDTCR,WDTCR_WDE);
    Local_enuErrorstate = ES_OK;
    return Local_enuErrorstate;
}

ES_t WDT_Disable(void){
    ES_t Local_enuErrorstate = ES_NOK;
    WDTCR = (1<<WDTCR_WDTOE) | (1<<WDTCR_WDE);
    WDTCR = 0;
    Local_enuErrorstate = ES_OK;
    return Local_enuErrorstate;
}


ES_t WDT_Sleep(WDT_SECONDS WDT_Seconds){
    ES_t Local_enuErrorstate = ES_NOK;
    if(WDT_Seconds > 8){
        Local_enuErrorstate = ES_OUT_OF_RANGE;
    }
    else{
        WDTCR |= 0b11111000;    //Masking prescaler bits
        WDTCR |= WDT_Seconds;
        Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}