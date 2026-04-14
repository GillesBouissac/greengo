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
#include "control_speaker.hpp"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini player;

void speakersInit(int rxPin, int txPin) {
    SoftwareSerial FPSerial(rxPin, txPin);
    FPSerial.begin(9600);
    while(!player.begin(FPSerial)) {
        Serial.println("Unable to initialize DFPlayer Mini, check connections and SD card.");
        delay(1000);
    }
    player.volume(20); // Set volume to a reasonable level (0-30)
    Serial.println("DFPlayer Mini online.");
    player.disableDAC(); // Disable DAC to save power when not playing audio
    player.randomAll();
    Serial.println("Random playback enabled.");
    Serial.println("Number of tracks in SD card: " + String(player.readFileCounts()));
    Serial.println("Number of folders in SD card: " + String(player.readFolderCounts()));
}








