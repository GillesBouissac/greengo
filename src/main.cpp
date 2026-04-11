/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"


// inputs for auto-alimentation (not implemented)
#define PWM_AUTO        3
#define BUTTON          7
typedef unsigned long   ulong;
typedef unsigned int    uint;

// ----------------------------------------
// Analog input smoothing
// ----------------------------------------
#define HISTORY_DEPTH   10
#define ANALOG_READ_MAX 1024
typedef struct {
  int idx;   // next idx
  int count; // total count of values read
  ulong values[HISTORY_DEPTH];
} PinHistory;

// Resets a PinHistory structure
void initHistory(PinHistory* history) {
  history->idx = 0;
  history->count = 0;
  for (int i=0; i<HISTORY_DEPTH; i++) {
    history->values[i] = 0;
  }
}

// Read a value and store it in the given history array
// The returned value is the average of all inputs in the array
ulong analogReadSmooth(int pin, PinHistory* history) {
  // Records the new value
  ulong value = analogRead (pin);
  history->idx   = (history->idx+1) % HISTORY_DEPTH;
  history->count = min(history->count+1, HISTORY_DEPTH);
  history->values[history->idx] = value;
  // Average
  int idx = history->idx;
  ulong sum = 0;
  for (int i=0; i<history->count; i++) {
    sum += history->values[idx];
    idx = (idx-1+HISTORY_DEPTH) % HISTORY_DEPTH;
  }
  return sum/history->count;
}

// Reset and fill the given PinHistory
ulong resampleAnalogInput(int pin, PinHistory* history) {
  initHistory (history);
  ulong result = 0;
  for (int i=0; i<HISTORY_DEPTH; i++) {
    result = analogReadSmooth (pin,  history);
  }
  return result;
}

// ----------------------------------------
// Pump RPM control
// ----------------------------------------
#define ADJ_PUMP_POWER    A2
#define PUMP_VOLT_MIN     7
#define PUMP_VOLT_MAX     12
#define PWM_PUMP          11
#define PUMP_POWER_MAX    255
#define PUMP_POWER_MIN    (255*PUMP_VOLT_MIN)/PUMP_VOLT_MAX
#define PUMP_POWER_RANGE  (PUMP_POWER_MAX-PUMP_POWER_MIN)
ulong adj_pump_power = 0;
uint updatePumpRpm(bool is_on) {
  uint pump_power = 0;
  if (is_on) {
    pump_power = PUMP_POWER_MIN + (adj_pump_power*PUMP_POWER_RANGE)/ANALOG_READ_MAX;
  }
  analogWrite (PWM_PUMP, pump_power);
  return pump_power;
}

// ----------------------------------------
// LED Blinking control
// ----------------------------------------
#define ADJ_LED_POWER     A0
#define ADJ_LED_FREQ      A1
#define PWM_LED           10
#define MS_PER_CYCLE_MIN  400
#define MS_PER_CYCLE_MAX  5000
#define LED_POWER_MIN     1
ulong start_time = 0;
ulong adj_led_power = 0;
ulong adj_led_freq = 0;
uint updateLedBlinking(bool is_on) {
  uint led_power = 0;
  if (is_on) {
    ulong led_max_power = max(min(255,(adj_led_power*255)/ANALOG_READ_MAX),LED_POWER_MIN);
    ulong ms_per_cycle = MS_PER_CYCLE_MIN + (adj_led_freq*MS_PER_CYCLE_MAX)/ANALOG_READ_MAX;
    ulong value_in_cycle = (millis()-start_time) % ms_per_cycle;
    float angle = (2 * PI * value_in_cycle / ms_per_cycle) + PI;
    led_power = LED_POWER_MIN + (led_max_power-LED_POWER_MIN)*(cos(angle)+1)/2;
  }
  else {
    start_time = millis();
  }
  analogWrite (PWM_LED, led_power);
  return led_power;
}

// ----------------------------------------
// Debug
// ----------------------------------------
void printvals(uint a,uint b,uint c) {
  Serial.print(a);
  Serial.print(",");
  Serial.print(b);
  Serial.print(",");
  Serial.print(c);
  Serial.println();
}

// ----------------------------------------
// Initialisation
// ----------------------------------------
void resampleAnalogInputs() {
  PinHistory history;
  adj_led_power  = resampleAnalogInput (ADJ_LED_POWER,  &history);
  adj_led_freq   = resampleAnalogInput (ADJ_LED_FREQ,   &history);
  adj_pump_power = resampleAnalogInput (ADJ_PUMP_POWER, &history);
  printvals(adj_led_power,adj_led_freq,adj_pump_power);
}
void setup () {
  Serial.begin(9600);
  pinMode (PWM_AUTO, OUTPUT);
  pinMode (PWM_PUMP, OUTPUT);
  pinMode (PWM_LED, OUTPUT);
  pinMode (BUTTON, INPUT);
  pinMode (ADJ_LED_POWER, INPUT);
  pinMode (ADJ_LED_FREQ, INPUT);
  pinMode (ADJ_PUMP_POWER, INPUT);
  resampleAnalogInputs();
}

// ----------------------------------------
// Main loop
// ----------------------------------------
bool lastButtonState = false;
void loop () {
  bool is_on = digitalRead(BUTTON)==HIGH;
  if (is_on && !lastButtonState) {
    resampleAnalogInputs();
  }
  uint led = updateLedBlinking(is_on);
  uint pump = updatePumpRpm(is_on);
  lastButtonState = is_on;
  printvals(led,pump,0);
}
