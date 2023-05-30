/*
 * File:   LabC6.c
 * Author: Gilad Meir
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

//Write your code her2469

void write_bit_2_OLED(int bbit) {
    LATBbits.LATB14 = bbit;
    DELAY_microseconds(1);
    LATBbits.LATB15 = 1;
    LATBbits.LATB15 = 0;
}

void send_command_2_OLED(int command) {
    int mask = 0x80;
    int bite_size = 8;
    int bi_zero = 0x00;
    int bi_one = 0x80;
    LATBbits.LATB15 = 1;
    LATCbits.LATC9 = 0;
    LATBbits.LATB15 = 0;
    while (bite_size != 0) {
        if ((command & mask) == bi_zero) {
            write_bit_2_OLED(0);
        }
        if ((command & mask) == bi_one) {
            write_bit_2_OLED(1);
        }
        bite_size--;
        command = command << 1;
    }
    LATCbits.LATC9 = 1;
}

void oledC_BitBangCommand(unsigned char cmd) {
    if (cmd == OLEDC_CMD_SET_DISPLAY_MODE_INVERSE) {
        send_command_2_OLED(0xA7);
    }
    if (cmd == OLEDC_CMD_SET_DISPLAY_MODE_ON) {
        send_command_2_OLED(0xA6);
    }

    //You may use calls to DELAY_microseconds(), defined in delay.c
}

/*
                         Main application
 */
int main(void) {

    // initialize the system
    SYSTEM_Initialize();

    oledC_setBackground(OLEDC_COLOR_RED);

    //Remove Hardware SPI (see L9 slide #16)
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPOR7bits.RP14R = 0; //RB14->SPI MOSI
    RPOR7bits.RP15R = 0; //RB15->SPI Clock
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
    //Set Direction (GPO) of software-SPI Clock/MOSI
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC9 = 0;
    TRISBbits.TRISB15 = 0;
    TRISBbits.TRISB14 = 0;
    LATCbits.LATC3=0;

    //Main loop
    while (1) {
        oledC_BitBangCommand(OLEDC_CMD_SET_DISPLAY_MODE_INVERSE);
        DELAY_milliseconds(1000);
        oledC_BitBangCommand(OLEDC_CMD_SET_DISPLAY_MODE_ON);
        DELAY_milliseconds(1000);
    }

}

/**
 End of File
 */

