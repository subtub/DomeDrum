
#ifndef INCLUDED_FSR_H
#define INCLUDED_FSR_H
#include "Arduino.h"

class FSR {
  public:
  // Methods
  void init(int p, int t, int mc, int mn);
  void read();
  void update();
  
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

