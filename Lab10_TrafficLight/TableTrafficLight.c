// ***** 0. Documentation Section *****
// TableTrafficLight.c for Lab 10
// Runs on LM4F120/TM4C123
// Index implementation of a Moore finite state machine to operate a traffic light.  
// Daniel Valvano, Jonathan Valvano
// December 29, 2014

// east/west red light connected to PB2
// east/west yellow light connected to PB1
// east/west green light connected to PB0
// north/south car detector connected to PE1 (1=car present)
// east/west car detector connected to PE0 (1=car present)

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

// ***** 2. Global Declarations Section *****
typedef void (*p_LED_operation)(void);

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
void DisableInterrupts(void); 
void EnableInterrupts(void);  
void delay_1ms(U32 time);
void delay_clk(U32 clk_cnt);
void LED_000(void);
void LED_001(void);
void LED_010(void);
void LED_011(void);
void LED_100(void);
void LED_110(void);
void LED_111(void);
void PLL_INIT(void);
void GPIO_INIT(void);
void SYSTICK_INIT(void);
void SYSTICK_INIT(void);
// ***** 3. Subroutines Section *****
   
int main(void){ 
    U32 sw_in;

    TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210); 
    EnableInterrupts();
    PLL_INIT(); 
    GPIO_INIT();
        
    LED_state current_state = LED_000_s; 
    while(1){
        sw_in = GPIO_PORTE_DATA_R & 0x03;
        (FSM[current_state].LED_operation)();
        current_state = FSM[current_state].Next[sw_in];
    }
}

void PLL_INIT(void) {
    SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)   // clear XTAL field, bits 10-6
                   + 0x00000540;   // 10101, configure for 16 MHz crystal
    // 0) Use RCC2
    SYSCTL_RCC2_R |=  0x80000000;  // USERCC2
    // 1) bypass PLL while initializing
    SYSCTL_RCC2_R |=  0x00000800;  // BYPASS2, PLL bypass
    // 2) select the crystal value and oscillator source
    SYSCTL_RCC2_R &= ~0x00000070;  // configure for main oscillator source
    // 3) activate PLL by clearing PWRDN
    SYSCTL_RCC2_R &= ~0x00002000;
    // 4) set the desired system divider
    SYSCTL_RCC2_R |= 0x40000000;   // use 400 MHz PLL
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000)  // clear system clock divider
                    + (4<<22);      // configure for 80 MHz clock
    // 5) wait for the PLL to lock by polling PLLLRIS
    while((SYSCTL_RIS_R&0x00000040)==0){};  // wait for PLLRIS bit
    // 6) enable use of PLL by clearing BYPASS
    SYSCTL_RCC2_R &= ~0x00000800;
}  
    
void GPIO_INIT(void) {
    volatile U64 delay;
    
    SYSCTL_RCGC2_R |= 0x42;     
    delay = SYSCTL_RCGC2_R;           
    
    // init port B 
    GPIO_PORTB_AMSEL_R &= ~0xFF;        
    GPIO_PORTB_PCTL_R &= ~0xFF;   
    GPIO_PORTB_DIR_R |= 0x07;          
    GPIO_PORTB_AFSEL_R &= ~0xFF;        
    GPIO_PORTB_DEN_R |= 0x07;          
    
    // init port F
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0xFF;
    GPIO_PORTF_PU_R |= 0x11; 
    GPIO_PORTF_AMSEL_R &= ~0xFF;        
    GPIO_PORTF_PCTL_R &= ~0xFF;   
    GPIO_PORTF_DIR_R &= ~0x11;          
    GPIO_PORTF_AFSEL_R &= ~0xFF;        
    GPIO_PORTF_DEN_R |= 0x11;          
}

void SYSTICK_INIT(void) {
  NVIC_ST_CTRL_R = 0;               
  NVIC_ST_CTRL_R = 0x00000005;      
}

void delay_1ms(U32 time){
    U32 i;
    
    for(i = 0; i < time; i++){
      delay_clk(80000);  
    }
}

void delay_clk(U32 clk_cnt) {
  NVIC_ST_RELOAD_R = clk_cnt - 1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
  while((NVIC_ST_CTRL_R & 0x00010000)==0); // wait for count flag
}

// LED: red, yellow, green
void LED_000 (void) {
    GPIO_PORTB_DATA_R &= ~0x07;
    delay_1ms(3);
}

void LED_001 (void) {
    GPIO_PORTB_DATA_R |= 0x01;
}

void LED_010 (void) {
    GPIO_PORTB_DATA_R |= 0x02;
}

void LED_011 (void) {
    GPIO_PORTB_DATA_R |= 0x03;
}

void LED_100 (void) {
    GPIO_PORTB_DATA_R |= 0x04;
}

void LED_110 (void) {
    GPIO_PORTB_DATA_R |= 0x06;
}

void LED_111 (void) {
    GPIO_PORTB_DATA_R |= 0x07;
}
