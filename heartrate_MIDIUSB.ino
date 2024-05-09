#include <MIDIUSB.h>

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
//Global Variables
int sensorPin = 0;        //pin number to use the ADC
int sensorValue = 0;      //initialization of sensor variable, equivalent to EMA Y
 
float EMA_a_low = 0.3;    //initialization of EMA alpha
float EMA_a_high = 0.5;
 
int EMA_S_low = 0;        //initialization of EMA S
int EMA_S_high = 0;
 
int highpass = 0;
float bandpass = 0;
 
void setup(){
  Serial.begin(9600);                   //setup of Serial module, 115200 bits/second
   
  EMA_S_low = analogRead(sensorPin);      //set EMA S for t=1
  EMA_S_high = analogRead(sensorPin);
}
 
void loop(){
  sensorValue =0;
  for(int i = 0; i<250; i++){
  sensorValue += analogRead(sensorPin);    //read the sensor value using ADC
  } 
  EMA_S_low = (EMA_a_low*sensorValue) + ((1-EMA_a_low)*EMA_S_low);  //run the EMA
  EMA_S_high = (EMA_a_high*sensorValue) + ((1-EMA_a_high)*EMA_S_high);
  
  bandpass = ((EMA_S_high - EMA_S_low));      //find the band-pass
  
  controlChange (0,32,min(127,max(map(atan(bandpass/20),0,PI/2.,0,127),0)));
  MidiUSB.flush();

  Serial.println(bandpass);
   
}
