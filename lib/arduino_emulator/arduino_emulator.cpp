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
#ifndef ARDUINO

#include <map>
#include <chrono>
#include <thread>
#include <vector>
#include "arduino_emulator.hpp"

using namespace std;

Serial_ Serial;

static std::map<uint8_t, std::vector<int>> expectedMeasures = {
    {A0, {854}},
    {A1, {10}},
    {A2, {768}},
    {7, {HIGH}}
};

void clearExpectedReads(uint8_t pin) {
    expectedMeasures[pin].clear();
}

void expectRead(uint8_t pin, int value) {
    expectedMeasures[pin].push_back(value);
}

int pinRead(uint8_t pin, int min_val, int max_val) {
    int value;
    if (expectedMeasures.find(pin) != expectedMeasures.end() && !expectedMeasures[pin].empty()) {
        value = expectedMeasures[pin][0];
        expectedMeasures[pin].push_back(value); // Re-add the value to the end of the vector for repeated reads
        expectedMeasures[pin].erase(expectedMeasures[pin].begin());
    } else {
        value = random() % (max_val - min_val + 1) + min_val; // Fallback to random if pin not in map
    }
//    printf("Get analog pin %d: %d\n", pin, value);
    return value;
}

int digitalRead(uint8_t pin) {
    return pinRead(pin, 0, 1);
}

int analogRead(uint8_t pin) {
    return pinRead(pin, 0, 1024);
}

void analogWrite(uint8_t pin, int val) {
//    printf("Analog write to pin %d: %d\n", pin, val);
}

void digitalWrite(uint8_t pin, uint8_t val) {
//    printf("Digital write to pin %d: %s\n", pin, val == HIGH ? "HIGH" : "LOW");
}

unsigned long millis(void) {
    static auto start = chrono::steady_clock::now();
    auto now = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(now - start).count();
}

void pinMode(uint8_t pin, uint8_t mode) {
    printf("Set pin %d mode to %s\n", pin, mode == OUTPUT ? "OUTPUT" : "INPUT");
}

void delay(unsigned long ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void Serial_::begin(int baud) {}
void Serial_::print(uint value) { printf("%u", value); }
void Serial_::print(const char* str) { printf("%s", str); }
void Serial_::println() { printf("\n"); }
void Serial_::println(uint value) { printf("%u\n", value); }
void Serial_::println(const char* str) { printf("%s\n", str); }

#ifndef PIO_UNIT_TESTING

int main() {
    setup ();
    while (true) {
        loop ();
    }
}

#endif /* PIO_UNIT_TESTING */

#endif /* ARDUINO */
