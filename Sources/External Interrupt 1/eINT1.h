/**
 * @file     eINT1.h
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

#ifndef _eINT1_H_
#define _eINT1_H_

#include "aKaReZa.h"


/**
 * @brief Initializes External Interrupt 1 (INT1).
 * 
 * @param _initStatus A boolean indicating whether to initialize (`Initialize`) or deinitialize (`deInitialize`) the ADC module.
 */
void eINT1_Init(bool _initStatus);

#endif