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
#ifndef control_pump_hpp
#define control_pump_hpp

#include "greengo_common.hpp"

#define PUMP_VOLT_MIN     7
#define PUMP_VOLT_MAX     12
#define PUMP_POWER_MAX    PWM_OUTPUT_MAX
#define PUMP_POWER_MIN    (255*PUMP_VOLT_MIN)/PUMP_VOLT_MAX
#define PUMP_POWER_RANGE  (PUMP_POWER_MAX-PUMP_POWER_MIN)

/// @brief Reads the potentiometer value for the pump power and returns the corresponding power level
/// @param pin The analog pin to read the potentiometer value from
/// @return The corresponding power level
ulong readPumpPower(int pin);

/// @brief Switches off the pump
uint switchOffPump();

/// @brief Compputes the output power of the PWM pin controlling the pump rotation
/// @param control The control value read from the potentiometer, between 0 and ANALOG_READ_MAX
/// @return The corresponding PWM output power
uint computePumpRpm(ulong control);

#endif /* control_pump_hpp */
