/**
 * DomeDrum - DomeDrum.ino
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * Software für unseren DomeDrum
 *
 * Hardware:   Teensy 2.0
 * Version:    0.0.1
 */

#include "DomeDrumConstants.h"
#include "FSR.h"

FSR fsr[FSR_TOTAL];

boolean capSenseActive = true;

/**
 * Main setup
 */
void setup() {
  initDebugLed();
  initFsrs();
  if(capSenseActive){
    initCapSense();
  }
  Serial.begin(9600);
  Serial.println("hello");
}


/**
 * Initialize the led debug pins
 */
void initDebugLed() {
  // declare LED as output
  pinMode(TEENSY_PIN_LED, OUTPUT);
  // declare pushbutton as input
  pinMode(TEENSY_PIN_BUTTON, INPUT);
}


/**
 * Initialize the FSR class array
 */
void initFsrs(){
  // We use Teensy Pins 12 - 21
  for(int i=0; i<FSR_TOTAL; i++){
    fsr[i].init(TEENSY_PIN_FSR_START+i, VELOCITY_DEF_THRESHOLD, MIDI_CHANNEL, MIDI_NOTE_START+i);
  }
}


/**
 * Main loop
 */
void loop() {
  loopDebugLed();
  loopFsrs();
  if(capSenseActive){
    capSenseUpdate();
  }
  delay(10);
}


/**
 * Turn on the led if button is pressed
 */
void loopDebugLed() {
  // read input value
  int val = digitalRead(TEENSY_PIN_BUTTON);
  // check if the input is HIGH (button released)
  if (val == HIGH) {
    // turn LED OFF
    digitalWrite(TEENSY_PIN_LED, LOW);
  } else {
    // turn LED ON
    digitalWrite(TEENSY_PIN_LED, HIGH);
  }
}


/**
 * Update all fsr sensors
 */
void loopFsrs() {
  for(int i=0; i<FSR_TOTAL; i++){
    fsr[i].updateMidiNote();
  }
}

