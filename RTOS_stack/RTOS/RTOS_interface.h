/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        **************************/
/*************                LAYER :   RTOS_stack			      ***********************/
/*************                SWC :     RTOS	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _RTOS_INTERFACE_H
#define _RTOS_INTERFACE_H



void RTOS_Start(void);
ES_t RTOS_CreateTask(u8 Copy_u8Priority,u16 Copy_u16Periodicity,void (*Copy_pvTaskFunc)(void),u16 Copy_u16FirstDelay);
void RTOS_SuspendTask(u8 Copy_u8Priority);
void RTOS_ResumeTask(u8 Copy_u8Priority);



#endif