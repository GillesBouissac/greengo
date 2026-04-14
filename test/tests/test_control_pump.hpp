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
#include "electronics.hpp"
#include "control_pump.hpp"
#include "greengo_common.hpp"
#include "arduino_emulator.hpp"

namespace ControlPumpTest {

    void readPumpPower_ShouldReturnAverageOfSamples() {
        clearExpectedReads(A2);
        for (int i = 0; i < BUFFER_SIZE; i++) {
            expectRead(A2, 768 + random() % 11 - 5); // Base value with noise
        }
        ulong result = readPumpPower(A2);
        // Average should be around 768
        TEST_ASSERT_UINT_WITHIN(5, 768, result);
    }

    void switchOffPump_ShouldReturnZero() {
        uint result = switchOffPump();
        TEST_ASSERT_EQUAL_INT(0, result);
    }

    void computePumpRpm_ShouldWorkWithMaxControl() {
        ulong control = ANALOG_READ_MAX; // 1024
        uint result = computePumpRpm(control);
        TEST_ASSERT_EQUAL_INT(PUMP_POWER_MAX, result); // Should be max power
    }

    void computePumpRpm_ShouldWorkWithMinControl() {
        ulong control = 0;
        uint result = computePumpRpm(control);
        TEST_ASSERT_EQUAL_INT(PUMP_POWER_MIN, result); // Should be min power
    }

    void computePumpRpm_ShouldWorkWithMidControl() {
        ulong control = ANALOG_READ_MAX / 2; // 512
        uint result = computePumpRpm(control);
        // Should be around PUMP_POWER_MIN + PUMP_POWER_RANGE / 2
        uint expected = PUMP_POWER_MIN + PUMP_POWER_RANGE / 2;
        TEST_ASSERT_UINT_WITHIN(1, expected, result);
    }

    void run_tests() {
        RUN_TEST(readPumpPower_ShouldReturnAverageOfSamples);
        RUN_TEST(switchOffPump_ShouldReturnZero);
        RUN_TEST(computePumpRpm_ShouldWorkWithMaxControl);
        RUN_TEST(computePumpRpm_ShouldWorkWithMinControl);
        RUN_TEST(computePumpRpm_ShouldWorkWithMidControl);
    }
}