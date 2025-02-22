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
    bitSet(EIMSK, INT0);  /**< Enable External Interrupt 0 (SW3) */
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
