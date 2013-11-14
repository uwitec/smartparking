#include <p18f46j50.h>
#include <delays.h>
#include "define.h"

#define psta B2(tmp)  //psta=paring lot status
#define delay() Delay1KTCYx(10000000000000)




uint8 irsta=0;
uint8 IRsense(void){

    uint8 tmp;
    DIRIN(TRISD,BIT2);
 //   Nop();Nop();
    tmp=PORTD;
 //   DIROUT(TRISD,BIT2);


    switch(irsta){
        case 0:
            if(psta==0) {irsta=1;}
            break;

        case 1:
            if(psta==0) {irsta=2;}
            else {irsta=0;}
            break;

        case 2:
            irsta=3;

            return 1;

        case 3:
            if(psta==1) {irsta=4;}
            else {irsta=3;}
            break;

        case 4:
       
            if(psta==1) {irsta=5;}
            //else{swsta=3;}
            break;

        case 5:
            irsta=0;

            delay();
            return 2;
            break;
    }
}