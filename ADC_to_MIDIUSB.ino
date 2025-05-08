#include <MIDIUSB.h>

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void setup() {
}

void loop() {
  int sensorValue = analogRead(A0);
  controlChange(0, 50, map(sensorValue,0,1023,0,127));
  MidiUSB.flush();
  delay(20);
}
