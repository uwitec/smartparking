#ifndef	__WENGPIC__
#define	__WENGPIC__
#include    <p18f46j50.h>
#include    <delays.h>
#include    "define.h"

/***  joseph add   ***/
#define REG(x)  (*(volatile unsigned char*)x)

/***  7LED  ***/
void LedInit(void);
void Hex2Led(uint8 VH, uint8 VL);
void Val2Led(uint8 VH, uint8 VL);
void LedDot(uint8 tp);
void LedProc(void);
/*** TMR0 ***/
void Tmr0Init(uint8 mS);
void Tmr0Proc(void);
/*** RTCC ***/
void RTCCInit(void);
void SetRTC(struct srtcc *s);
/*** UART ***/
void uartinit(void);
void rprint(const rom char *src);
void uprint(char *src);
void UPutC( uint8 c);
void HPutC( uint8 val);
/***  LCD  ***/
void LcdCmd( uint8 Data);
void LPutC( uint8 Data);
void LcdInit(void);
void LcdHex( uint8 val );
void LPrint( uint8 Pos, const rom char * Ptr);
void LcdDump(uint8 pos, uint8 v);
#define	LcdAddr(x)  LcdCmd(0x80|x)
/***  I2C  ***/
void Sbit(void);
void Pbit(void);
uint8 I2CWrite(uint8 Data);
uint8 I2CRead (uint8 ack );
/***  24LC32  ***/
uint8 eepWrite(uint16 addr, uint8 nbyte, uint8 *src);
uint8 eepRead(uint16 addr, uint8 nbyte, uint8 *dst);
/***  PPS  ***/
void PPSunlock(void);
void PPSlock(void);
/***  RFID  ***/
uint8 GetCardID(void);
/***  Button  ***/
uint8 BtnProc(void);
extern uint8 sw1sta,sw2sta,sw3sta,sw4sta;
/*** CC2500 ***/
void ccInit(void);
uint8 ccGetPkg(uint8 *dst);
void ccSendPkg(uint8 *src);
void ccStrobe(uint8 reg);
uint8 ccGetReg(uint8 reg);
void ccSetReg(uint8 reg, uint8 val);
void ccProc(void);

#define ccSetPW(n)      ccSetReg(0x7E,n)
#define ccGetPW()       ccGetReg(0xFE)
#define ccStatus(reg)   ccGetReg(0xC0 | reg)
#define ccSRX()         ccStrobe(0x34)
#define ccSTX()         ccStrobe(0x35)
#define ccSIDLE()       ccStrobe(0x36)
#define ccSFRX()        ccStrobe(0x3A)
#define ccSFTX()        ccStrobe(0x3B)
#define ccFSM()         ccStatus(0x35)
/***  共用變數  ***/
extern uint8 rfid[8];
extern uint8 v[5];	//卡號
/*** AD ***/
void ADInit(void);
int16 GetADC( uint8 ch);
/*** Relay ***/
void RlyON(uint8 n);
void RlyProc(void);
/*** Beep ***/
void BeepON(uint8 n);
void BeeProc(void);
extern uint8 BCNT, RCNT;
#endif
