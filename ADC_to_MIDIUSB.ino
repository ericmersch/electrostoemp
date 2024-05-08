#include <MIDIUSB.h>

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).
// controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 to 65

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

int lastPotValue=0;

void setup() {
}

void loop() {
  
  int potValue = analogRead(A0);
  if (lastPotValue != potValue){
    controlChange(0, 50, map(potValue,0,1023,0,127));
    
  }
  lastPotValue = potValue;
}
