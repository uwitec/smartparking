#include "WengPIC.h"
#include <stdio.h>

#define     len     rcv[0]
#define     tp      rcv[1]
#define     ID      rcv[2]
#define     _EID    rcv[3]
#define     _PID    rcv[3]
#define     _PSTA   rcv[4]
#define     MyID    11//看PIC板定義
#define     MID     254
#define     _askparking(id)       sendpkg(2,id,0)
#define     _askenter(id)         sendpkg(3,id,0)


#define rcv     ccbuf

extern uint8 ccbuf[64];
//uint8 rcv[64];
uint8 psta;//parking status
uint8 esta;
uint8 cardid[8];
uint8 retry;
uint8 pary[32];


uint8 sendpkg(uint8 type,uint8 TID,uint8 *data){
    tp = type ;
    switch (type){
        case 1 :
            len = 2;
            ID = 0;
            break;
        case 2 : 
        case 3 :
            len = 2;
            ID = TID ;
            break;
        case 4 :
            len = 3;
            ID = MID;
            _EID = MyID;
            if(retry){
                uint8 i;
                len =11;
                for(i=0;i<8;i++){
                    rcv[4+i] = data[i];
                    }
                 }
            break;
        case 5 :
            len = 4;
            ID = MID;
            _PID = MyID;
            _PSTA = psta;
            break;
        case 6 :
        case 7 :
            len = 2;
            ID = _EID;
            break;
 
    }
    ccSendPkg(rcv);
}
void reset(void){

}

/*-------------------------------------------------*/
#define PNO     3 //車位總數
void query(void){
    static uint8 qsta=0;
    switch(qsta){
        case 0: _askenter(1);       break;
        case 1: _askparking(11);    break;
        case 2: _askparking(12);    break;
        case 3: _askparking(13);    break;
        case 4: _askparking(14);    break;
    } 
    qsta++;
    if(qsta>PNO){qsta=0;}
}
/*------------------------------------------------*/


void EchoParking(uint8 _psta){
    sendpkg(5,MID,_psta);
}
uint8 EchoEnter(uint8 *CARDID){
        uint8 buf[32];
        sprintf(buf,"%d,%s",MyID,CARDID);
        sendpkg(4,MID,buf);
}


int rfim(){
    
            if((MyID != ID)&&(ID != 0)){ return 1;}//error 1 not me
    switch(tp){
        case 1 : //Reset
            if(len != 2){break;}
            if(MyID == MID){break;}//MID送的封包不處理
            reset();    break;
        case 2 : //ask parking
            if(len != 2){break;}
            if(ID == MID){break;}//MID送的封包不處理
            EchoParking(psta); break;
        case 3 : //ask enter
            if(len != 2){break;}
            if(ID == MID){break;}  //MID送的封包不處理          

           EchoEnter(rfid);break;
        case 4 : //echo enter
            if(len == 3 ){break;}
            if(len == 11){
                //uprint(s);//UART Printf CARDID
                sendpkg(7,_EID,0);//ACK
                break;
            }
        case 5 : //echo parking
            if(len != 4){break;}
            {uint8 r;
            r=0;
            if(pary[_PID-11]=='1'){r=BIT1;}
            pary[_PID-11]=_PSTA+'0';
            r+=(pary[_PID-11]=='1');
            if(r==1){sendpkg(6,_EID,0);}
            }
            break;
        case 6 : //command 命令指令
            if(len != 2){break;} 
            esta=1;
            break;
            
        case 7 :  //ack
            if(len != 2){break;}
            retry=0;
            break;

    }


}



