/**
 * DomeDrum - CapSense.ino
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

#include <CapSense.h>

/*
  Macbook Netzteil dran, sonst reagiert CapSense beim Tippern auf Laptop...
*/

int lastMappedVal = 0;

CapSense cs = CapSense(4, 6); // 2.7M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil;

int max = 0;
long capBuffer[CAPSENSE_BUFFER_SIZE];
int capBufferCounter = 0;


void initCapSense() {
  initCapBuffer();
  //cs.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1
  cs.set_CS_AutocaL_Millis(10000);     // turn off autocalibrate on channel 1
}


void capSenseUpdate() {
  // read value
  long total1 =  cs.capSense(30);
  
  // store in buffer / reset buffer index // increment buffer
  if(capBufferCounter >= CAPSENSE_BUFFER_SIZE) capBufferCounter = 0;
  capBuffer[capBufferCounter] = total1;
  capBufferCounter++;
  
  // calculate average
  long avg = getAverage(capBuffer, CAPSENSE_BUFFER_SIZE);  
    
  int mappedCapVal = 0;
  //if(total1 < CAP_SENSE_THRESH){
  if(avg < CAP_SENSE_AVG_THRESH){
    mappedCapVal = 0;
  }
  else {
    //mappedCapVal = map(avg, CAP_SENSE_THRESH, 240, 0, 127);
    mappedCapVal = map(avg, CAP_SENSE_AVG_THRESH, 240, 0, 127);
    if(mappedCapVal > 127) mappedCapVal = 127;
  }
  Serial.print("CapSense: Value: ");
  Serial.print(total1);
  Serial.print("\tAverage: ");
  Serial.print(avg);
  Serial.print("\tMappedCapVal: ");
  Serial.print(mappedCapVal);
  Serial.print("\n");
  
  //usbMIDI.sendNoteOn(100, mappedCapVal, 1);
  //usbMIDI.sendControlChange(CAP_SENSE_MIDI_NOTE, mappedCapVal, CAP_SENSE_MIDI_CHANNEL);
  //usbMIDI.sendPitchBend(mappedCapVal, CAP_SENSE_MIDI_CHANNEL);
  //usbMIDI.sendPitchBend(0x2000 + mappedCapVal, CAP_SENSE_MIDI_CHANNEL);
  int capSenseTolerance = 3;
  //if(lastMappedVal != mappedCapVal){
    if(mappedCapVal > lastMappedVal + capSenseTolerance || mappedCapVal < lastMappedVal - capSenseTolerance){
    usbMIDI.sendControlChange(CAP_SENSE_MIDI_NOTE, mappedCapVal, CAP_SENSE_MIDI_CHANNEL);
  }
  
}


long getAverage(long arr[], int arraySize){
  long sum = 0;
  for(int i=0; i<arraySize; i++){
    sum += arr[i];
  }
  return sum / arraySize;
}

void initCapBuffer(){
  for(int i=0; i<CAPSENSE_BUFFER_SIZE; i++){
    capBuffer[i] = 0;
  }
}
