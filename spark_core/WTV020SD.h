/*
 WTV020SD.h - Library to control a WTV020-SD module to play audio tracks (https://www.sparkfun.com/products/11125)
 Created by Jeff Mekler, June 29, 2014
 Based on code by Diego J. Arevalo (http://forum.arduino.cc/index.php?topic=117009.0)
 Released into the public domain.
 */
 
#include "application.h"

#ifndef WTV020SD_H
#define WTV020SD_H

class WTV020SD
{
public:
    WTV020SD(int resetPin,int clockPin,int dataPin, int busyPin);
    void play(uint16_t trackNumber);
    void asyncPlay(uint16_t trackNumber);
    void pause();
    void stop();
    void volume(uint8_t volumeLevel);
    bool busy();
private:
    void sendCommand(uint16_t command);
    void reset();
    int _resetPin;
    int _clockPin;
    int _dataPin;
    int _busyPin;
    int _busyPinState;
};

#endif
