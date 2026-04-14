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
#include <unity.h>
#include <stdlib.h>
#include "electronics.hpp"
#include "control_cheeks.hpp"
#include "greengo_common.hpp"
#include "arduino_emulator.hpp"

namespace ControlCheeksTest {

    void readCheeksPower_ShouldReturnAverageOfSamples() {
        clearExpectedReads(A0);
        for (int i = 0; i < BUFFER_SIZE; i++) {
            expectRead(A0, 500 + random() % 21 - 10); // Base value with noise
        }
        ulong result = readCheeksPower(A0);
        // Since analogRead adds noise +/-10, average should be around 500
        TEST_ASSERT_UINT_WITHIN(10, 500, result); // Allow some margin for noise
    }

    void readCheeksBlinkFrequency_ShouldReturnAverageOfSamples() {
        clearExpectedReads(A1);
        for (int i = 0; i < BUFFER_SIZE; i++) {
            expectRead(A1, 200 + random() % 21 - 10); // Base value with noise
        }
        ulong result = readCheeksBlinkFrequency(A1);
        TEST_ASSERT_UINT_WITHIN(10, 200, result);
    }

    void switchOffCheeks_ShouldReturnZero() {
        uint result = switchOffCheeks();
        TEST_ASSERT_EQUAL_INT(0, result);
        // Note: start_time is set to millis(), but since it's static, hard to test directly
    }

    void computeCheeksPower_ShouldWorkWithMaxPowerAndMinFreq() {
        // Set controls to max power and min frequency (fast blink)
        ulong power_control = ANALOG_READ_MAX; // 1024
        ulong blink_freq_control = 0; // min freq, fastest blink
        uint result = computeCheeksPower(power_control, blink_freq_control);
        // Should be between LED_POWER_MIN and 255
        TEST_ASSERT_GREATER_OR_EQUAL_INT(LED_POWER_MIN, result);
        TEST_ASSERT_LESS_OR_EQUAL_INT(255, result);
    }

    void computeCheeksPower_ShouldWorkWithMinPower() {
        ulong power_control = 0;
        ulong blink_freq_control = ANALOG_READ_MAX;
        uint result = computeCheeksPower(power_control, blink_freq_control);
        TEST_ASSERT_EQUAL_INT(LED_POWER_MIN, result); // Should be min power
    }

    void run_tests() {
        RUN_TEST(readCheeksPower_ShouldReturnAverageOfSamples);
        RUN_TEST(readCheeksBlinkFrequency_ShouldReturnAverageOfSamples);
        RUN_TEST(switchOffCheeks_ShouldReturnZero);
        RUN_TEST(computeCheeksPower_ShouldWorkWithMaxPowerAndMinFreq);
        RUN_TEST(computeCheeksPower_ShouldWorkWithMinPower);
    }
}
