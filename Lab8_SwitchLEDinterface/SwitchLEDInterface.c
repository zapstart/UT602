// ***** 0. Documentation Section *****
// SwitchLEDInterface.c for Lab 8
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to toggle an LED
// while a button is pressed and turn the LED on when the
// button is released.  This lab requires external hardware
// to be wired to the LaunchPad using the prototyping board.
// December 28, 2014
//      Jon Valvano and Ramesh Yerraballi

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"
#include "..\Header\standard_define.h"

// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void GPIO_port_init(void);
void Delay_1ms(U64 time);

// ***** 3. Subroutines Section *****

// PE0, PB0, or PA2 connected to positive logic momentary switch using 10k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic
// shown in Lab8_artist.sch (PCB Artist schematic file) or 
// Lab8_artist.pdf (compatible with many various readers like Adobe Acrobat).
int main(void){ 
    //**********************************************************************
    // The following version tests input on PE0 and output on PE1
    //**********************************************************************
    TExaS_Init(SW_PIN_PE0, LED_PIN_PE1);  // activate grader and set system clock to 80 MHz
    GPIO_port_init(); 
    EnableInterrupts();           // enable interrupts for the grader
    
    GPIO_PORTE_DATA_R |= 0x02; 
    while(1){
        Delay_1ms(100);
        if (GPIO_PORTE_DATA_R & 0x01) {
            GPIO_PORTE_DATA_R ^= 0x02;
        }
        else {
           GPIO_PORTE_DATA_R |= 0x02; 
        }
    }
}

void GPIO_port_init(void) {
    U64 delay;

    // init GPIO port E0 and E1
    SYSCTL_RCGC2_R     |= 0x10;
    delay = SYSCTL_RCGC2_R; 
    GPIO_PORTE_AMSEL_R &= ~0x03;
    GPIO_PORTE_DIR_R   |= 0x02;          
    GPIO_PORTE_DIR_R   &= ~0x01;          
    GPIO_PORTE_AFSEL_R &= ~0x03;          
    GPIO_PORTE_DEN_R   |= 0x03;        
}

void Delay_1ms(U64 time){
    U64 i;

    while(time > 0){
        i = 13333;
        while(i > 0){
            i = i - 1;
        }
        time = time - 1; 
    }
}
