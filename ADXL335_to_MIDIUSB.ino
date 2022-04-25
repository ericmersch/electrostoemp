#include "MIDIUSB.h"

//Global Variables
int sensorPin = 0;        //pin number to use the ADC
int sensorValue = 0;      //initialization of sensor variable, equivalent to EMA Y
bool State = false;
bool lastState = false;

 

void setup(){
  //Serial.begin(9600);
}


void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
 
void loop(){

  sensorValue = sqrt(analogRead(A0)^2+analogRead(A1)^2+analogRead(A2)^2);    //read the sensor value using ADC
  

  State = (sensorValue>=22);

  //Serial.println(sensorValue);
  
  if (State != lastState) {
    // if the state has changed, increment the counter
    if (State) {
      
      
      noteOn(1,69,120);
      MidiUSB.flush();
      delay(100);
    } 
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      noteOff(1,69,120);
      MidiUSB.flush();
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastState = State;
   
  delay(5);                              //20ms delay
}
