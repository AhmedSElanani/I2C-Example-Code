//****************************************************************************
 #ifndef	I2C__H_
 #define	I2C__H_

 #include "STD_TYPES.h"
 #include "BIT_MATH.h"
 #include "I2C_Config.h"
 #include "I2C_REG.h"
 #include "avr/interrupt.h"
 
 
  
 //	Functions Prototypes
void I2C_Init (void);
void generate_start_condition (void);
void generate_stop_condition (void);
void I2C_Send_AddressPacket(u8 slave,u8 Mode);
void I2C_Transmit_DataPacket(u8 data);
u8 I2C_Receive(void);
u8 Read_StatusRegister(void);
void clear_TWINT_flag (void);
void clear_TWSTA_bit (void);
void I2C_Callback(void(*function_ptr) (void));
 
 
#endif
//****************************************************************************