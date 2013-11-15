
#include "WengPIC.h"
#include "smartparking.h"
#include <string.h>





uint8 ccbuf[64];
uint8 CNT;

Packet packet;
Client client[MAX_CLIENT];

void LcdPkg(void){
      //  Packet* pPacket = (Packet*) ccbuf;
	LPutC(packet.length+'0');LPutC(' ');
	LPutC(packet.srcID/100+'0'); LPutC((packet.srcID/10)%10+'0'); LPutC(packet.srcID%10+'0'); LPutC(' ');
        LPutC(packet.dstID/100+'0'); LPutC((packet.dstID/10)%10+'0'); LPutC(packet.dstID%10+'0'); LPutC(' ');
	LPutC(packet.Data[0]+'0');   LPutC(packet.Data[1]+'0');
	LPutC(packet.Data[2]+'0');   LPutC(packet.Data[3]+'0');
}

void PrePkg( Packet packet){
    memcpy(ccbuf , &packet ,sizeof(packet) );
}

void ccRXProc(void){
	uint8 r;
	r=ccFSM();
	switch (r){
		uint8 r1;
		case 1:
			r1=ccGetPkg(ccbuf);
			if(r1==0){//if( ccbuf[3]=packet.srcID){}
                            memcpy(&packet , ccbuf,sizeof(Packet));
                            LcdAddr(0x40);
                            LcdPkg();
                           
                          
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

     // --all init variable define here--

      
/*
       packet.type=ASK;
       packet.subtype=ENTER;
       packet.length=2;
       packet.srcID=254;
       packet.dstID=1;
*/
   // uint8 tempData[4] = {4,6,9,1};
   // int i = 0;
       packet.type=ECHO;
       packet.subtype=ENTER;
       packet.length=5;
       packet.srcID=254;
       packet.dstID=1;
      // for(i=0; i<sizeof(tempData); i++)
           //packet.Data[i] = tempData[i];

    //-----------------



	ANCON0 = 0xFF;
	ANCON1 = 0x1F;
	ccInit();
	ccSIDLE();
        //Tmr0Init(50);
      

	while(1){
		Tmr0Proc();
               CNT++;
		if (CNT>199 ){
                            
                            PrePkg(packet);
                            LcdAddr(0); LcdPkg();
                            CNT=0;
                            ccSIDLE(); ccSFTX();
                            ccSendPkg(ccbuf);
                }
            
		else{ccRXProc();}
                //
	}
}


uint8 CARIND=0;
/*typedef struct s_table {
    uint8 ID[8];
    uint32 IT;
    uint8 PARK;
    uint32 PT;
} STABLE;
*/
void IDcopy(uint8* dis, uint8* src, int iSize){
    memcpy(dis,src,iSize);
}
uint8 id[8];
STABLE mystable[10];
STABLE *sp;
void test(void){
    
    
    sp = &mystable[CARIND];
    IDcopy(sp->ID,id,sizeof(id));
    sp->IT++;
    sp->PARK=1;
    sp->PT++;

}



