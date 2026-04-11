#include <stdio.h>
#include "Arduino.h"
#include "unity_config.h"

void unityOutputStart() {
    Serial.begin(115200);
}

void unityOutputChar(char c) {
    Serial.write(c);
}

void unityOutputFlush() {
    Serial.flush();
}

void unityOutputComplete() {
    Serial.end();
}

void setup()
{
    while (!Serial) {
        delay(3000);
    }
}
