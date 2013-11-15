
#define GetCard(x)  eepRead(x*8, 8, buf)

uint8 retry;//RF封包是否要重送  1:要重送RFID_CARD_ID
uint8 esta;//0:不可取票  1:可取票
uint8 card_id[8];//FRID_CARD_ID
uint8 ENTER=0;
#define	_RF6	B6(ENTER1)
#define	_RF3	B3(ENTER1)
#define	_RF7	B7(ENTER1)
uint8 entsta(void){
    static uint16 timeout;
	static uint8 ENTSta=0;
	uint8 r;
	switch(ENTSta){
        case 0 : //Reset
            ENTSta++;
	    esta = 0;
	    retry = 0;
	    break;
        case 1: //待命(1)6
	    if( _RF6){ ENTSta++; esta =1; _RF6=0;} break;
        case 2: //取票中 (2)
	    ENTSta++;
            //card_id = GetCardID();
	    r=GetCardID();
	    if(r==1){ esta = 0; retry = 1; }
            break;
        case 3: //已取票3.3
	    if(_RF3){ ENTSta++; timeout=50; _RF3=0;} break;
        case 4:
	    if(_RF7){ ENTSta = 1; retry = 0; _RF7=0;} break;
	}
	return ENTSta;
	}


