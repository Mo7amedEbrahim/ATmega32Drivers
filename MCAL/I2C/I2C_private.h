/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     I2C	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _I2C_PRIVATE_H
#define _I2C_PRIVATE_H

//#define F_CPU       8000000
/* ---------- Registers Declarations ---------- */
#define TWBR            *((volatile u8 *) 0x20)   //TWI Bit Rate Register – TWBR

#define TWCR            *((volatile u8 *) 0x56)   //TWI Control Register – TWCR
#define TWCR_TWIE       0
#define TWCR_TWEN       2
#define TWCR_TWWC       3
#define TWCR_TWSTO      4
#define TWCR_TWSTA      5
#define TWCR_TWEA       6
#define TWCR_TWINT      7

#define TWSR            *((volatile u8 *) 0x21)   //TWI Status Register – TWSR
#define TWSR_TWPS0      0
#define TWSR_TWPS1      1
#define TWSR_TWPS3      3
#define TWSR_TWPS4      4
#define TWSR_TWPS5      5
#define TWSR_TWPS6      6
#define TWSR_TWPS7      7

#define TWDR            *((volatile u8 *) 0x23)   //TWI Data Register – TWDR

#define TWAR            *((volatile u8 *) 0x22)   //TWI (Slave) Address Register– TWAR
#define TWAR_TWGCE      0
/**********************************************************************/
#define I2C_MASTER          0
#define I2C_SLAVE           1

#define TWI_STATUS          TWSR & 0xF8
#define TWI_START           0x08
#define TWI_REP_START       0x10
#define TWI_MT_SLA_ACK      0x18
#define TWI_MR_SLA_ACK      0x40
#define TWI_MT_DATA_ACK     0x28
#define TWI_SR_SLA_ACK      0x60
#define TWI_MR_DATA_ACK     0x50






#endif
