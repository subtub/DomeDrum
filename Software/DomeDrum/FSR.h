/**
 * DomeDrum - FSR.h
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

