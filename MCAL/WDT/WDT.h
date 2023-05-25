/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     WDT	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/

#ifndef _WDT_H
#define _WDT_H

#define WDTCR               *((volatile u8 *) 0x41)
#define WDTCR_WDTOE         4
#define WDTCR_WDE           4

/*  Librarys Includes   */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Error_States.h"
typedef enum{
    ms16_3 = 0,
    ms32_5 = 1,
    ms65   = 2,
    s_13   = 3,
    s_26   = 4,
    s_52   = 5,
    s1     = 6,
    s2_1   = 7
}WDT_SECONDS;

ES_t WDT_Enable(void);
ES_t WDT_Disable(void);
ES_t WDT_Sleep(WDT_SECONDS WDT_Seconds);






#endif