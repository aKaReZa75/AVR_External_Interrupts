/**
 * @file     eINT0.h
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

#ifndef _eINT0_H_
#define _eINT0_H_

#include "aKaReZa.h"


/**
 * @brief Initializes External Interrupt 0 (INT0).
 * 
 * @param _initStatus A boolean indicating whether to initialize (`Initialize`) or deinitialize (`deInitialize`) the ADC module.
 */
void eINT0_Init(bool _initStatus);

#endif