// BranchingFunctionsDelays.c Lab 6
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to 
// toggle an LED while a button is pressed and 
// turn the LED on when the button is released.  
// This lab will use the hardware already built into the LaunchPad.
// Daniel Valvano, Jonathan Valvano
// January 8, 2014

// built-in connection: PF0 connected to negative logic momentary switch, SW2
// built-in connection: PF1 connected to red LED
// built-in connection: PF2 connected to blue LED
// built-in connection: PF3 connected to green LED
// built-in connection: PF4 connected to negative logic momentary switch, SW1

#include "TExaS.h"

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void PortF_Init(void);
void Delay100ms(U64 time)

int main(void){ 
    volatile U64 delay;
  
    TExaS_Init(SW_PIN_PF4, LED_PIN_PF2);  // activate grader and set system clock to 80 MHz
    // initialization goes here
    
    PortF_Init(); 
    EnableInterrupts();           // enable interrupts for the grader
    while(1){
      // body goes here
    }
}

void PortF_Init(void) { 
    SYSCTL_RCGC2_R     = SYSCTL_RCGC2_GPIOF;
    Delay100ms(0x1);        
    GPIO_PORTF_LOCK_R  = 0x4C4F434B;  
    GPIO_PORTF_CR_R    = 0x14;        
    GPIO_PORTF_AMSEL_R = 0x0;
    GPIO_PORTF_DIR_R   = 0x04;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
    GPIO_PORTF_AFSEL_R = 0x00;          // 6) no alternate function
    GPIO_PORTF_PUR_R   = 0x10;          // enable pullup resistors on PF4,PF0       
    GPIO_PORTF_DEN_R   = 0x14;          // 7) enable digital pins PF4-PF0 
    GPIO_PORTF_DATA_R  = 0x04; 
}

void Delay100ms(U64 time){
  unsigned long i;
  while(time > 0){
    i = 1333333;  
    while(i > 0){
      i = i - 1;
    }
    time = time - 1; 
  }
}