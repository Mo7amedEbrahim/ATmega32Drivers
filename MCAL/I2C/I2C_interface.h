/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     I2C	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _I2C_INTERFACE_H
#define _I2C_INTERFACE_H

/* ---------- Macaro Declarations ---------- */
#define I2C_WRITE   0
#define I2C_READ    0
/* ---------- Macaro Functions Declarations ---------- */
#define BITRATE(I2C_SPEED)  ((F_CPU - 16ul * I2C_SPEED)/(2ul * I2C_SPEED * I2C_PRESCALER))
/* ---------- DataType Declarations ---------- */



/* ---------- Software Interfaces Declarations ---------- */
ES_t I2C_Init(void);
ES_t I2C_StartCondition(void);
ES_t I2C_RepeatedStartCondition(void);
ES_t I2C_StopCondition(void);
ES_t I2C_WriteSlaveAddress(u8 Copy_u8SlaveAddress,u8 Copy_u8Operation);
ES_t I2C_WriteData(u8 Copy_u8Data);
ES_t I2C_CheckMyAddress(void);
ES_t I2C_ReadData(u8 *Copy_pu8Data);









#endif