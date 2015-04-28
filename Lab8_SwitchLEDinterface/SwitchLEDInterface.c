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
  
	
EnableInterrupts();           // enable interrupts for the grader
    while(1){
        
    }
  
}

void GPIO_port_init(void) {
    SYSCTL_RCGC2_R     = ;
    
    // GPIO port E
    GPIO_PORTE_LOCK_R  = 0x4C4F434B;  
    GPIO_PORTE_CR_R    = 0x14;       
    GPIO_PORTE_AMSEL_R = 0x0;
    GPIO_PORTE_DIR_R   = 0x04;          
    GPIO_PORTE_AFSEL_R = 0x00;          
    GPIO_PORTE_PUR_R   = 0x10;         
    GPIO_PORTE_DEN_R   = 0x14;        
    GPIO_PORTE_DATA_R  = 0x00; 
    
    // GPIO port B
    GPIO_PORTB_LOCK_R  = 0x4C4F434B;  
    GPIO_PORTB_CR_R    = 0x14;       
    GPIO_PORTB_AMSEL_R = 0x0;
    GPIO_PORTB_DIR_R   = 0x04;          
    GPIO_PORTB_AFSEL_R = 0x00;          
    GPIO_PORTB_PUR_R   = 0x10;         
    GPIO_PORTB_DEN_R   = 0x14;        
    GPIO_PORTB_DATA_R  = 0x00; 
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
