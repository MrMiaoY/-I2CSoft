#include "SoftI2C.h"

#define  SoftI2C_NOP()				{_nop_();_nop_();_nop_();_nop_();_nop_();}
#define  SoftI2C_AckTimeout 	6000

ErrorStatus SoftI2C_Read(u8 I2cAddr,u8 SubAddr,u8 *Data,u8 Length);
ErrorStatus SoftI2C_Write(u8 I2cAddr,u8 SubAddr,u8 *Data,u8 Length);

static void SoftI2C_SCL_SetLevel(u8 Level);
static void SoftI2C_SDA_SetLevel(u8 Level);
static u8 SoftI2C_SDA_GetLevel(void);
static I2CBusStatus SoftI2C_Start(void);
static void SoftI2C_Stop(void);
static void SoftI2C_SendByte(u8 Data);
static u8 SoftI2C_ReceiverByte(void);



void SoftI2C_SCL_SetLevel(u8 Level)
{
		if(Level)
		{
			I2C_SCL = 1;
		}
		else
		{
			I2C_SCL = 0;
		}
}

void SoftI2C_SDA_SetLevel(u8 Level)
{
		if(Level)
		{
			I2C_SDA = 1;
		}
		else
		{
			I2C_SDA = 0;
		}
}

u8 SoftI2C_SDA_GetLevel(void)
{	
		if(I2C_SDA != 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
}

I2CBusStatus SoftI2C_Start(void)
{
    SoftI2C_SDA_SetLevel(1);
    SoftI2C_NOP();
    SoftI2C_SCL_SetLevel(1);	  
    SoftI2C_NOP();
	 
	  if(SoftI2C_SDA_GetLevel() == 0)
		{
		   return I2CBus_Busy;
		}
		
    SoftI2C_SDA_SetLevel(0);
	  SoftI2C_NOP();

		if(SoftI2C_SDA_GetLevel() == 1)
		{
		   return I2CBus_Error;
		}
		
		return I2CBus_Ready;		
}

void SoftI2C_Stop(void)
{
    SoftI2C_SDA_SetLevel(0);
    SoftI2C_NOP();
    SoftI2C_SCL_SetLevel(1);	  
    SoftI2C_NOP();	
    SoftI2C_SDA_SetLevel(1);
    SoftI2C_NOP();	  
}

ErrorStatus SoftI2C_WaitAck(void)
{ 
		
	 u16 RxAckTimeOut =	SoftI2C_AckTimeout;

		SoftI2C_SCL_SetLevel(0);
		SoftI2C_NOP();
		SoftI2C_SDA_SetLevel(1);
		SoftI2C_NOP();
		while(SoftI2C_SDA_GetLevel() && RxAckTimeOut)
		{
				SoftI2C_NOP();
				RxAckTimeOut--;
		}
		
		if(RxAckTimeOut == 0)
		{
				return Error;
		}
		else
		{
			 SoftI2C_SCL_SetLevel(1);
		   SoftI2C_NOP();
			 SoftI2C_SCL_SetLevel(0);
		   SoftI2C_NOP();
				return Success;
		}
}

void SoftI2C_Ack(void)
{        
        SoftI2C_SCL_SetLevel(0);
        SoftI2C_NOP();
        SoftI2C_SDA_SetLevel(0);
        SoftI2C_NOP();
        SoftI2C_SCL_SetLevel(1);
        SoftI2C_NOP();
        SoftI2C_SCL_SetLevel(0);
        SoftI2C_NOP();
}

void SoftI2C_NoAck(void)
{        
        SoftI2C_SCL_SetLevel(0);
        SoftI2C_NOP();
        SoftI2C_SDA_SetLevel(1);
        SoftI2C_NOP();
        SoftI2C_SCL_SetLevel(1);
        SoftI2C_NOP();
        SoftI2C_SCL_SetLevel(0);
        SoftI2C_NOP();
}
		
void SoftI2C_SendByte(u8 Data)
{
		u8 i;  
	
		for(i = 0; i < 8; i++)
	  {	
			SoftI2C_SCL_SetLevel(0);
			SoftI2C_NOP();
			if(Data & 0x80)
			{
					SoftI2C_SDA_SetLevel(1);
			}
			else
			{
					SoftI2C_SDA_SetLevel(0);
			}
			SoftI2C_NOP();	
				
			SoftI2C_SCL_SetLevel(1);	  
      SoftI2C_NOP();				
      Data <<= 1;				
		}
		//SoftI2C_SCL_SetLevel(0);	  
		//SoftI2C_NOP(); 	
		
}

u8 SoftI2C_ReceiverByte(void)
{
		u8 i;
    u8 dat = 0;	

		SoftI2C_SDA_SetLevel(1);	
		SoftI2C_NOP();		
	  
		for(i = 0; i < 8; i++)
	  {					
				dat = (dat<<1);	
				SoftI2C_SCL_SetLevel(0);	  
		    SoftI2C_NOP(); 	
		    SoftI2C_SCL_SetLevel(1);	  
		    SoftI2C_NOP(); 
			
			  if(SoftI2C_SDA_GetLevel() == 1)
				{
						dat = (dat | 0x01);
				}	  
		}	
		//SoftI2C_SCL_SetLevel(0);	  
		//SoftI2C_NOP(); 	
		
		return dat;
}

ErrorStatus SoftI2C_Read(u8 I2cAddr,u8 SubAddr,u8 *Data,u8 Length)
{
		u8 i;	  
 
	  if(SoftI2C_Start())
		{
				SoftI2C_Stop();
			  return Error;
		}
		SoftI2C_SendByte(I2cAddr & 0xfe);		
		if(SoftI2C_WaitAck())
		{
			SoftI2C_Stop();
			return Error;
		}

		SoftI2C_SendByte(SubAddr);
		if(SoftI2C_WaitAck())
		{
			SoftI2C_Stop();
			return Error;
		}
		
		SoftI2C_Stop();
		
	  if(SoftI2C_Start())
		{
				SoftI2C_Stop();
			  return Error;
		}
		SoftI2C_SendByte(I2cAddr | 0x01);
		if(SoftI2C_WaitAck())
		{
			SoftI2C_Stop();
			return Error;
		}
		
		for(i = 0; i < Length; i++)
		{
				*Data = SoftI2C_ReceiverByte();
			   if(i == (Length - 1))
				 {
						SoftI2C_NoAck();
				 }
				 else
				 {
						SoftI2C_Ack();
				 }
				 Data++;
		}

		SoftI2C_Stop();
		return Success;			
}

ErrorStatus SoftI2C_Write(u8 I2cAddr,u8 SubAddr,u8 *Data,u8 Length)
{
		u8 i;

	  if(SoftI2C_Start())
		{
				SoftI2C_Stop();
			  return Error;
		}

		SoftI2C_SendByte(I2cAddr & 0xfe);
		if(SoftI2C_WaitAck())
		{
			SoftI2C_Stop();
			return Error;
		}

		SoftI2C_SendByte(SubAddr);
		if(SoftI2C_WaitAck())
		{
			SoftI2C_Stop();
			return Error;
		}

		for(i = 0; i < Length; i++)
		{
			 SoftI2C_SendByte(Data[i]);
			if(SoftI2C_WaitAck())
			{
				SoftI2C_Stop();
				return Error;
			}			
		}
		
		SoftI2C_Stop();
		return Success;			
}
