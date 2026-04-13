
#include "control_cheeks.hpp"
#include "control_pump.hpp"

/// @brief Helper function to print multiple values to the serial output, separated by commas
template<typename T, typename... Args>
void printvals(T first, Args... rest) {
  Serial.print(first);
  if constexpr (sizeof...(rest) > 0) {
    Serial.print(",");
    printvals(rest...);
  } else {
    Serial.println();
  }
}

/// @brief Pin definitions
#define ADJ_LED_POWER     A0 // Potentiometer for adjusting the LED power (brightness)
#define ADJ_LED_FREQ      A1 // Potentiometer for adjusting the LED blinking frequency, the lower the faster the blinking
#define ADJ_PUMP_POWER    A2 // Potentiometer for adjusting the pump RPM
#define BUTTON             7 // Button for turning on/off the pump and LED
#define PWM_LED           10 // PWM output pin for the LED, controls the brightness
#define PWM_PUMP          11 // PWM output pin for the pump, controls the RPM

/// @brief Initialisation
void setup () {
  Serial.begin(9600);
  pinMode (BUTTON, INPUT);
  pinMode (ADJ_LED_POWER, INPUT);
  pinMode (ADJ_LED_FREQ, INPUT);
  pinMode (ADJ_PUMP_POWER, INPUT);
  pinMode (PWM_PUMP, OUTPUT);
  pinMode (PWM_LED, OUTPUT);
}

/// @brief Engine current state
static bool lastButtonState = false;
static ulong cheek_power_control = 0;
static ulong cheek_blink_control = 0;
static ulong pump_power_control = 0;

/// @brief Main loop
void loop () {
  uint led_power = 0;
  uint pump_power = 0;

  bool is_on = digitalRead(BUTTON)==HIGH;
  if (is_on) {
    if (!lastButtonState) {
      cheek_power_control = readCheeksPower (ADJ_LED_POWER);
      cheek_blink_control = readCheeksBlinkFrequency (ADJ_LED_FREQ);
      pump_power_control  = readPumpPower (ADJ_PUMP_POWER);
    }
    led_power = computeCheeksPower(cheek_power_control, cheek_blink_control);
    pump_power = computePumpRpm(pump_power_control);
  }
  else {
    led_power = switchOffCheeks();
    pump_power = switchOffPump();
  }

  analogWrite (PWM_PUMP, pump_power);
  analogWrite (PWM_LED, led_power);
  printvals((uint)is_on, pump_power_control, cheek_blink_control, cheek_power_control, pump_power, led_power);

  lastButtonState = is_on;
}
