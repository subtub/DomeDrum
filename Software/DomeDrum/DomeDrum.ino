/**
 * Software für unseren DomeDrum
 *
 * Hardware:   Teensy 2.0
 * Version:    0.0.1
 */

#include "FSR.h"
#include "DomeDrumConstants.h"
#include <CapSense.h>

FSR fsr[FSR_TOTAL];
CapSense cs = CapSense(4, 6);

int max = 0;
long capBuffer[CAPSENSE_BUFFER_SIZE];
int capBufferCounter = 0;


/**
 * Main setup
 */
void setup() {
  // declare LED as output
  pinMode(TEENSY_PIN_LED, OUTPUT);
  // declare pushbutton as input
  pinMode(TEENSY_PIN_BUTTON, INPUT);
  
  initFsrs();
  initCapBuffer();
  
  // cap sense
  //cs.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  
  
  Serial.begin(9600);
  Serial.println("hello");
}


/**
 * Main loop
 */
void loop() {
  int val = digitalRead(TEENSY_PIN_BUTTON);  // read input value
  if (val == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(TEENSY_PIN_LED, LOW);  // turn LED OFF
  } else {
    digitalWrite(TEENSY_PIN_LED, HIGH);  // turn LED ON
  }
  
  for(int i=0; i<FSR_TOTAL; i++){
    fsr[i].update();
  }
  
  long total1 =  cs.capSense(30);
  if(capBufferCounter >= CAPSENSE_BUFFER_SIZE) capBufferCounter = 0;
  capBuffer[capBufferCounter] = total1;
  long avg = getAverage(capBuffer, CAPSENSE_BUFFER_SIZE);  
  capBufferCounter++;
  usbMIDI.sendNoteOn(midiNote, map()getAverage, 300, midiChannel);
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


long getAverage(long arr[], int arraySize){
  long sum = 0;
  for(int i=0; i<arraySize; i++){
    sum += arr[i];
  }
  return sum / arraySize;
}


void initFsrs(){
  // Wir benutzen die Teensy Pins 21 - 12
  for(int i=0; i<FSR_TOTAL; i++){
    fsr[i].init(TEENSY_PIN_FSR_START+i, VELOCITY_DEF_THRESHOLD, MIDI_CHANNEL, MIDI_NOTE_START+i);
  }
}

void initCapBuffer(){
  for(int i=0; i<CAPSENSE_BUFFER_SIZE; i++){
    capBuffer[i] = 0;
  }
}

