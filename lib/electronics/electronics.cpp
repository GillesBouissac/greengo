#include "electronics.hpp"
#include "cbuffer.hpp"

// ----------------------------------------
// Analog input smoothing
// ----------------------------------------
// Read a value and store it in the given history array
// The returned value is the average of all inputs in the array
void sampleAnalogInput(int pin, CircularBuffer* pbuffer) {
    CircularBufferInit (pbuffer);
    for (int i=0; i<BUFFER_SIZE; i++) {
        CircularBufferAdd (pbuffer, analogRead (pin));
    }
}
