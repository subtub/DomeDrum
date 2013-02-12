
#ifndef INCLUDED_FSR_H
#define INCLUDED_FSR_H
#include "Arduino.h"

/**
 * Force Sensitive Resistor utility class contains the sensor pin,
 * the midi note, channel parameter and some threshold magic.
 */
class FSR {
  public:
  // Methods
  void init(int p, int t, int mc, int mn);
  void updateMidiNote();
  //void updateMidiFade();
  
  private:
  int mapToMidi(int in);
  
  // Variables
  int pin;
  int midiChannel;
  int midiNote;
  int threshold;
  int lastVelocity;
  boolean active; // if last call of update() resulted in a midi-send
};

#endif // INCLUDED_FSR_H

