/**
 * DomeDrum - FSR.cpp
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
