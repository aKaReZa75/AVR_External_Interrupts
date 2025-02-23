#include "aKaReZa.h"

#define RGB_R_Config  DDRB
#define RGB_R_Control PORTB
#define RGB_R_PIN     3

/**
 * @brief Interrupt Service Routine for INT1 (External Interrupt 1), triggered by SW2
 * 
 * @note **Important**: For the interrupt to work, `globalInt_Enable` must be called to enable global interrupts. 
 *       Alternatively, you can set the I-bit (Interrupt Enable) in the `SREG` (Status Register) manually by writing `1` to the I-bit.
 */
ISR(INT1_vect)
{
  bitToggle(RGB_R_Control, RGB_R_PIN);

  intFlag_clear(EIFR, INTF1);
};


int main(void)
{
  GPIO_Config_OUTPUT(RGB_R_Config, RGB_R_PIN);

  eINT1_Init(Initialize);

  /* Global interrupt enable */
  globalInt_Enable;
  while(1)
  {
    
  };
};