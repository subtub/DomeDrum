/**
 * Software für unseren DomeDrum
 *
 * Hardware:   Teensy 2.0
 * Version:    0.0.1
 */

#include "DomeDrumConstants.h"

#include "FSR.h"
FSR fsr[FSR_TOTAL];


/**
 * Main setup
 */
void setup() {
  initDebugLed();
  initFsrs();
  //capSenseInit();
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
  //capSenseUpdate();
  delay(1);
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

