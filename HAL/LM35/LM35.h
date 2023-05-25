/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   HAL			      ***************************/
/*************                SWC :     LM35	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _LM35_H
#define _LM35_H

#define RIGHT_ADJUST 1
#define LEFT_ADJUST 0

#define AREF    		0
#define AVCC    		1
#define INTERNAL_256    2
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

ES_t LM35_ReadTempSynch(u8 Copy_u8Channel,u16 *Copy_Reading);
ES_t LM35_ReadTempASynch(u8 Copy_u8Channel,u16 *Copy_Reading,void(*LocalPtr)(void));    //TODO: Fix this function

#endif
