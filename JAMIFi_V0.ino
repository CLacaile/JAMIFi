// JAMIFi - Just Another MIDI Filter
// MIDI channel filter device
// Author: Clément LACAILE
// Date: 24 nov 18
// Version: 0

#include <MIDI.h>

#define NB_CHANNELS 4
#define POT_RESOLUTION 1024

MIDI_CREATE_DEFAULT_INSTANCE();

static const unsigned ledPin = 13;      // LED pin on Arduino Uno
static const unsigned potPin = 2;       // Potentiometer pin
int value = 0;                          // the value of the potentiometer

void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
    MIDI.begin(MIDI_CHANNEL_OMNI);      // Launch MIDI and listen to all channels
}

void loop()
{
    value = analogRead(potPin);
    Serial.println(getChannelFromPot(value));
    if (MIDI.read())                    
    {
        MIDI.send(MIDI.getType(),
                  MIDI.getData1(),
                  MIDI.getData2(),
                  getChannelFromPot(value));    // Send the received data on the selected channel
    }
}

// Get the channel selected by the potentiometer 
byte getChannelFromPot(int potValue) {
    if (potValue <= POT_RESOLUTION/NB_CHANNELS * 1) {
      return 1;
    }
    else if (potValue <= POT_RESOLUTION/NB_CHANNELS * 2) {
      return 2;
    }
    else if (potValue <= POT_RESOLUTION/NB_CHANNELS * 3) {
      return 3;
    }
    else if (potValue <= POT_RESOLUTION/NB_CHANNELS * 4) {
      return 4;
    }
    else {
      return MIDI_CHANNEL_OMNI;
    }
}

