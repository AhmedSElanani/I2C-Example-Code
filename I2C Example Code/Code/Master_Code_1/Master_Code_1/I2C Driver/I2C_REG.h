//****************************************************************************
 #ifndef	I2C_REG_H_
 #define	I2C_REG_H_
 
 
 
//	I2C Registers 
#ifndef	TWBR
#define TWBR						(*((volatile u8*)(0x20)))
#endif

#ifndef	TWCR
#define TWCR						(*((volatile u8*)(0x56)))
#endif

#ifndef	TWSR
#define TWSR						(*((volatile u8*)(0x21)))
#endif

#ifndef	TWDR
#define TWDR						(*((volatile u8*)(0x23)))
#endif

#ifndef	TWAR
#define TWAR						(*((volatile u8*)(0x22)))
#endif

 
 
//	I2C Registers Bits
//TWCR Register
#define		TWIE	0
#define		TWEN	2
#define		TWWC	3
#define		TWSTO	4
#define		TWSTA	5
#define		TWEA	6
#define		TWINT	7


//TWSR Register
#define		TWPS0	0
#define		TWPS1	1


//TWAR Register
#define		TWGCE	0

 
#endif
//****************************************************************************