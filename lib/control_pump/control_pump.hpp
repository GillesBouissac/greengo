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
