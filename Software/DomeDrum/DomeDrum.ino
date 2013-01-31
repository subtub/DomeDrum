/**
 * Software für unseren DomeDrum
 *
 * Hardware:   Teensy 2.0
 * Version:    0.0.1
 */

#include "FSR.h"
#define NUM_FSRS 10
FSR fsr[NUM_FSRS];

#define PIN_START 12

#define MIDI_CHANNEL 1
#define MIDI_NOTE_START 48 // C4

#define VELOCITY_DEF_THRESHOLD 1 // der standart thresholöd [0..127]

#define TEENSY_LED_PIN 11
#define BUTTON_PIN 10


void setup() {
  // declare LED as output
  pinMode(TEENSY_LED_PIN, OUTPUT);
  // declare pushbutton as input
  pinMode(BUTTON_PIN, INPUT);
  
  initFsrs();
}

void initFsrs(){
  // Wir benutzen die Teensy Pins 21 - 12
  for(int i=0; i<NUM_FSRS; i++){
    fsr[i].init(PIN_START+i, VELOCITY_DEF_THRESHOLD, MIDI_CHANNEL, MIDI_NOTE_START+i);
  }
}
   

void loop() {
  int val = digitalRead(BUTTON_PIN);  // read input value
  if (val == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(TEENSY_LED_PIN, LOW);  // turn LED OFF
  } else {
    digitalWrite(TEENSY_LED_PIN, HIGH);  // turn LED ON
  }
  
  for(int i=0; i<NUM_FSRS; i++){
    fsr[i].update();
  }
  
  /*
  for(int i=0; i<NUM_FSRS; i++) {
    int s = analogRead(12+i);
    usbMIDI.sendNoteOn(10, fsrToMidi(s), 1+i);
  }
  */
  /*int s1 = analogRead(12);
  usbMIDI.sendNoteOn(10, fsrToMidi(s1), 1);
  int s2 = analogRead(13);
  usbMIDI.sendNoteOn(10, fsrToMidi(s2), 2);
  int s3 = analogRead(14);
  usbMIDI.sendNoteOn(10, fsrToMidi(s3), 3);
  int s4 = analogRead(15);
  usbMIDI.sendNoteOn(10, fsrToMidi(s4), 4);*/
  delay(1);
}

