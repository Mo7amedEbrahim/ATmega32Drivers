/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     ADC	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _ADC_CONFIG_H
#define _ADC_CONFIG_H


/**
 * @options
 * AREF     /   AVCC    /   INTERNAL_256
 */
#define REF_VOLT    INTERNAL_256


/**
 * @options
 * LEFT_ADJUST for 8Bit Resolution     /   RIGHT_ADJUST for 10Bit Resolution
 */
#define DATAREG    RIGHT_ADJUST

/**
 * @options
 * LEFT_ADJUST     /   RIGHT_ADJUST
 */
#define ADC_PRESCALER   ADC_DIV_BY_128


#define ADC_TIMEOUT     50000



#endif
