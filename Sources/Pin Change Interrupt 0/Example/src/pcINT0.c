/**
 * @file     pcINT0.c
 * @brief    Pin Change 0 (PCINT0) Library for AVR Microcontrollers
 * @note     This file provides functions to manage Pin Change Interrupt 0 (pcINT0) 
 *           on AVR microcontrollers, specifically for the ATmega328 microcontroller.
 * 
 * @author   Hossein Bagheri
 * @github   https://github.com/aKaReZa75
 * 
 * @note     For detailed explanations of this library, along with additional notes and examples of usage, 
 *           please visit the following repository:
 *           https://github.com/aKaReZa75/AVR_External_Interrupts
 */

#include "pcINT0.h"


/**
 * @brief Initializes Pin Change Interrupt 0 (PCINT0).
 * 
 * This function is used to initialize the Pin Change Interrupt 0 (PCINT0) based on
 * the input parameter _initStatus. The initialization will set the interrupt
 * configuration and enable or disable the interrupt accordingly.
 * 
 * @param _initStatus A boolean indicating whether to initialize (`Initialize`) or deinitialize (`deInitialize`) the ADC module.
 */
void pcINT0_Init(bool _initStatus)
{
  if(_initStatus) 
  {    
    bitSet(PCICR, PCIE0);   /**< Enable Pin Change Interrupt for Port B (PCINT0) */
    bitSet(PCMSK0, PCINT5); /**< Enable Pin Change Interrupt for Pin 5 on Port B (SW1) */
    intFlag_clear(PCIFR, PCIE0);  /**< Clear the interrupt flag for PCINT0, ensuring no pending interrupts at startup */
  }
  else
  {
    /* Disable pcINT1 and reset configuration */  
    bitClear(PCICR, PCIE0); 
    bitClear(PCMSK0, PCINT5);
  };
};
