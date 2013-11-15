#include <p18f46j50.h>
#include <delays.h>
#include "define.h"

#define irsense B2(tmp)  //psta=paring lot status
#define t1000 1000

uint8 irsta=0;
uint8 psta;
uint16 oncnt=0, offcnt=0;


uint8 IRsense(void){

    uint8 tmp;
    DIRIN(TRISD,BIT2);
    Nop();Nop();Nop();Nop();
    tmp=PORTD;
    DIROUT(TRISC,BIT2);


    switch(irsta){
   
        case 1:
            psta=0;
            B2(LATC)=0;
            if(irsense==1) {oncnt=0;irsta=2;}
          //  else {irsta=1;}
            break;

        case 2:
            oncnt++;
            if(oncnt>t1000) {irsta=3;}
            if(irsense==0) {irsta=1;}
            break;


        case 3:
            psta=1;
            B2(LATC)=1;
            if(irsense==0) {irsta=4;offcnt=0;}
            break;

        case 4:
            offcnt++;
            if(offcnt>t1000) {irsta=1;}
            if(irsense==1) {irsta=3;}
           
            break;

        default: irsta=1; break;

     
    }
    return irsta;
}