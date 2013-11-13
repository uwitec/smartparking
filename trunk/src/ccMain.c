#include "WengPIC.h"
//asasa 
#define _GID		ccbuf[1]
#define _SID 		ccbuf[3]
#define _TID		ccbuf[4]
#define GID		10
#define MyID            66
#define TID     	8
#define TID2            99
uint8 ccbuf[64];
uint8 CNT,vs;
uint24 ad200;
uint8 crv[10]={0,1,1,1,0,0,0,1,1,0};
void LcdPkg(void){
	LPutC(_SID/10+'0');LPutC(_SID%10+'0');LPutC(' ');
	LPutC(_TID/10+'0');LPutC(_TID%10+'0');LPutC(' ');
	LPutC(ccbuf[5]);   LPutC(ccbuf[6]);
	LPutC(ccbuf[7]);   LPutC(ccbuf[8]);LPutC(' ');
	LPutC(ccbuf[9]);   LPutC(ccbuf[10]);
	LPutC(ccbuf[11]);  LPutC(ccbuf[12]);

}

void PrePkg(uint16 vr, uint8 sw){
	uint8 a,b;
	ccbuf[0]=12;
	_GID=GID ;
	ccbuf[2]=GID>>8;
	_SID=MyID;
	_TID=TID;

	a=vr/100; b=vr%100;
	ccbuf[5]=a/10+'0'; ccbuf[6]=a%10+'0';
	ccbuf[7]=b/10+'0'; ccbuf[8]=b%10+'0';

	ccbuf[9]=B0(sw)+'0';
	ccbuf[10]=B1(sw)+'0';
	ccbuf[11]=B2(sw)+'0';
	ccbuf[12]=B3(sw)+'0';

}

/*void PrePkg2(uint16 vr, uint8 sw){
	uint8 a,b;
	ccbuf[0]=12;
	_GID=GID;
	ccbuf[2]=GID>>8;
	_SID=MyID;
	_TID=TID2;

	a=vr/100; b=vr%100;
	ccbuf[5]=a/10+'0'; ccbuf[6]=a%10+'0';
	ccbuf[7]=b/10+'0'; ccbuf[8]=b%10+'0';

	ccbuf[9]=B0(sw)+'0';
	ccbuf[10]=B1(sw)+'0';
	ccbuf[11]=B2(sw)+'0';
	ccbuf[12]=B3(sw)+'0';

}*/

void ccRXProc(void){
	uint8 r;
	r=ccFSM();
	switch (r){
		uint8 r1;
		case 1:
			r1=ccGetPkg(ccbuf);
			if(r1==0){
				if(_TID==MyID ){
                                   LcdAddr(0x40);
                                   LcdPkg();


                                }
                            //LcdAddr(0x40); LcdPkg();
                           // if(ccbuf[9] == 1 &&){ccSendPkg(crv);}
			}
				ccSRX();
				break;
		case 17:
			ccSFRX();
			ccSIDLE();
			ccSRX();
			break;
		}
}

void main(void){
	ANCON0 = 0xFF;
	ANCON1 = 0x1F;
	ccInit();
	ccSIDLE();
        //Tmr0Init(50);
	while(1){
		Tmr0Proc();
		CNT++;
		ad200 += GetADC(4);
		vs |= BtnProc();
		if (CNT>199 ){

                            PrePkg(ad200/200,vs);
                            LcdAddr(0); LcdPkg();
                            ad200=0; vs=0;
                            CNT=0;
                            ccSIDLE(); ccSFTX();
                            ccSendPkg(ccbuf);
                }
                /*else if(CNT>399){
                            PrePkg2(ad200/200,vs);
                            LcdAddr(0); LcdPkg();
                            ad200=0; vs=0;
                            CNT=0;
                            ccSIDLE(); ccSFTX();
                            ccSendPkg(ccbuf);
		}*/
		else{
			ccRXProc();
		}
	}
}

