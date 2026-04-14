/*
 * Copyright (c) 2026 Gilles Bouissac
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#ifndef control_cheeks_hpp
#define control_cheeks_hpp

#include "greengo_common.hpp"

#define MS_PER_CYCLE_MIN  400
#define MS_PER_CYCLE_MAX  5000
#define LED_POWER_MIN     1

/// @brief Reads the potentiometer controlling for the cheeks LED power and returns the corresponding power level
/// @param pin The analog pin to read the potentiometer value from
/// @return The corresponding power level
ulong readCheeksPower(int pin);

/// @brief Reads the potentiometer controlling the cheeks LED blink frequency and returns the corresponding frequency
/// @param pin The analog pin to read the potentiometer value from
/// @return The corresponding frequency, the lower the value, the faster the blinking
ulong readCheeksBlinkFrequency(int pin);

/// @brief Switches off the cheeks LED
uint switchOffCheeks();

/// @brief Compputes the output power of the PWM pin controlling the cheeks LED brightness
/// @param power_control The control value read from the power potentiometer, between 0 and ANALOG_READ_MAX
/// @param blink_frequency_control The control value read from the blink frequency potentiometer, between 0 and ANALOG_READ_MAX
/// @return The corresponding PWM output power
uint computeCheeksPower(ulong power_control, ulong blink_frequency_control);

#endif /* control_cheeks_hpp */
