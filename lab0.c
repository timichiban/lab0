#include "p24fj64ga002.h"
#include <stdio.h>


_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_ON & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

#define PRESSED 0
#define RELEASED 1
#define cycle 14745600
#define oneSecPR 57599 //2*cycle/256-1

typedef enum stateTypeEnum{
    led4,
    led5,
    led6,
    led7
} stateType;

volatile stateType curState;

int main(void)
{
    initLEDs();
    initCNForSW1();
    initTimer1();
    curState = led4;

    while(1){
         switch(curState){
            case led4:
                turnOnLED(4);
                break;
            case led5:
                turnOnLED(5);
                break;
            case led6:
                turnOnLED(6);
                break;
            case led7:
                turnOnLED(7);
                break;
        }
    }
}

void _ISR _CNInterrupt(void){
    IFS1bits.CNIF = 0;
    if(PORTBbits.RB5 == PRESSED){
        TMR2 = 0; //According to the datasheet this should be reset automatically, but it does not sometimes.
        PR2 = oneSecPR; //Period register value calculated from lecture
        T2CONbits.TCKPS = 0b11; //prescalar 256 //TODO: fix timing to be 2 seconds
        IFS0bits.T2IF = 0; // Timer 2 interrupt flag down
        T2CONbits.TON = 1; // Turn timer 2 on
        int counter = 0;
        // Wait until the timer 2 interrupt flag goes up. This is done in hardware.
        while(IFS0bits.T2IF == 0 && counter != 2) {
            if(PORTBbits.RB5 == RELEASED){
                if(curState == led4) curState = led5;
                else if(curState == led5) curState = led6;
                else if(curState == led6) curState = led7;
                else if(curState == led7) curState = led4;
                return;
            }
            if(IFS0bits.T2IF == 1) {
                IFS0bits.T2IF = 0;
                T2CONbits.TON = 0;
                TMR2 = 0;
                counter+=1;
                T2CONbits.TON = 1; // Turn timer 2 on
            }
        }
        IFS0bits.T2IF = 0; // Put the flag down afterwards.
        T2CONbits.TON = 0; // Turn the timer off so it does not keep counting.
       // if(IFS0bits.T2IF == 1 && PORTBbits.RB5 == PRESSED){
            if(curState == led4) curState = led7;
            else if(curState == led5) curState = led4;
            else if(curState == led6) curState = led5;
            else if(curState == led7) curState = led6;
        //}

    }
    //if timer runs <2 seconds, on release go forward
    //if timer runs >= 2 seconds, on release go backwards
}
