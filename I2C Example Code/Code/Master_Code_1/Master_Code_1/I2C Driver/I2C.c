//****************************************************************************
#include "I2C.h"


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static void (*volatile G_TWI)(void) ='\0' ;



/*******************************************************************************
 *									ISRs	    	                           *
 *******************************************************************************/
ISR(TWI_vect)
{
	if (G_TWI!='\0')
	{
		(*G_TWI)();
	}
}


/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
  void I2C_Init (void)
 {
	//Check that I2C is Enabled
	#if (I2C_Enable==1)
		//Set the SCL clock frequency in the Master modes
		CLR_BIT(TWSR,TWPS0);
		CLR_BIT(TWSR,TWPS1);
		TWBR = I2C_Prescaler;
		
		//Set the Slave Address
		TWAR = (I2C_SlaveAddress<<1);
		
		//Configure General Call Recognition
		#if (Enable_GeneralCall_Rec==1)
			SET_BIT(TWAR,TWGCE);
		#elif (Enable_GeneralCall_Rec==0)
			CLR_BIT(TWAR,TWGCE);
		#endif
		
		//Enable Acknowledge Bit
		SET_BIT(TWCR,TWEA);
		
		
		//Check that the Interrupt by the I2C is Enabled
		#if (I2C_Interrupt_Enable == 1)
			SET_BIT(TWCR,TWIE);
			asm volatile ("SEI");	//sei();
		#endif
		
		//Enable I2C
		SET_BIT(TWCR,TWEN);
		
	#endif
		
 }
	
	
void generate_start_condition (void)
{
	SET_BIT(TWCR,TWSTA);	
}
	

void generate_stop_condition (void)
{	
	SET_BIT(TWCR,TWSTO);
	while(TWCR&(1<<TWSTO));		/* Wait until stop condition execution */
}


void I2C_Send_AddressPacket(u8 slave,u8 Mode)
{
	//Writing to the register initiates data transmission.
	TWDR = (slave<<1) | (Mode);
}


void I2C_Transmit_DataPacket(u8 data)
{
	//Writing to the register initiates data transmission.
	TWDR = data;
}


u8 I2C_Receive(void)
{
	//Reading the register causes the Shift Register Receive buffer to be read.
	return TWDR;
}


u8 Read_StatusRegister(void)
{
	//Return the status code generated in the Status register to the User	
	return (TWSR&0xF8);
}


void clear_TWINT_flag (void)
{
	//Clear the Interrupt Flag
	SET_BIT(TWCR,TWINT);
}


void clear_TWSTA_bit (void)
{
	//Clear the TWSTA bit in TWCR register when Start Condition is sent
	CLR_BIT(TWCR,TWSTA);
}


   
/*
 * calling back function enable you to use I2C_ISR
 * Any function passed to callback function will be
 * called in ISR
 */
void I2C_Callback(void(*function_ptr) (void))
{
	G_TWI = function_ptr ;
}


 //****************************************************************************