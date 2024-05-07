#include "MIDIUSB.h"

// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to

int buttonState = 0;         // current state of the button
int Velocity = 80;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT_PULLUP);
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      
      noteOn(1,69,Velocity);
      MidiUSB.flush();
    } 
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      noteOff(1,69,Velocity);
      MidiUSB.flush();
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState = buttonState;
  
  //delay(5);
  
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
