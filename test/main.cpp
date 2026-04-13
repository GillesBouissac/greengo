#include <unity.h>
#include <string.h>
#include <stdlib.h>
#include "greengo_common.hpp"

#include "tests/test_cbuffer.hpp"
#include "tests/test_control_cheeks.hpp"
#include "tests/test_control_pump.hpp"
#include "tests/test_electronics.hpp"

#define RUN_TEST_GROUP(TEST) \
    if (!std::getenv("TEST_GROUP") || (strcmp(#TEST, std::getenv("TEST_GROUP")) == 0)) { \
        TEST::run_tests(); \
    }

void setUp(void) {
    // This is run before EACH TEST
}

void tearDown(void) {
    // This is run after EACH TEST
}

int main(int argc, char **argv)
{

    UNITY_BEGIN();

    RUN_TEST_GROUP(CircularBufferTest);
    RUN_TEST_GROUP(ControlCheeksTest);
    RUN_TEST_GROUP(ControlPumpTest);
    RUN_TEST_GROUP(ElectronicsTest);

    UNITY_END();

    return 0;
}
