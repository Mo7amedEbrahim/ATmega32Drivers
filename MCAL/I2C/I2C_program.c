/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     I2C	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
/*      Lib Includes    */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Error_States.h"
#include "../../LIB/STD_TYPES.h"
/*      I2C Includes    */
#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"

ES_t I2C_Init(void){
    ES_t Local_enuErrorstate = ES_NOK;
#if I2C_MODE == I2C_MASTER
    /*  Set The BITRATE and Prescaler   */
    TWBR = (u8)BITRATE(I2C_CLOCK_SPEED);
    #if I2C_PRESCALER == 1
        CLR_BIT(TWSR,TWSR_TWPS0);
        CLR_BIT(TWSR,TWSR_TWPS1);
    #elif I2C_PRESCALER == 4
        SET_BIT(TWSR,TWSR_TWPS0);
        CLR_BIT(TWSR,TWSR_TWPS1);
    #elif I2C_PRESCALER == 16
        CLR_BIT(TWSR,TWSR_TWPS0);
        SET_BIT(TWSR,TWSR_TWPS1);
    #elif I2C_PRESCALER == 64
        SET_BIT(TWSR,TWSR_TWPS0);
        SET_BIT(TWSR,TWSR_TWPS1);
    #endif
    /*  Master can act as Slave so we Give him Address  */
    CLR_BIT(TWAR,TWAR_TWGCE);
    TWAR = (I2C_NODE_ADDRESS<<1) | I2C_RECOGNISE_GENERAL_CALL;
    //  Clear the flag
    SET_BIT(TWCR,TWCR_TWINT);
    //  Enable I2C
    SET_BIT(TWCR,TWCR_TWEN);
    Local_enuErrorstate = ES_OK;
#elif I2C_MODE == I2C_SLAVE
    TWAR = (I2C_NODE_ADDRESS<<1) | I2C_RECOGNISE_GENERAL_CALL;
    //  Clear the flag
    SET_BIT(TWCR,TWCR_TWINT);
    //  Enable I2C
    SET_BIT(TWCR,TWCR_TWEN);
    Local_enuErrorstate = ES_OK;
#endif
    return Local_enuErrorstate;
}
ES_t I2C_StartCondition(void){
    ES_t Local_enuErrorstate = ES_NOK;
    SET_BIT(TWCR,TWCR_TWINT);
    SET_BIT(TWCR,TWCR_TWSTA);
    SET_BIT(TWCR,TWCR_TWEN);
    while(!GET_BIT(TWCR,TWCR_TWINT));
    if ( (TWI_STATUS) == TWI_START)
    {
        Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}
ES_t I2C_RepeatedStartCondition(void){
    ES_t Local_enuErrorstate = ES_NOK;
    SET_BIT(TWCR,TWCR_TWINT);
    SET_BIT(TWCR,TWCR_TWSTA);
    SET_BIT(TWCR,TWCR_TWEN);
    while(!GET_BIT(TWCR,TWCR_TWINT));
    if( (TWI_STATUS) == TWI_REP_START){
        Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}

ES_t I2C_StopCondition(void){
    ES_t Local_enuErrorstate = ES_NOK;
    SET_BIT(TWCR,TWCR_TWINT);
    SET_BIT(TWCR,TWCR_TWEN);
    SET_BIT(TWCR,TWCR_TWSTO);
    while(!GET_BIT(TWCR,TWCR_TWINT));
    Local_enuErrorstate = ES_OK;
    return Local_enuErrorstate;
}
ES_t I2C_WriteSlaveAddress(u8 Copy_u8SlaveAddress,u8 Copy_u8Operation){
    ES_t Local_enuErrorstate = ES_NOK;
    u8 Loc_u8Data = Copy_u8SlaveAddress << 1;
    Loc_u8Data |= Copy_u8Operation;
    TWDR = Loc_u8Data;
    SET_BIT(TWCR, TWCR_TWINT);
    SET_BIT(TWCR, TWCR_TWEN);
    while(!GET_BIT(TWCR, TWCR_TWINT));
    u8 Loc_u8Status = TWI_STATUS;
    if (Loc_u8Status == TWI_MT_SLA_ACK || Loc_u8Status == TWI_MR_SLA_ACK) {
    Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}
ES_t I2C_WriteData(u8 Copy_u8Data){
    ES_t Local_enuErrorstate = ES_NOK;
    TWDR = Copy_u8Data;
    SET_BIT(TWCR,TWCR_TWINT);
    while(!GET_BIT(TWCR,TWCR_TWINT));
    if ((TWI_STATUS) == TWI_MT_DATA_ACK) {
        Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}
ES_t I2C_CheckMyAddress(void){
    ES_t Local_enuErrorstate = ES_NOK;
    SET_BIT(TWCR,TWCR_TWINT);
    while(!GET_BIT(TWCR,TWCR_TWINT));
    if ((TWI_STATUS) == TWI_SR_SLA_ACK) {
        Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}
ES_t I2C_ReadData(u8 *Copy_pu8Data){
    ES_t Local_enuErrorstate = ES_NOK;
    SET_BIT(TWCR,TWCR_TWINT);
    SET_BIT(TWCR,TWCR_TWEA);
    while(!GET_BIT(TWCR,TWCR_TWINT));
    if ((TWI_STATUS) == TWI_MR_DATA_ACK) {
        *Copy_pu8Data = TWDR;
        Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}
