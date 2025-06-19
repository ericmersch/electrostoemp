#include <CapacitiveSensor.h>
#include <MIDIUSB.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   pitchSensor = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   volumeSensor = CapacitiveSensor(9,7);        // 10M resistor between pins 9 & 7, pin 7 is sensor pin, add a wire and or foil if desired


void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void setup()                    
{
   pitchSensor.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   volumeSensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
   Serial.begin(9600);
}

void loop()                    
{
    long pitch =  pitchSensor.capacitiveSensor(1000);
    long volume =  volumeSensor.capacitiveSensor(1000);  
    Serial.print(pitch);
    Serial.print(",");
    Serial.println(volume);
    
    noteOn(0,max(0,min(127,map(pitch,0,1500,0,127))),max(0,min(127,map(volume,0,1500,0,127))));
    MidiUSB.flush();           
    delay(20);                             // arbitrary delay to limit data to serial port 
}
