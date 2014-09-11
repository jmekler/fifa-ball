#include "WTV020SD.h"

const uint16_t PLAY_PAUSE = 0xFFFE;
const uint16_t STOP = 0xFFFF;
const uint16_t VOLUME_MASK = 0xFFF0;

WTV020SD::WTV020SD(int resetPin,int clockPin,int dataPin, int busyPin) {
    _resetPin = resetPin;
    _clockPin = clockPin;
    _dataPin  = dataPin;
    _busyPin  = busyPin;
    
    pinMode(_resetPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    pinMode(_dataPin, OUTPUT);
    pinMode(_busyPin, INPUT);
    
    digitalWrite(_resetPin, HIGH);
    digitalWrite(_clockPin, HIGH);
}

void WTV020SD::play(uint16_t trackNumber) {
    asyncPlay(trackNumber);
    // block until audio track playback finishes
    do {
        delay(10);
    } while (busy());
}

void WTV020SD::asyncPlay(uint16_t trackNumber) {
    sendCommand(trackNumber);
}

void WTV020SD::pause() {
    sendCommand(PLAY_PAUSE);
}

void WTV020SD::stop() {
    sendCommand(STOP);
}

void WTV020SD::volume(uint8_t volumeLevel) {
    unsigned int volume = min(max(volumeLevel, 0), 8);
    sendCommand(VOLUME_MASK + volume);
}

bool WTV020SD::busy() {
    return (digitalRead(_busyPin) == HIGH);
}

void WTV020SD::sendCommand(uint16_t command) {
    reset();
    digitalWrite(_clockPin, LOW);
    delay(2);
    
    for (unsigned int mask = 0x8000; mask > 0; mask >>= 1) {
        digitalWrite(_clockPin, LOW);
        
        if (command & mask) {
          digitalWrite(_dataPin, HIGH);
        }
        else {
          digitalWrite(_dataPin, LOW);
        }
        delayMicroseconds(100);
        
        digitalWrite(_clockPin, HIGH);
        delayMicroseconds(100);
    }
}

// reset the WTV020SD:
void WTV020SD::reset() {
    // make sure reset pin starts high
    digitalWrite(_resetPin, HIGH);
    delay(5);
    digitalWrite(_resetPin, LOW);
    delay(5);
    digitalWrite(_resetPin, HIGH);
    delay(300);
}