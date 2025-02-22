#include "aKaReZa.h"

#define RGB_R_Config  DDRB
#define RGB_R_Control PORTB
#define RGB_R_PIN     3

/* Interrupt Service Routine for INT1 (External Interrupt 1), triggered by SW2 */
ISR(INT1_vect)
{
  bitToggle(RGB_R_Control, RGB_R_PIN);

  intFlag_clear(EIFR, INTF1);
};

int main(void)
{
  GPIO_Config_OUTPUT(RGB_R_Config, RGB_R_PIN);

  bitSet(EIMSK, INT1);  /**< Enable External Interrupt 1 (SW2) */
  /* Configure External Interrupt 1 to trigger on rising edge */
  bitSet(EICRA, ISC11);
  bitSet(EICRA, ISC10); 
  intFlag_clear(EIFR, INTF1); /**< Clear the interrupt flag for INT1 */

  /* Global interrupt enable */
  globalInt_Enable;
  while(1)
  {
    
  };
};