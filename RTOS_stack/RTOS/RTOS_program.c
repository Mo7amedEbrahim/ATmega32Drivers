/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        **************************/
/*************                LAYER :   RTOS_stack			      ***********************/
/*************                SWC :     RTOS	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
/*		Libraries Includes		*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Error_States.h"
/*  MCAL Includes   */
#include "../Timer2/TMR2_interface.h"
#include "../GIE/GIE_interface.h"
/*  RTOS Includes   */
#include "RTOS_private.h"
#include "RTOS_interface.h"
#include "RTOS_config.h"

Task_t SystemTasks[TASK_NUMBER] = {{NULL}};

void RTOS_Start(void){
    TMR2_CTCSetCallBack(&voidScheduler);
    GIE_Enable();
    TMR2_init(125);
}

ES_t RTOS_CreateTask(u8 Copy_u8Priority,u16 Copy_u16Periodicity,void (*Copy_pvTaskFunc)(void),u16 Copy_u16FirstDelay){
    ES_t Local_enuErrorstate = ES_NOK;
    if(SystemTasks[Copy_u8Priority].TaskFunc == NULLPTR){
        SystemTasks[Copy_u8Priority].Periodicity = Copy_u16Periodicity;
        SystemTasks[Copy_u8Priority].TaskFunc = Copy_pvTaskFunc;
        SystemTasks[Copy_u8Priority].Task_State = TASK_RESUMED;
        SystemTasks[Copy_u8Priority].FirstDelay = Copy_u16FirstDelay;
        Local_enuErrorstate = ES_OK;
    }
    else{
        /*  Reserved Priority   */
    }
    return Local_enuErrorstate;
}

void RTOS_DeleteTask(u8 Copy_u8Priority){
    SystemTasks[Copy_u8Priority].TaskFunc = NULLPTR;
}

void RTOS_SuspendTask(u8 Copy_u8Priority){
    SystemTasks[Copy_u8Priority].Task_State = TASK_SUSPENDED;
}

void RTOS_ResumeTask(u8 Copy_u8Priority){
    SystemTasks[Copy_u8Priority].Task_State = TASK_RESUMED;
}

static void voidScheduler(void){
    u8 Local_u8TaskCounter = 0;
    for(Local_u8TaskCounter = 0;Local_u8TaskCounter < TASK_NUMBER; Local_u8TaskCounter++){
        if(SystemTasks[Local_u8TaskCounter].Task_State == TASK_RESUMED){
            if( SystemTasks[Local_u8TaskCounter].FirstDelay == 0){
                if(SystemTasks[Local_u8TaskCounter].TaskFunc != NULLPTR){
                    SystemTasks[Local_u8TaskCounter].TaskFunc();
                    SystemTasks[Local_u8TaskCounter].FirstDelay = SystemTasks[Local_u8TaskCounter].Periodicity - 1;
                }
                else{
                    /*  Do Nothing  */
                }
            }
            else{
                SystemTasks[Local_u8TaskCounter].FirstDelay--;
            }
        }
        else{
            //  Task Suspended    
        }
    }
}
