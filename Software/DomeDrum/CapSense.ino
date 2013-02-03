
/*

#include <CapSense.h>

CapSense cs = CapSense(4, 6);

int max = 0;
long capBuffer[CAPSENSE_BUFFER_SIZE];
int capBufferCounter = 0;


void capSenseInit() {
  initCapBuffer();
  cap sense
  cs.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
}


void capSenseUpdate() {
  long total1 =  cs.capSense(30);
  if(capBufferCounter >= CAPSENSE_BUFFER_SIZE) capBufferCounter = 0;
  capBuffer[capBufferCounter] = total1;
  long avg = getAverage(capBuffer, CAPSENSE_BUFFER_SIZE);  
  capBufferCounter++;
  Serial.println(avg);
  
  //if(total1 > max){
    //max = total1;
    ((Serial.println(total1);
  //}
  //Serial.println(total1);
  int capSensThresh = 150;
  int total2 = 0;
  if(total1 < capSensThresh){
    total2 = 0;
  }
  else {
    total2 = map(total1, 0, 700, 40, 127);
  }
  
  //usbMIDI.sendNoteOn(100, total2, 1);
  
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


*/
