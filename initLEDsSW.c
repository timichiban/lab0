#include "p24fj64ga002.h"
#include "initLEDsSW.h"

void initLEDs(){
    TRISBbits.TRISB15 = 0;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB12 = 0;

    LATBbits.LATB15 = OFF;
    LATBbits.LATB14 = OFF;
    LATBbits.LATB13 = OFF;
    LATBbits.LATB12 = OFF;
}

/* This is a nice helper function which turns on a particular LED
 */
void turnOnLED(int led){
    if(led == 4){
        LATBbits.LATB15 = ON;
        LATBbits.LATB14 = OFF;
        LATBbits.LATB13 = OFF;
        LATBbits.LATB12 = OFF;
    }
    else if(led == 5){
        LATBbits.LATB15 = OFF;
        LATBbits.LATB14 = ON;
        LATBbits.LATB13 = OFF;
        LATBbits.LATB12 = OFF;
    }
    else if(led == 6){
        LATBbits.LATB15 = OFF;
        LATBbits.LATB14 = OFF;
        LATBbits.LATB13 = ON;
        LATBbits.LATB12 = OFF;
    }
    else if(led == 7){
        LATBbits.LATB15 = OFF;
        LATBbits.LATB14 = OFF;
        LATBbits.LATB13 = OFF;
        LATBbits.LATB12 = ON;
    }
}
