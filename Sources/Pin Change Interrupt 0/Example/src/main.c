#include "aKaReZa.h"

#define RGB_R_Config  DDRB
#define RGB_R_Control PORTB
#define RGB_R_PIN     3

/**
 * @brief Interrupt Service Routine for Pin Change Interrupt 0 (PCINT0), triggered by SW1
 *
 * @note **Important**: For the interrupt to work, `globalInt_Enable` must be called to enable global interrupts. 
 *       Alternatively, you can set the I-bit (Interrupt Enable) in the `SREG` (Status Register) manually by writing `1` to the I-bit.
 */
ISR(PCINT0_vect) 
{
  bitToggle(RGB_R_Control, RGB_R_PIN);  /**< Toggle the Red LED state (turn it on/off) */
  
  intFlag_clear(PCIFR, PCIE0);  /**< Clear the interrupt flag for PCINT0 to allow further interrupts */
};


int main(void)
{
  GPIO_Config_OUTPUT(RGB_R_Config, RGB_R_PIN);

  pcINT0_Init(Initialize);
  
  /* Global interrupt enable */
  globalInt_Enable;
  while(1)
  {
    
  };
};