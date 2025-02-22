#include "aKaReZa.h"

#define RGB_R_Config  DDRB
#define RGB_R_Control PORTB
#define RGB_R_PIN     3

/* Interrupt Service Routine for Pin Change Interrupt 0 (PCINT0) triggered by SW1 */
ISR(PCINT0_vect) 
{
  bitToggle(RGB_R_Control, RGB_R_PIN);  /**< Toggle the Red LED state (turn it on/off) */
  
  intFlag_clear(PCIFR, PCIE0);  /**< Clear the interrupt flag for PCINT0 to allow further interrupts */
};

int main(void)
{
  GPIO_Config_OUTPUT(RGB_R_Config, RGB_R_PIN);

  bitSet(PCICR, PCIE0);   /**< Enable Pin Change Interrupt for Port B (PCINT0) */
  bitSet(PCMSK0, PCINT5); /**< Enable Pin Change Interrupt for Pin 5 on Port B (SW1) */

  intFlag_clear(PCIFR, PCIE0);  /**< Clear the interrupt flag for PCINT0, ensuring no pending interrupts at startup */

  /* Global interrupt enable */
  globalInt_Enable;
  while(1)
  {
    
  };
};