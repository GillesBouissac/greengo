#include <unity.h>
#include "electronics.hpp"
#include "cbuffer.hpp"
#include "arduino_emulator.hpp"

namespace ElectronicsTest {

    void sampleAnalogInput_ShouldFillBufferWithReads() {
        CircularBuffer buffer;
        clearExpectedReads(A0);
        // Expect 10 reads of 500
        for (int i = 0; i < BUFFER_SIZE; i++) {
            expectRead(A0, 500);
        }
        sampleAnalogInput(A0, &buffer);
        TEST_ASSERT_EQUAL_INT(BUFFER_SIZE, buffer.count);
        // Since analogRead adds noise +/-10, average should be around 500
        ulong average = CircularBufferAverage(&buffer);
        TEST_ASSERT_UINT_WITHIN(10, 500, average);
    }

    void sampleAnalogInput_ShouldHandleDifferentValues() {
        CircularBuffer buffer;
        clearExpectedReads(A1);
        expectRead(A1, 100);
        expectRead(A1, 200);
        expectRead(A1, 300);
        expectRead(A1, 400);
        expectRead(A1, 500);
        sampleAnalogInput(A1, &buffer);
        TEST_ASSERT_EQUAL_INT(BUFFER_SIZE, buffer.count);
        // Check some values with noise tolerance
        TEST_ASSERT_UINT_WITHIN(10, 100, CircularBufferGet(&buffer, 0));
        TEST_ASSERT_UINT_WITHIN(10, 200, CircularBufferGet(&buffer, 1));
        TEST_ASSERT_UINT_WITHIN(10, 300, CircularBufferGet(&buffer, 2));
    }

    void run_tests() {
        RUN_TEST(sampleAnalogInput_ShouldFillBufferWithReads);
        RUN_TEST(sampleAnalogInput_ShouldHandleDifferentValues);
    }
}