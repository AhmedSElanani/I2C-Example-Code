/*
 * Master_Code_1.c
 *
 * Created: 12-Jul-20 10:41:37 PM
 * Author : Ahmed Salah
 */ 

#define		F_CPU		16000000UL


#include "DIO Driver/DIO_INIT.h"
#include "I2C Driver/I2C.h"
#include "delay_Timer1 Driver/delay_Timer1.h"



//	Global Variables
static volatile u8 Binary_Flags = 0;
static volatile u8 Output_Data = 0;


//	Function Prototypes
void I2C_Handler(void);


//	Main Entry Point
int main(void)
{
    /* Initialize PORTD */
    DIO_VidSetPortDirection(portD,OUTPUT);
    DIO_VidWritePortValue(portD,0);
	
	/* Initialize PORTA For Debugging */
	DIO_VidSetPortDirection(portA,OUTPUT);
	DIO_VidWritePortValue(portA,0);
							
    /* Initialize I2C */
    I2C_Callback(I2C_Handler);
    I2C_Init();
	
    while (1) 
    {
		//Check the State of Binary Semaphore
		if (Binary_Flags == 0x03)
		{
			//Reset Binary Semaphore
			Binary_Flags = 0;
			
			//Output the Data Received over I2C to PORTD
			DIO_VidWritePortValue(portD,Output_Data);

			//Delay for a time
			delay_ms_Timer1(50);
			
			/* Send Start Condition */
			generate_start_condition ();
			
		}
    }
}


void I2C_Handler(void)
{
	//Initialize a Variable to hold the Transmitted Data for the first Function Call only
	static volatile u8 Data = 2;		

	switch(Read_StatusRegister())
	{
		case STARTCONDITION_SENT:
			I2C_Send_AddressPacket(0x01,WRITE);
			clear_TWSTA_bit();
			break;
		
		case SLAW_SENT_ACK_RECEIVED:
			I2C_Transmit_DataPacket(Data);
			break;
		
		case DATA_SENT_ACK_RECEIVED:
			generate_stop_condition();
			Data += 3;
			break;
		
		case STOP_OR_REPEATEDSTART_RECEIVED_STILLSLAVE:
			Binary_Flags |= 1;
			break;
		
		case DATA_RECEIVED_ACK_SENT:
			Output_Data = I2C_Receive();
			Binary_Flags |= 2;
			break;
		
	}
	
	//Show the Contents of the Status Register for Debugging
	DIO_VidWritePortValue(portA,Read_StatusRegister());

	//Clear the Flag
	clear_TWINT_flag ();

}