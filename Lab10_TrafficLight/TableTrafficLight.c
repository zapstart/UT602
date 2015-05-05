// ***** 0. Documentation Section *****
// TableTrafficLight.c for Lab 10
// Runs on LM4F120/TM4C123
// Index implementation of a Moore finite state machine to operate a traffic light.  
// Daniel Valvano, Jonathan Valvano
// December 29, 2014

// east/west red light connected to PB5
// east/west yellow light connected to PB4
// east/west green light connected to PB3
// north/south facing red light connected to PB2
// north/south facing yellow light connected to PB1
// north/south facing green light connected to PB0
// pedestrian detector connected to PE2 (1=pedestrian present)
// north/south car detector connected to PE1 (1=car present)
// east/west car detector connected to PE0 (1=car present)
// "walk" light connected to PF3 (built-in green LED)
// "don't walk" light connected to PF1 (built-in red LED)

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

// ***** 2. Global Declarations Section *****
#define init    0
#define goN     1
#define waitN   2
#define goE     3
#define waitE   4
#define walk    5
#define rushW   6
#define dontW   7

typedef const struct state {
    U32 output;
    U32 delay;
    U32 Next[8];
}traffic_light, *ptraffic_light;

traffic_light TL_FSM[x] = {
    {x, x, {}},
    {x, x, {}},
    {x, x, {}},
    {x, x, {}},
    {x, x, {}},
    {x, x, {}},
    {x, x, {}},
    {x, x, {}},
    {x, x, {}},
    {x, x, {}},
}

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

// ***** 3. Subroutines Section *****
void GPIO_INIT(void);
   
int main(void){ 
    TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210); 
 
    
    EnableInterrupts();
    while(1){
     
    }
}

void GPIO_INIT(void) {
    volatile U64 delay;
    
    SYSCTL_RCGC2_R |= 0x12;     
    delay = SYSCTL_RCGC2_R;           
    
    // init port B 
    GPIO_PORTB_AMSEL_R &= ~0xFF;        
    GPIO_PORTB_PCTL_R &= ~0xFF;   
    GPIO_PORTB_DIR_R |= 0x3F;          
    GPIO_PORTB_AFSEL_R &= 0xFF;        
    GPIO_PORTB_DEN_R |= 0x3F;          
    
    // init port E
    GPIO_PORTE_AMSEL_R &= ~0xFF;        
    GPIO_PORTE_PCTL_R &= ~0xFF;   
    GPIO_PORTE_DIR_R &= ~0x07;          
    GPIO_PORTE_AFSEL_R &= ~0xFF;        
    GPIO_PORTE_DEN_R |= 0x07;          

    // init port F 
    GPIO_PORTB_AMSEL_R &= ~0xFF;        
    GPIO_PORTB_PCTL_R &= ~0xFF;   
    GPIO_PORTB_DIR_R |= 0x0A;          
    GPIO_PORTB_AFSEL_R &= ~0xFF;        
    GPIO_PORTB_PUR_R |= 0x0A;          
    GPIO_PORTB_DEN_R |= 0x0A;          
}

