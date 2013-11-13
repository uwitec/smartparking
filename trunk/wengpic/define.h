#ifndef	__DEF__
#define __DEF__




/* 振盪器頻率 */
#define	FOSC	12000000
/*  自定型態  */
typedef  unsigned char  uint8;
typedef  unsigned int   uint16;
typedef  unsigned short long   uint24;
typedef  unsigned long  uint32;
typedef  char	int8;
typedef  int	int16;
typedef  short long	int24;
typedef  long	int32;
typedef  far rom char*  FRC;

#define	BIT0	1
#define	BIT1	(1<<1)
#define	BIT2	(1<<2)
#define	BIT3	(1<<3)
#define	BIT4	(1<<4)
#define	BIT5	(1<<5)
#define	BIT6	(1<<6)
#define	BIT7	(1<<7)

#define	SET(reg,b)  reg |= (b)
#define	CLR(reg,b)  reg &= ~(b)
#define	TGL(reg,b)  reg ^= (b)
#define	DIRIN(reg,b)  reg |= (b)
#define	DIROUT(reg,b)  reg &= ~(b)

struct srtcc {
	uint8	year;
	uint8	mon;
	uint8	day;
	uint8	hour;
	uint8	week;
	uint8	min;
	uint8	sec;
};	

/*  結構位元定義  */
struct _S8 {
	unsigned b0:1;
	unsigned b1:1;
	unsigned b2:1;
	unsigned b3:1;
	unsigned b4:1;
	unsigned b5:1;
	unsigned b6:1;
	unsigned b7:1;
};

#define	B0(x)	((struct _S8 *)&x)->b0
#define	B1(x)	((struct _S8 *)&x)->b1
#define	B2(x)	((struct _S8 *)&x)->b2
#define	B3(x)	((struct _S8 *)&x)->b3
#define	B4(x)	((struct _S8 *)&x)->b4
#define	B5(x)	((struct _S8 *)&x)->b5
#define	B6(x)	((struct _S8 *)&x)->b6
#define	B7(x)	((struct _S8 *)&x)->b7
/* 自定位元，定義與使用
#define	_tmr0F	B0(initF)	//定義 initF 第0位元為 _tmr0F
	_tmr0F = 1;
	if (_tmr0F == 0){ _tmr0F = 1; }
*/

extern near unsigned char	initF,initF1;
#define	_tmr0F	B0(initF)
#define	_7ledF	B1(initF)
#define	_uartF	B2(initF)
#define	_rtccF	B3(initF)
#define	_lcdF	B4(initF)
#define	_rfidF	B5(initF)
#define	_intF	B6(initF)	//Demo 程式中斷許可
#define _adcF   B7(initF)

#define _ccrF   B0(initF1)


#define	RELAY	B0(LATD)
#define	BEEP	B1(LATD)
/***  INTCON  ***/
#define	_GIEH	B7(INTCON)
#define	_GIEL	B6(INTCON)

/***  RCON  ***/
#define	_IPEN	B7(RCON)
#define INTON() {_IPEN=1; _GIEL=1; _GIEH=1;}
#define INTOFF() _GIEH=0

//--- PPS input PIN
#define miINT1   RPINR1
#define miINT2   RPINR2
#define miINT3   RPINR3
#define miT0CKI  RPINR4
#define miT3CKI  RPINR6
#define miCCP1   RPINR7
#define miCCP2   RPINR8
#define miT1G    RPINR12
#define miT3G    RPINR13
#define miURX2   RPINR16
#define miUCK2   RPINR17
#define miSDI2   RPINR21
#define miSCKIN2 RPINR22
#define miSSIN2  RPINR23
#define miPWMFL  RPINR24
//--- PPS RPORx output PIN
#define moNULL   0
#define moC1OUT  1
#define moC2OUT  2
#define moUTX2   5
#define moUDT2   6
#define moSDO2   9       //SPI data out
#define moSCK2   10      //SPI clock out
#define moSSDMA  12      //SPI DMA 從選擇
#define moULPOUT 13      //低功耗喚醒事件
#define moCCP1   14      //CCP1
#define moP1B    15
#define moP1C    16
#define moP1D    17
#define moCCP2   18      //CCP2
#define moP2B    19
#define moP2C    20
#define moP2D    21

#define RPO(fn,rpn)  *(&RPOR0+rpn) = fn;
#define RPI(fn,rpn)  fn=rpn;
#endif
