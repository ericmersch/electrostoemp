#include <MIDIUSB.h>

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
//Global Variables
int sensorPin = 0;        //pin number to use the ADC
int sensorValue = 0;      //initialization of sensor variable, equivalent to EMA Y
 
float a = 0.3;    //initialization of EMA alpha
float b = 0.5;
 
float y1 = 0;        //initialization of EMA S
float y2 = 0;

float bandpass = 0;
 
void setup(){
  Serial.begin(9600);                   //setup of Serial module, 115200 bits/second
   
  y1 = analogRead(sensorPin);      //set EMA S for t=1
  y2 = analogRead(sensorPin);
}
 
void loop(){
  sensorValue =0;
  for(int i = 0; i<250; i++){
  sensorValue += analogRead(sensorPin);    //read the sensor value using ADC
  } 
  y1 = a*sensorValue + (1-a)*y1;  //run the EMA
  y2 = b*sensorValue + (1-b)*y2;
  
  bandpass = y2 - y1;      //find the band-pass
  
  controlChange (0,32,max(map(atan(bandpass/20),0,PI/2.,0,127),0)); //sigmoid and threshold
  MidiUSB.flush();

  Serial.println(bandpass);
   
  //delay(1);                              //20ms delay
}
