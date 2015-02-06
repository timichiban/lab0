#include "p24fj64ga002.h"
#include "initCN.h"

void initCNForSW1(){
    /* Initialize the pin on the development board to be an input. According to
     * the datasheet, this is RB5 or pin 14
     */
    TRISBbits.TRISB5 = 1;

    //Put the overall CN Interrupt flag down (set it to 0)
    IFS1bits.CNIF = 0;

    //Enable the overall change notification interrupt
    IEC1bits.CNIE = 1;
    CNEN2bits.CN27IE = 1;
}
