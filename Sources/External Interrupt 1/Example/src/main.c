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

  eINT1_Init(Initialize);

  /* Global interrupt enable */
  globalInt_Enable;
  while(1)
  {
    
  };
};