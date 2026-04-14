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
#include "cbuffer.hpp"

namespace CircularBufferTest {

    CircularBuffer buff;

    void CircularBuffer_ShouldBeEmptyAfterInit() {
        CircularBufferInit(&buff);
        TEST_ASSERT_TRUE(CircularBufferEmpty(&buff));
    }

    void CircularBuffer_ShouldNotBeEmptyAfterNewElements() {
        CircularBufferInit(&buff);
        CircularBufferAdd(&buff, 42);
        TEST_ASSERT_FALSE(CircularBufferEmpty(&buff));
        TEST_ASSERT_EQUAL_INT(1, buff.count);
        TEST_ASSERT_EQUAL_INT(42, CircularBufferGet(&buff, 0));
    }

    void CircularBufferGet_ShouldReturnElementAtSpecifiedIndex() {
        CircularBufferInit(&buff);
        // Add HISTORY_DEPTH elements
        for (int i = 0; i < BUFFER_SIZE; i++) {
            CircularBufferAdd(&buff, i);
        }
        TEST_ASSERT_EQUAL_INT(BUFFER_SIZE, buff.count);
        TEST_ASSERT_EQUAL_INT(0, CircularBufferGet(&buff, 0));
        
        // Add one more element - count should not exceed HISTORY_DEPTH
        CircularBufferAdd(&buff, 99);
        TEST_ASSERT_EQUAL_INT(BUFFER_SIZE, buff.count);
        
        // Verify that the buffer wrapped around correctly
        TEST_ASSERT_EQUAL_INT(1, CircularBufferGet(&buff, 0));
    }

    void CircularBufferGet_ShouldReadElementSuccessfully() {
        CircularBufferInit(&buff);
        CircularBufferAdd(&buff, 10);
        TEST_ASSERT_EQUAL_INT(10, CircularBufferGet(&buff, 0));

        CircularBufferAdd(&buff, 20);
        TEST_ASSERT_EQUAL_INT(10, CircularBufferGet(&buff, 0));
        TEST_ASSERT_EQUAL_INT(20, CircularBufferGet(&buff, 1));

        CircularBufferAdd(&buff, 30);
        TEST_ASSERT_EQUAL_INT(10, CircularBufferGet(&buff, 0));
        TEST_ASSERT_EQUAL_INT(20, CircularBufferGet(&buff, 1));
        TEST_ASSERT_EQUAL_INT(30, CircularBufferGet(&buff, 2));

        // Out of range
        TEST_ASSERT_EQUAL_INT(0, CircularBufferGet(&buff, 3));
        TEST_ASSERT_EQUAL_INT(0, CircularBufferGet(&buff, -1));

        // Force rotation
        for (int i = 4; i <= BUFFER_SIZE+4; i++) {
            CircularBufferAdd(&buff, i * 10);
        }
        TEST_ASSERT_EQUAL_INT(50, CircularBufferGet(&buff, 0));
        TEST_ASSERT_EQUAL_INT(140, CircularBufferGet(&buff, BUFFER_SIZE-1));
    }

    void CircularBufferAverage_ShouldCalculateAverageCorrectly() {
        CircularBufferInit(&buff);
        // Test empty buffer
        TEST_ASSERT_EQUAL_INT(0, CircularBufferAverage(&buff));

        // Add one value
        CircularBufferAdd(&buff, 10);
        TEST_ASSERT_EQUAL_INT(10, CircularBufferAverage(&buff));

        // Add another value
        CircularBufferAdd(&buff, 20);
        TEST_ASSERT_EQUAL_INT(15, CircularBufferAverage(&buff)); // (10 + 20) / 2

        // Add a third value
        CircularBufferAdd(&buff, 30);
        TEST_ASSERT_EQUAL_INT(20, CircularBufferAverage(&buff)); // (10 + 20 + 30) / 3

        // Fill the buffer and test average
        for (int i = 4; i <= BUFFER_SIZE; i++) {
            CircularBufferAdd(&buff, i * 10);
        }
        // Expected average is (10 + 100) / 2 = 55
        TEST_ASSERT_EQUAL_INT(55, CircularBufferAverage(&buff));
    }

    void CircularBufferInit_ShouldCleanBufferSuccessfully() {
        CircularBufferInit(&buff);
        for (uint8_t i = 0; i < BUFFER_SIZE/2; i++) {
            CircularBufferAdd(&buff, i);
        }
        TEST_ASSERT_FALSE(CircularBufferEmpty(&buff));
        CircularBufferInit(&buff);
        TEST_ASSERT_TRUE(CircularBufferEmpty(&buff));
    }

    void run_tests() {
        RUN_TEST(CircularBuffer_ShouldBeEmptyAfterInit);
        RUN_TEST(CircularBuffer_ShouldNotBeEmptyAfterNewElements);
        RUN_TEST(CircularBufferGet_ShouldReturnElementAtSpecifiedIndex);
        RUN_TEST(CircularBufferGet_ShouldReadElementSuccessfully);
        RUN_TEST(CircularBufferAverage_ShouldCalculateAverageCorrectly);
        RUN_TEST(CircularBufferInit_ShouldCleanBufferSuccessfully);
    }
}
