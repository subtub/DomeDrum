/**
 * Software für unseren DomeDrum
 *
 * Hardware:   Teensy 2.0
 * Version:    0.0.1
 */

#include "FSR.h"
#include <CapSense.h>

#define NUM_FSRS 10

#define PIN_START 12
#define TEENSY_LED_PIN 11
#define BUTTON_PIN 10

#define MIDI_CHANNEL 1
#define MIDI_NOTE_START 48 // C4
#define VELOCITY_DEF_THRESHOLD 1 // der standart thresholöd [0..127]

#define CAP_BUFFER_SIZE 50

FSR fsr[NUM_FSRS];
CapSense cs = CapSense(4, 6);

int max = 0;
long capBuffer[CAP_BUFFER_SIZE];
int capBufferCounter = 0;

void setup() {
  // declare LED as output
  pinMode(TEENSY_LED_PIN, OUTPUT);
  // declare pushbutton as input
  pinMode(BUTTON_PIN, INPUT);
  
  initFsrs();
  initCapBuffer();
  
  // cap sense
  //cs.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);
  Serial.println("hello");
}

long getAverage(long arr[], int arraySize){
  long sum = 0;
  for(int i=0; i<arraySize; i++){
    sum += arr[i];
  }
  return sum / arraySize;
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
  
  long total1 =  cs.capSense(30);
  if(capBufferCounter >= CAP_BUFFER_SIZE) capBufferCounter = 0;
  capBuffer[capBufferCounter] = total1;
  long avg = getAverage(capBuffer, CAP_BUFFER_SIZE);  
  capBufferCounter++;
  usbMIDI.sendNoteOn(midiNote, map()getAverage, 300, , midiChannel);
  Serial.println(avg);
  /*
  if(total1 > max){
    max = total1;
    Serial.println(total1);
  }
  */
  //Serial.println(total1);
  int capSensThresh = 150;
  int total2 = 0;
  if(total1 < capSensThresh){
    total2 = 0;
  }
  else {
    total2 = map(total1, 0, 700, 40, 127);
  }
  
  usbMIDI.sendNoteOn(100, total2, 1);
  
  delay(1);
}

void initFsrs(){
  // Wir benutzen die Teensy Pins 21 - 12
  for(int i=0; i<NUM_FSRS; i++){
    fsr[i].init(PIN_START+i, VELOCITY_DEF_THRESHOLD, MIDI_CHANNEL, MIDI_NOTE_START+i);
  }
}

void initCapBuffer(){
  for(int i=0; i<CAP_BUFFER_SIZE; i++){
    capBuffer[i] = 0;
  }
}

