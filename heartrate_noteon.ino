
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

int previous = 0;
 
void setup(){
  Serial.begin(115200);                   //setup of Serial module, 115200 bits/second
   
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
  
//  sendControlChange (0,32,map(bandpass,0,150,0,127));
//  MidiUSB.flush();

  //sendControlChange (0,32,map(bandpass,0,250,0,127));
  //MidiUSB.flush();
  //Serial.print(bandpass);
  //Serial.print(" ; ");
  
  if(bandpass>60 && previous <=60)
  {
    noteOn(1,69,120);
    delay(5);
    //noteOff(1,69,120);
    MidiUSB.flush();
  }
  //else Serial.println(0);
  previous = bandpass;
  delay(5);                              //20ms delay
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
