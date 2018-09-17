#ifndef __Soft_I2C_H__
#define __Soft_I2C_H__

#include "main.h"
#include "Delay.h"

//定义I2C_SCL引脚
sbit  I2C_SCL = P2^3;

//定义I2C_SDA引脚
sbit  I2C_SDA = P2^4;

typedef enum
{
    ACK 	= 0,
    NACK 	= 1
} AckStatus;

typedef enum
{
    I2CBus_Ready = 0,
    I2CBus_Busy  = 1,
    I2CBus_Error = 2
} I2CBusStatus;

typedef enum
{
    Success 	= 0,
    Error 	= 1
} ErrorStatus;

extern ErrorStatus SoftI2C_Read(u8 I2cAddr,u8 SubAddr,u8 *Data,u8 Length);
extern ErrorStatus SoftI2C_Write(u8 I2cAddr,u8 SubAddr,u8 *Data,u8 Length);


#endif //__Soft_I2C_H__
