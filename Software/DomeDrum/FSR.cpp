
#include "FSR.h"

void FSR::init(int p, int t, int mc, int mn) {
  pin = p;
  midiChannel = mc;
  midiNote = mn;
  threshold = t;
  active = false;
  lastVelocity = 0;
}


void FSR::updateMidiNote() {
  // current velocity [0..127]
  int in = analogRead(pin);
  int velocity = mapToMidi(in);
  if(!active && velocity > threshold){
    // send midi note on with new velocity
    usbMIDI.sendNoteOn(midiNote, velocity, midiChannel);
    active = true;
  }
  if(active && velocity < threshold){
    usbMIDI.sendNoteOff(midiNote, 0, midiChannel);
    active = false;
  }
  lastVelocity = velocity;
}


/*void FSR::sendMidiFade() {
  if(lastVelocity != velocity) {
    // send midi note off message --- may be useless -> check
    usbMIDI.sendNoteOff(midiNote, lastVelocity, midiChannel);
    // send midi note on with new velocity
    usbMIDI.sendNoteOn(midiNote, velocity, midiChannel);
  }
}*/


int FSR::mapToMidi(int in) {
  return int(map(in, 0,1023, 0,126));
}
