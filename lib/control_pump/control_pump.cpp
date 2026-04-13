#include "control_pump.hpp"
#include "electronics.hpp"

ulong readPumpPower(int pin) {
    static CircularBuffer pump_power_buffer;
    sampleAnalogInput(pin, &pump_power_buffer);
    return CircularBufferAverage(&pump_power_buffer);
}

uint switchOffPump() {
    return 0;
}

uint computePumpRpm(ulong control) {
    return PUMP_POWER_MIN + (control*PUMP_POWER_RANGE)/ANALOG_READ_MAX;
}
