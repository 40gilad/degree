/*
 * File:   LabC6.c
 * Author: Amit
 *
 * Created on April 11, 2021, 16:17 AM
 */

#include <stdlib.h>
#include <stdio.h>
#include <p24FJ256GA705.h>

#include "System/system.h"
#include "System/delay.h"
#include "oledDriver/oledC.h"
#include "oledDriver/oledC_colors.h"
#include "oledDriver/oledC_shapes.h"

int is_inverse = 0;
void __attribute__((__interrupt__))_T1Interrupt(void) {

    if (!is_inverse) {
        is_inverse = 1;
        oledC_sendCommand(OLEDC_CMD_SET_DISPLAY_MODE_INVERSE, NULL, 0);
    } else {
        oledC_sendCommand(OLEDC_CMD_SET_DISPLAY_MODE_ON, NULL, 0);
        is_inverse = 0;
    }
    IFS0bits.T1IF = 0;
    return;

}

void User_Initialize(void) {

    //Initialize LED/Switch IO Direction (TRISx)
    TRISA |= (1 << 11);
    TRISA |= (1 << 12);
    TRISA &= ~(1 << 8);
    TRISA &= ~(1 << 9);

    //Set RB12 (AN8) as Analog Input
    TRISB |= (1 << 12);
    ANSB |= (1 << 12);

    //Initialize A/D Circuit (AD1CON1)
    AD1CHS = 8; //AN8
    //TURN OFF 4-9 BITS IN AD1CON1

    AD1CON1bits.SSRC = 0;
    AD1CON1bits.FORM = 0;
    AD1CON1bits.MODE12 = 1;
    AD1CON1bits.ADON = 1;

    AD1CON2 = 0;
    AD1CON3 = 0X0000;
    AD1CON3bits.ADCS = 0xFF;
    AD1CON3bits.SAMC = 0x10;

        T1CONbits.TON = 1;
    T1CONbits.TSIDL = 1;
    T1CONbits.TGATE = 0;
    //    T1CONbits.TECS=0;
    T1CONbits.TCKPS = 2;
    INTCON2bits.GIE = 1;
    T1CONbits.TCS = 0;
    PR1 = 62500;
    IPC0bits.T1IP = 1;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    
    oledC_setBackground(0xffff);
    oledC_clearScreen();

}

/*
                         Main application
 */
int main(void) {

    // initialize the system
    SYSTEM_Initialize();
    User_Initialize();
    while (1) {
    }
}

/**
 End of File
 */

