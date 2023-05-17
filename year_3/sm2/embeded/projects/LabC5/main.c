/*
 * File:   LabC5.c
 * Author: GILAD MEIR
 *
 * Created on May 17, 2023, 16:17 AM
 */

#include <stdlib.h>
#include <stdio.h>
#include <p24FJ256GA705.h>
#include "System/system.h"
#include "System/delay.h"
#include "oledDriver/oledC.h"
#include "oledDriver/oledC_colors.h"
#include "oledDriver/oledC_shapes.h"

#define COMPO -1
#define RED 0
#define GREEN 1
#define BLUE 2
#define OC1 13
#define OC2 14
#define OC3 15
#define threshold 0x0050
int is_s1 = 0;
int is_s2 = 1;
int temp_levels[3];

void is_pressed() {
    int counter = 0;
    while (!PORTAbits.RA11) {
        counter++;
    }
    if (counter > 10) {
        is_s1 = 1;
        counter = 0;
    } else {
        is_s1 = 0;
    }
    while (!PORTAbits.RA12) {
        counter++;
    }
    if (counter > 10) {
        is_s2 = 1;
        counter = 0;
    } else {
        is_s2 = 0;

    }

}

void change_brightness(int pot, int curr_color) {
    long temp = 0;
    switch (curr_color) {
        case RED:
            OC1R = pot;
            break;
        case GREEN:
            OC2R = pot;
            break;
        case BLUE:
            OC3R = pot;
            break;
        default:
            temp = pot;
            OC1R = temp_levels[0];
            OC1R = (uint16_t) (OC1R * temp / 1024);
            if (OC1R == 0)
                RPOR13bits.RP26R = 0;
            else
                RPOR13bits.RP26R = OC1;
            OC2R = temp_levels[1];
            OC2R = (uint16_t) (OC2R * temp / 1024);
            if (OC2R == 0)
                RPOR13bits.RP27R = 0;
            else
                RPOR13bits.RP27R = OC2;
            OC3R = temp_levels[2];
            OC3R = (uint16_t) (OC3R * temp / 1024);
            if (OC3R == 0)
                RPOR11bits.RP23R = 0;
            else
                RPOR11bits.RP23R = OC3;
            break;

    }
}

int sample_pot() {
    AD1CON1bits.SAMP = 1;
    DELAY_milliseconds(50);
    AD1CON1bits.SAMP = 0;
    while (!AD1CON1bits.DONE);

    return (ADC1BUF0);
}

void inc_light(int curr_color) {
    switch (curr_color) {
        case RED:
            RPOR13bits.RP26R = OC1;
            RPOR13bits.RP27R = 0;
            RPOR11bits.RP23R = 0;
            break;
        case GREEN:
            RPOR13bits.RP26R = 0;
            RPOR13bits.RP27R = OC2;
            RPOR11bits.RP23R = 0;
            break;
        case BLUE:
            RPOR13bits.RP26R = 0;
            RPOR13bits.RP27R = 0;
            RPOR11bits.RP23R = OC3;

            break;
        default://COMPO
            RPOR13bits.RP26R = OC1;
            RPOR13bits.RP27R = OC2;
            RPOR11bits.RP23R = OC3;

    }

}

void User_Initialize(void) {

    oledC_setBackground(0x0);

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

    /************************************************************************************/

    //OC1 (13) TO RA0 - RED (RP26)     OC2 (14) TO RA1 - GREEN (RP27)     OC3 (15) TO RC7 - BLUE (RP23)
    RPOR13bits.RP26R = OC1;
    RPOR13bits.RP27R = OC2;
    RPOR11bits.RP23R = OC3;

    // define OC1RS, OC2RS, OC3RS to full period (amount of time it's high) 100%=1023
    OC1RS = 1024;
    OC2RS = 1024;
    OC3RS = 1024;
    // init brightness level to 100
    OC1R = 100;
    OC2R = 100;
    OC3R = 100;

    // other parameters
    OC1CON2bits.SYNCSEL = 0x1F; //self-sync
    OC1CON2bits.OCTRIG = 0; //sync mode
    OC1CON1bits.OCTSEL = 0b111; //FOSC/2
    OC1CON1bits.OCM = 0b110; //edge aligned
    OC1CON2bits.TRIGSTAT = 1;

    OC2CON2bits.SYNCSEL = 0x1F; //self-sync
    OC2CON2bits.OCTRIG = 0; //sync mode
    OC2CON1bits.OCTSEL = 0b111; //FOSC/2
    OC2CON1bits.OCM = 0b110; //edge aligned
    OC2CON2bits.TRIGSTAT = 1;

    OC3CON2bits.SYNCSEL = 0x1F; //self-sync
    OC3CON2bits.OCTRIG = 0; //sync mode
    OC3CON1bits.OCTSEL = 0b111; //FOSC/2
    OC3CON1bits.OCM = 0b110; //edge aligned
    OC3CON2bits.TRIGSTAT = 1;


}

/*
                         Main application
 */
int main(void) {

    // initialize the system
    SYSTEM_Initialize();
    User_Initialize();
    int curr_color = COMPO;
    int prev_stat;
    int colors_level[] = {100, 100, 100};
    int pot = 0, temp_pot = 0, compot = 0;

    //Main loop
    while (1) {
        if (is_s2)// S2 is pressed
        {
            curr_color = ((curr_color + 1) % 3);
            inc_light(curr_color);
            is_pressed();
            //            pot = sample_pot();
            while ((!is_s2 && !is_s1)) {
                pot = sample_pot();
                if (!((pot < temp_pot - threshold) || (pot > temp_pot + threshold))) {
                    is_pressed();
                    continue;
                }
                if ((pot < colors_level[curr_color] - threshold) || (pot > colors_level[curr_color] + threshold)) {
                    colors_level[curr_color] = pot;
                    change_brightness(pot, curr_color);
                    colors_level[curr_color] = pot;
                    temp_pot = pot;
                    is_pressed();
                }

            }
        }

        if (is_s1)// S1 IS PRESSED 
        {
            for (int i = 0; i < 3; i++)
                temp_levels[i] = colors_level[i];
            curr_color = -1;
            inc_light(curr_color);
            temp_pot = pot;
            is_pressed();
            while (!is_s1) {
                compot = sample_pot();
                if ((compot < temp_pot - threshold) || (compot > temp_pot + threshold)) {
                    change_brightness(compot, curr_color);
                    temp_pot = compot;
                }
                is_pressed();
            }
            for (int i = 0; i < 3; i++)
                colors_level[i] = temp_levels[i];
            curr_color = BLUE;
            is_s2 = 1;
        }
    }
    return 1;
}


/**
 End of File
 */


