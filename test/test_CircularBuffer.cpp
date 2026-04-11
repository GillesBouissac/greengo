#include <unity.h>
#include "cbuffer.hpp"

CircularBuffer buff;

void setUp(void) {
    CircularBufferInit(&buff);
}

void tearDown(void) {
    CircularBufferEmpty(&buff);
}

void test_circular_buffer_empty_after_init() {
    TEST_ASSERT_TRUE(CircularBufferEmpty(&buff));
}

void test_circular_buffer_not_empty_after_new_element_added() {
    CircularBufferAdd(&buff, 42);
    TEST_ASSERT_FALSE(CircularBufferEmpty(&buff));
    TEST_ASSERT_EQUAL_UINT(1, buff.count);
    TEST_ASSERT_EQUAL_UINT(42, CircularBufferGet(&buff, 0));
}

void test_circular_buffer_reports_full_correctly() {
    // Add HISTORY_DEPTH elements
    for (int i = 0; i < HISTORY_DEPTH; i++) {
        CircularBufferAdd(&buff, i);
    }
    TEST_ASSERT_EQUAL_UINT(HISTORY_DEPTH, buff.count);
    TEST_ASSERT_EQUAL_UINT(0, CircularBufferGet(&buff, 0));
    
    // Add one more element - count should not exceed HISTORY_DEPTH
    CircularBufferAdd(&buff, 99);
    TEST_ASSERT_EQUAL_UINT(HISTORY_DEPTH, buff.count);
    
    // Verify that the buffer wrapped around correctly
    TEST_ASSERT_EQUAL_UINT(1, CircularBufferGet(&buff, 0));
}

void test_circular_buffer_read_element_succesful() {
    CircularBufferAdd(&buff, 10);
    TEST_ASSERT_EQUAL_UINT(10, CircularBufferGet(&buff, 0));

    CircularBufferAdd(&buff, 20);
    TEST_ASSERT_EQUAL_UINT(10, CircularBufferGet(&buff, 0));
    TEST_ASSERT_EQUAL_UINT(20, CircularBufferGet(&buff, 1));

    CircularBufferAdd(&buff, 30);
    TEST_ASSERT_EQUAL_UINT(10, CircularBufferGet(&buff, 0));
    TEST_ASSERT_EQUAL_UINT(20, CircularBufferGet(&buff, 1));
    TEST_ASSERT_EQUAL_UINT(30, CircularBufferGet(&buff, 2));

    // Out of range
    TEST_ASSERT_EQUAL_UINT(0, CircularBufferGet(&buff, 3));
    TEST_ASSERT_EQUAL_UINT(0, CircularBufferGet(&buff, -1));

    // Force rotation
    for (int i = 4; i <= HISTORY_DEPTH+4; i++) {
        CircularBufferAdd(&buff, i * 10);
    }
    TEST_ASSERT_EQUAL_UINT(50, CircularBufferGet(&buff, 0));
    TEST_ASSERT_EQUAL_UINT(140, CircularBufferGet(&buff, HISTORY_DEPTH-1));
}

void test_circular_buffer_average() {
    // Test empty buffer
    TEST_ASSERT_EQUAL_UINT(0, CircularBufferAverage(&buff));

    // Add one value
    CircularBufferAdd(&buff, 10);
    TEST_ASSERT_EQUAL_UINT(10, CircularBufferAverage(&buff));

    // Add another value
    CircularBufferAdd(&buff, 20);
    TEST_ASSERT_EQUAL_UINT(15, CircularBufferAverage(&buff)); // (10 + 20) / 2

    // Add a third value
    CircularBufferAdd(&buff, 30);
    TEST_ASSERT_EQUAL_UINT(20, CircularBufferAverage(&buff)); // (10 + 20 + 30) / 3

    // Fill the buffer and test average
    for (int i = 4; i <= HISTORY_DEPTH; i++) {
        CircularBufferAdd(&buff, i * 10);
    }
    // Expected average is (10 + 100) / 2 = 55
    TEST_ASSERT_EQUAL_UINT(55, CircularBufferAverage(&buff));
}

void test_circular_buffer_cleaned_succesfully() {
    for (uint8_t i = 0; i < HISTORY_DEPTH/2; i++) {
        CircularBufferAdd(&buff, i);
    }
    TEST_ASSERT_FALSE(CircularBufferEmpty(&buff));
    CircularBufferInit(&buff);
    TEST_ASSERT_TRUE(CircularBufferEmpty(&buff));
}

int main( int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_circular_buffer_empty_after_init);
    RUN_TEST(test_circular_buffer_not_empty_after_new_element_added);
    RUN_TEST(test_circular_buffer_reports_full_correctly);
    RUN_TEST(test_circular_buffer_read_element_succesful);
    RUN_TEST(test_circular_buffer_average);
    RUN_TEST(test_circular_buffer_cleaned_succesfully);

    UNITY_END();
}
