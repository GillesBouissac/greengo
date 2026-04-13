#include "control_cheeks.hpp"
#include "electronics.hpp"

ulong readCheeksPower(int pin) {
    static CircularBuffer cheeks_power_buffer;
    sampleAnalogInput(pin, &cheeks_power_buffer);
    return CircularBufferAverage(&cheeks_power_buffer);
}

ulong readCheeksBlinkFrequency(int pin) {
    static CircularBuffer cheeks_blink_buffer;
    sampleAnalogInput(pin, &cheeks_blink_buffer);
    return CircularBufferAverage(&cheeks_blink_buffer);
}

static ulong start_time = 0;
uint switchOffCheeks() {
    start_time = millis();
    return 0;
}

uint computeCheeksPower(ulong power_control, ulong blink_frequency_control) {
    ulong led_max_power = max(min(255,(power_control*255)/ANALOG_READ_MAX),LED_POWER_MIN);
    ulong ms_per_cycle = MS_PER_CYCLE_MIN + (blink_frequency_control*MS_PER_CYCLE_MAX)/ANALOG_READ_MAX;
    ulong value_in_cycle = (millis()-start_time) % ms_per_cycle;
    float angle = (2 * PI * value_in_cycle / ms_per_cycle) + PI;

    return LED_POWER_MIN + (led_max_power-LED_POWER_MIN)*(cos(angle)+1)/2;
}
