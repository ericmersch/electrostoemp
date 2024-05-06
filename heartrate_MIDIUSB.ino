
#include "MIDIUSB.h"

//Global Variables
int sensorPin = 0;        //pin number to use the ADC
int sensorValue = 0;      //initialization of sensor variable, equivalent to EMA Y
 
float EMA_a_low = 0.01;    //initialization of EMA alpha
float EMA_a_high = 0.1;
 
int EMA_S_low = 0;        //initialization of EMA S
int EMA_S_high = 0;
 
int highpass = 0;
int bandpass = 0;
 
void setup(){
   
  EMA_S_low = analogRead(sensorPin);      //set EMA S for t=1
  EMA_S_high = analogRead(sensorPin);
}
 
void loop(){
  sensorValue =0;
  for(int i = 0; i<30; i++){
  sensorValue += analogRead(sensorPin);    //read the sensor value using ADC
  } 
  EMA_S_low = (EMA_a_low*sensorValue) + ((1-EMA_a_low)*EMA_S_low);  //run the EMA
  EMA_S_high = (EMA_a_high*sensorValue) + ((1-EMA_a_high)*EMA_S_high);
  
  bandpass = EMA_S_high - EMA_S_low;      //find the band-pass
  
  sendControlChange (0,32,map(bandpass,0,250,0,127));
  MidiUSB.flush();
   
  delay(5);                              //20ms delay
}

void sendControlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
