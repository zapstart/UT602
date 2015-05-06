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
typedef void (*p_LED_operation) (void);

typedef enum {
    INIT_s = 0,
    LED_000_s,
    LED_001_s,
    LED_010_s,
    LED_011_s,
    LED_100_s,
    LED_110_s,
    LED_111_s
} LED_state;

typedef const struct state {
    p_LED_operation LED_operation; 
    LED_state       Next[4];
} state_type;

void LED_000 (void) {

}

void LED_001 (void) {
}

void LED_010 (void) {
}

void LED_011 (void) {
}

void LED_100 (void) {
}

void LED_110 (void) {
}

void LED_111 (void) {
}

LED_state current_state = 

state_type FSM[7] = {
    {&LED_000, {LED_111_s, LED_111_s, LED_111_s, LED_111_S}},
    {&LED_001, {LED_001, LED_000, LED_000, LED_001}},
    {&LED_010, {LED_010, LED_000, LED_000, LED_010}},
    {&LED_100, {LED_100, LED_000, LED_000, LED_100}},
    {&LED_011, {LED_011, LED_001, LED_010, LED_011}},
    {&LED_110, {LED_110, LED_010, LED_100, LED_110}},
    {&LED_111, {LED_111, LED_011, LED_110, LED_111}}
};

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

