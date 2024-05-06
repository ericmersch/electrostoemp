

#include "MIDIUSB.h"

//Global Variables
int sensorValue = 0;      //initialization of sensor variable, equivalent to EMA Y
 

void setup(){
}


void sendControlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
 
void loop(){
  sensorValue = analogRead(A0);    //read the sensor value using ADC

  sendControlChange (0,32,map(sensorValue,0,1023,0,127));
  MidiUSB.flush();
   
  delay(5);                              //20ms delay
}
