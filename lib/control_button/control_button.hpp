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
#ifndef control_button_hpp
#define control_button_hpp

#include "greengo_common.hpp"

/// @brief A class to handle button press detection
class CButton
{

public:

    /// @brief Constructor for the PressButton class
    /// @param pin Pin number where the button is connected
    /// @param activeState The state (HIGH or LOW) that represents the button being pressed
    CButton(uint8_t pin, uint8_t activeState = LOW);

    /// @brief Initializes the button pin mode, should be called in the setup() function
    void setup();

    /// @brief Updates the button state, should be called in the loop() function to detect button presses
    void update();

    /// @brief Sets the interval for the still pressed event
    /// @param interval The interval in milliseconds
    void setStillPressedInterval(unsigned long interval) {
        _StillPressedInterval = interval;
    }

    /// @brief Gets the interval for the still pressed event
    /// @return The interval in milliseconds
    unsigned long getStillPressedInterval() {
        return _StillPressedInterval;
    }

    /// @brief Tells that the last update call detected a short press
    /// @return True if the button was short pressed, false otherwise
    boolean isShortPressed();

    /// @brief Tells that the last update call detected a long press
    /// @return True if the button was long pressed, false otherwise
    boolean isLongPressed();

    /// @brief Tells that the last update call detected a still press
    ///        Note: The value will oscillate between true and false every _StillPressedInterval milliseconds as long as the button is still pressed
    ///              This allows to trigger actions at regular intervals while the button is still pressed
    /// @return True if the button was still pressed and that this value can be used to trigger an action, false otherwise
    boolean isStillPressed();

    /// @brief Tells that the last update call detected that the button was just pressed
    /// @return True if the button was pressed in the last update call, false otherwise
    boolean justPressed();

    /// @brief Tells that the last update call detected that the button was just released
    /// @return True if the button was released in the last update call, false otherwise
    boolean justReleased();

    /// @brief Tells that the button is currently pressed
    /// @return True if the button is currently pressed, false otherwise
    boolean isPressed();

    /// @brief Tells that the button is currently released
    /// @return True if the button is currently released, false otherwise
    boolean isReleased();

public:
    // Time thresholds for different types of button presses in milliseconds
    static const unsigned long SHORT_PRESS_TIME = 200;
    static const unsigned long LONG_PRESS_TIME = 500;
    static const unsigned long BOUNCE_TIME = 50; // debounce time

private:
    uint8_t _pin;
    uint8_t _state; // the last known button state
    uint8_t _statePressed; // the state value when the button is considered pressed
    uint8_t _stateReleased; // the state value when the button is considered released
    unsigned long _lastSwitchTime = 0; // the time when the button has last been switched
    unsigned long _lastStillPressedTime = 0; // the time when the still pressed event was last triggered
    unsigned long _StillPressedInterval = 500; // the time when the still pressed event was last triggered

    // Detected button press situations
    boolean _shortPressed = false;
    boolean _longPressed = false;
    boolean _stillPressed = false;
    boolean _justPressed = false;
    boolean _justReleased = false;
};


#endif /* control_button_hpp */
