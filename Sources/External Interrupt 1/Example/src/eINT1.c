/**
 * @file     eINT1.c
 * @brief    External Interrupt 1 (INT1) Library for AVR Microcontrollers
 * @note     This file provides functions to manage External Interrupt 1 (INT1) on AVR 
 *           microcontrollers, specifically for the ATmega328 microcontroller.
 * 
 * @author   Hossein Bagheri
 * @github   https://github.com/aKaReZa75
 * 
 * @note     For detailed explanations of this library, along with additional notes and examples of usage, 
 *           please visit the following repository:
 *           https://github.com/aKaReZa75/AVR_External_Interrupts
 */

#include "eINT1.h"

/**
 * @brief Initializes External Interrupt 1 (INT1).
 * 
 * This function is used to initialize the External Interrupt 1 (INT1) based on
 * the input parameter _initStatus. The initialization will set the interrupt
 * configuration and enable or disable the interrupt accordingly.
 * 
 * @param _initStatus A boolean indicating whether to initialize (`Initialize`) or deinitialize (`deInitialize`) the ADC module.
 */
void eINT1_Init(bool _initStatus)
{
  if(_initStatus) 
  {    
    bitSet(EIMSK, INT1);  /**< Enable External Interrupt 1 (SW2) */
    /* Configure External Interrupt 1 to trigger on rising edge */
    bitSet(EICRA, ISC11);
    bitSet(EICRA, ISC10); 
    intFlag_clear(EIFR, INTF1); /**< Clear the interrupt flag for INT1 */
  }
  else
  {
    /* Disable eINT1 and reset configuration */  
    bitClear(EIMSK, INT1); 
    bitClear(EICRA, ISC11);
    bitClear(EICRA, ISC10); 
  };
};
