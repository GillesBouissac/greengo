#ifndef arduino_emulator_hpp
#define arduino_emulator_hpp

#ifndef ARDUINO

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define PI 3.14159265358979323846
#define A0 (uint8_t)14
#define A1 (uint8_t)15
#define A2 (uint8_t)16
#define HIGH 0x1
#define LOW  0x0
#define INPUT 0x0
#define OUTPUT 0x1

void setup ();
void loop ();
int digitalRead(uint8_t pin);
int analogRead(uint8_t pin);
void analogWrite(uint8_t pin, int val);
void digitalWrite(uint8_t pin, uint8_t val);
unsigned long millis(void) ;
void pinMode(uint8_t pin, uint8_t mode);
void delay(unsigned long ms);

/// @brief Clear all expected reads for a specific pin
/// @param pin The pin for which to clear expected reads
void clearExpectedReads(uint8_t pin);

/// @brief Adds an expected value for a specific pin
/// @param pin The pin for which to expect a read
/// @param value The expected value
void expectRead(uint8_t pin, int value);

class Serial_ {
public:
    void begin(int baud);
    void print(uint value);
    void print(const char* str);
    void println();
    void println(uint value);
    void println(const char* str);
};

extern Serial_ Serial;

#endif /* ARDUINO */

#endif /* arduino_emulator_hpp */
