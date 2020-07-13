//****************************************************************************
 #ifndef	I2C_CONFIG_H_
 #define	I2C_CONFIG_H_
 

/*	I2C Configuration	*/ 
//	Define CPU Clock
#ifndef	F_CPU
#define	F_CPU									16000000UL		//16MHz
#endif

#define		I2C_Enable							1			// (1) to Enable, (0) to Disable
#define		I2C_SlaveAddress					0x01		// Choose any unreserved 7-Bit Address you like
#define		I2C_Prescaler						92			// Choose from (0) to (255), which gives Prescaler from (F_CPU/16) to (F_CPU/526)
#define		Enable_GeneralCall_Rec				1			// (1) to Enable, (0) to Disable 
#define		I2C_Interrupt_Enable				1			// (1) to Enable, (0) to Disable




/*	You Needn't Modify this Part	*/
//	I2C Modes
#define		WRITE								0
#define		READ								1

//	I2C States
#define		STARTCONDITION_SENT							0x08
#define		REPEAT_STARTCONDITION_SENT					0x10
#define 	SLAW_SENT_ACK_RECEIVED						0x18
#define 	SLAW_SENT_NACK_RECEIVED						0x20
#define 	SLAR_SENT_ACK_RECEIVED						0x40
#define 	SLAR_SENT_NACK_RECEIVED						0x48
#define 	SLAW_RECEIVED_ACK_SENT						0x60
#define		DATA_SENT_ACK_RECEIVED						0x28
#define		DATA_SENT_NACK_RECEIVED						0x30
#define		DATA_RECEIVED_ACK_RECEIVED					0x50
#define		DATA_RECEIVED_NACK_RECEIVED					0x58
#define 	DATA_RECEIVED_ACK_SENT						0x80
#define 	DATA_RECEIVED_NACK_SENT						0x88
#define		ARBITRATION_LOST							0x38
#define		STOP_OR_REPEATEDSTART_RECEIVED_STILLSLAVE	0xA0



#endif
//****************************************************************************