/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

#include <stdint.h>
#include "xc.h"

//------------------------------------------------------------------------------
//Main Function
//------------------------------------------------------------------------------
int main(void)
{
    int mask=0;
    int count=0, pot;
    
  
    
    //Initialize LED/Switch IO Direction (TRISx)
    TRISA|=(1<<11);
    TRISA&=~(1<<8);

    //Set RB12 (AN8) as Analog Input
    TRISB|=(1<<12);
    ANSB|=(1<<12);
    
    //Initialize A/D Circuit (AD1CON1)
    
    //TURN OFF 4-9 BITS IN AD1CON1
    mask=0X3F<<4;
    AD1CON1&=~mask;
    
    //TURN ON 10,15 ON AD1CON1
    mask&=(1<<10)|(1<<15);
    AD1CON1|=mask;
    
    AD1CON2=0;
    AD1CON3=0;
    AD1CON3=0X10FF;

    //Main loop
    while(1)
    {
        
        //Count presses on S1 in variable count (Light up LED1 each time S1 pressed)
        if (PORTA & (1<<11)){
            LATA &=~(1<<8);
            count++;
        }
        else
            LATA&=(1<<8);
        
        //Select AN8 for A/D conversion

        //Perform A/D Conversion

        //Put Result in variable pot
        pot /*= ???*/ ;
    }
}
