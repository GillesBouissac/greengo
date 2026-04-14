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
#include "control_button.hpp"

CButton::CButton(uint8_t pin, uint8_t activeState) {
    _pin = pin;
    _statePressed = activeState;
    _stateReleased = !activeState;
    _state = _stateReleased; // initialize state to released
}

void CButton::setup() {
    pinMode(_pin, _stateReleased == HIGH ? INPUT_PULLUP : INPUT); // set pin to input pull-up mode
}

void CButton::update() {
    int currentState = digitalRead(_pin);

    // Debouncing: We detect a button state change but we need to known if enough time has passed since
    //   the last change to consider it as a real change and not just a bounce
    unsigned long stateDuration = millis() - _lastSwitchTime;
    if (_state != currentState) {
        if (stateDuration < BOUNCE_TIME) {
            // Not enough time has passed since the last change, we ignore this change and wait for the next one
            return;
        }
        _lastSwitchTime = millis();
    }

    _justReleased = false;
    _justPressed = false;
    if (_state == _stateReleased && currentState == _statePressed) { // button is pressed
        _justPressed = true;
    }
    else if (_state == _statePressed && currentState == _stateReleased) { // button is released
        _justReleased = true;
        if (stateDuration < SHORT_PRESS_TIME) {
            _shortPressed = true;
        }
        else if (stateDuration > LONG_PRESS_TIME) {
            _longPressed = true;
        }
    }
    else if (_state == _statePressed && currentState == _statePressed) { // button still pressed
        if (stateDuration > LONG_PRESS_TIME) {
            _stillPressed = false;
            unsigned long stillPressedDuration = millis() - _lastStillPressedTime;
            if (stillPressedDuration > _StillPressedInterval) {
                _stillPressed = true;
                _lastStillPressedTime = millis();
            }
        }
    }
    else { // _state == _stateReleased && currentState == _stateReleased) // button still released
        _shortPressed = false;
        _longPressed = false;
        _stillPressed = false;
    }
    _state = currentState;
}

boolean CButton::isShortPressed() {
    return _shortPressed;
}

boolean CButton::isLongPressed() {
    return _longPressed;
}

boolean CButton::isStillPressed() {
    return _stillPressed;
}

boolean CButton::justPressed() {
    return _justPressed;
}

boolean CButton::justReleased() {
    return _justReleased;
}

boolean CButton::isPressed() {
    return _state == _statePressed;
}

boolean CButton::isReleased() {
    return _state == _stateReleased;
}
