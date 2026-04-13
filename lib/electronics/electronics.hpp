#ifndef electronics_hpp
#define electronics_hpp

#include "cbuffer.hpp"

#define ANALOG_READ_MAX   1024
#define PWM_OUTPUT_MAX    255

/// @brief Reads the given analog pin multiple time to fill the circular buffer
/// @param pin The analog pin to read the value from
/// @param pbuffer The circular buffer to store the read values
void sampleAnalogInput(int pin, CircularBuffer* pbuffer);

#endif /* electronics_hpp */
