/*
 * File:   LabC4.c
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


}

/*
                         Main application
 */
int main(void) {

    // initialize the system
    SYSTEM_Initialize();
    User_Initialize();

    uint8_t str_integer[5];
    uint8_t str_pot[5];
    uint8_t font_color = 0x10;
    int count = 0;
    int pot = 0;
    int temp = 0;
    int inv_flag = 0;


    //Set OLED Background color and Clear the display and display 0 for S1 press-counter
    oledC_setBackground(0xfc60);
    sprintf(str_integer, "%d", count);
    oledC_DrawString(35, 1, 3, 3, str_integer, 0x10);
    sprintf(str_pot, "%d", pot);
    oledC_DrawString(35, 50, 3, 3, str_pot, font_color);

    //Main loop
    while (1) {

        AD1CON1bits.SAMP = 1;
        DELAY_milliseconds(50);
        AD1CON1bits.SAMP = 0;
        while (!AD1CON1bits.DONE);
        temp = ADC1BUF0;
        if ((temp < pot-0x0010) || (temp > pot+0x0010)){
            oledC_DrawString(35, 50, 3, 3, str_pot, 0xfc60);
            pot = temp;
            sprintf(str_pot, "%d", pot);
            oledC_DrawString(35, 50, 3, 3, str_pot, 0x10);
        }





        if (!PORTAbits.RA12)// S2 is pressed
        {
            if (!inv_flag) // inverse is off, color is on as it should
            {
                inv_flag = 1;
                while (!PORTAbits.RA12)
                    oledC_sendCommand(0xA7, NULL, 0);
            } else {
                inv_flag = 0;
                while (!PORTAbits.RA12)
                    oledC_sendCommand(0xA6, NULL, 0);
            }
        }

        if (!PORTAbits.RA11)// S1 IS PRESSED 
        {
            oledC_DrawString(35, 1, 3, 3, str_integer, 0xfc60);
            LATAbits.LATA8 = 1;
            count++;
            sprintf(str_integer, "%d", count);
            oledC_DrawString(35, 1, 3, 3, str_integer, 0x10);
            while (!PORTAbits.RA11);
        } else
            LATAbits.LATA8 = 0;
    }
    return 1;
}
/**
 End of File
 */

