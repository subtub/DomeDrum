/**
 * Software für unseren DomeDrum
 *
 * Hardware:   Teensy 2.0
 * Version:    0.0.1
 */


#define TEENSY_LED_PIN 11

// Die 10 FSR Sensoren PINs
// Wir benutzen die Teensy Pins 21 - 12
int FSR_PIN[] = { 21, 20, 19, 18, 17, 16, 15, 14, 13, 12 };

#define BUTTON_PIN 10


void setup() {
  // Ein kurzes blinken der build in LED des teensy's um visuelles
  // feedback zu bekommen, dass alles gut läuft.
  digitalWrite(TEENSY_LED_PIN, HIGH);
  delay(200);
  digitalWrite(TEENSY_LED_PIN, LOW);
  delay(200);
  digitalWrite(TEENSY_LED_PIN, HIGH);
  // declare LED as output
  pinMode(TEENSY_LED_PIN, OUTPUT);
  
  // declare pushbutton as input
  pinMode(BUTTON_PIN, INPUT);
  
  //Serial.begin(9600);
  //Serial.println("Teensy Setup Ready");
}
   

void loop() {
  int val = digitalRead(BUTTON_PIN);  // read input value
  if (val == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(TEENSY_LED_PIN, LOW);  // turn LED OFF
  } else {
    digitalWrite(TEENSY_LED_PIN, HIGH);  // turn LED ON
  }
  
  for(int i=0; i<=9; i++) {
    int s = analogRead(12+i);
    usbMIDI.sendNoteOn(10, fsrToMidi(s), 1+i);
  }
  
  /*int s1 = analogRead(12);
  usbMIDI.sendNoteOn(10, fsrToMidi(s1), 1);
  int s2 = analogRead(13);
  usbMIDI.sendNoteOn(10, fsrToMidi(s2), 2);
  int s3 = analogRead(14);
  usbMIDI.sendNoteOn(10, fsrToMidi(s3), 3);
  int s4 = analogRead(15);
  usbMIDI.sendNoteOn(10, fsrToMidi(s4), 4);*/
}


int fsrToMidi(int in) {
  return int(map(in, 0,1023, 0,126));
}
