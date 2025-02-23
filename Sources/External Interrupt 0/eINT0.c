/**
 * @file     eINT0.c
 * @brief    External Interrupt 0 (INT0) Library for AVR Microcontrollers
 * @note     This file provides functions to manage External Interrupt 0 (INT0) on AVR 
 *           microcontrollers, specifically for the ATmega328 microcontroller.
 * 
 * @author   Hossein Bagheri
 * @github   https://github.com/aKaReZa75
 * 
 * @note     For detailed explanations of this library, along with additional notes and examples of usage, 
 *           please visit the following repository:
 *           https://github.com/aKaReZa75/AVR_External_Interrupts
 */

#include "eINT0.h"


/**
 * @brief Interrupt Service Routine for INT0 (External Interrupt 0)
 * 
 * @note **Important**: For the interrupt to work, `globalInt_Enable` must be called to enable global interrupts. 
 *       Alternatively, you can set the I-bit (Interrupt Enable) in the `SREG` (Status Register) manually by writing `1` to the I-bit.
 */
ISR(INT0_vect)
{
  /* Place your code here */

  intFlag_clear(EIFR, INTF0);
};


/**
 * @brief Initializes External Interrupt 0 (INT0).
 * 
 * This function is used to initialize the External Interrupt 0 (INT0) based on
 * the input parameter _initStatus. The initialization will set the interrupt
 * configuration and enable or disable the interrupt accordingly.
 * 
 * @param _initStatus A boolean indicating whether to initialize (`Initialize`) or deinitialize (`deInitialize`) the Interrupt.
 */
void eINT0_Init(bool _initStatus)
{
  if(_initStatus) 
  {    
    bitSet(EIMSK, INT0);  /**< Enable External Interrupt 0 */
    /* Configure External Interrupt 0 to trigger on falling edge */
    bitSet(EICRA, ISC01);
    bitClear(EICRA, ISC00); 
    intFlag_clear(EIFR, INTF0); /**< Clear the interrupt flag for INT0 */
  }
  else
  {
    /* Disable eINT0 and reset configuration */  
    bitClear(EIMSK, INT0);   
    bitClear(EICRA, ISC01);
    bitClear(EICRA, ISC00);
  };
};
