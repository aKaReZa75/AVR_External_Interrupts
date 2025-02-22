/**
 * @file     pcINT0.h
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

#ifndef _pcINT0_H_
#define _pcINT0_H_

#include "aKaReZa.h"


/**
 * @brief Initializes Pin Change Interrupt 0 (PCINT0).
 * 
 * @param _initStatus A boolean indicating whether to initialize (`Initialize`) or deinitialize (`deInitialize`) the Interrupt.
 */
void pcINT0_Init(bool _initStatus);

#endif