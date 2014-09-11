// This #include statement was automatically added by the Spark IDE.
#include "WTV020SD.h"
int resetPin = D7;
int clockPin = D4;
int dataPin = D3;
int busyPin = D2;

WTV020SD player(resetPin, clockPin, dataPin, busyPin); // reset, clock, data, busy

bool sleep = false;
long sleepStart = 0;
int sleepTime;

void setup() {
    // define API functions
    Spark.function("goal", goalNotification);
    Spark.function("sleep", gotoSleep);
    
    // set playback volume
    player.volume(7); // range: 0..7
}

void loop() {
    // check to see if we should sleep
    if (sleep && (millis() > sleepStart)) {
        Spark.sleep(SLEEP_MODE_DEEP, sleepTime);
    }
    
    // busy audio indicator
    if (player.busy()) {
        RGB.control(true);
        RGB.color(255,0,0);
        delay(100);
    } else {
        RGB.control(false);
    }
}

// plays goal audio clip
int goalNotification(String command) {
    // play audio clip
    player.asyncPlay(0001);
    
    // return success
    return 1;
}

// puts wifi to sleep for specified amount of time
int gotoSleep(String command) {
    sleep = true;
    sleepStart = millis() + 1000;
    sleepTime = command.toInt();
    if (sleepTime == 0) { sleepTime = 60; }
    return sleepTime;
}



    
    // find audio track to playback
    // uint16_t teamTrack = 50;
    // switch (command) {
    //     case "Algeria":
    //         teamTrack = 1;
    //         break;
    //     case "Argentina":
    //         teamTrack = 2;
    //         break;
    //     case "Australia":
    //         teamTrack = 3;
    //         break;
    //     case "Belgium":
    //         teamTrack = 4;
    //         break;
    //     case "Bosnia Herzigovina":
    //         teamTrack = 5;
    //         break;
    //     case "Brazil":
    //         teamTrack = 6;
    //         break;
    //     case "Cameroon":
    //         teamTrack = 7;
    //         break;
    //     case "Chile":
    //         teamTrack = 8;
    //         break;
    //     case "Columbia":
    //         teamTrack = 9;
    //         break;
    //     case "Costa Rica":
    //         teamTrack = 10;
    //         break;
    //     case "Croatia":
    //         teamTrack = 11;
    //         break;
    //     case "Ecuador":
    //         teamTrack = 12;
    //         break;
    //     case "England":
    //         teamTrack = 13;
    //         break;
    //     case "France":
    //         teamTrack = 14;
    //         break;
    //     case "Germany":
    //         teamTrack = 15;
    //         break;
    //     case "Ghana":
    //         teamTrack = 16;
    //         break;
    //     case "Greece":
    //         teamTrack = 17;
    //         break;
    //     case "Honduras":
    //         teamTrack = 18;
    //         break;
    //     case "Iran":
    //         teamTrack = 19;
    //         break;
    //     case "Italy":
    //         teamTrack = 20;
    //         break;
    //     case "Ivory Coast":
    //         teamTrack = 21;
    //         break;
    //     case "Japan":
    //         teamTrack = 22;
    //         break;
    //     case "Mexico":
    //         teamTrack = 23;
    //         break;
    //     case "Netherlands":
    //         teamTrack = 24;
    //         break;
    //     case "Nigeria":
    //         teamTrack = 25;
    //         break;
    //     case "Portugal":
    //         teamTrack = 26;
    //         break;
    //     case "Russia":
    //         teamTrack = 27;
    //         break;
    //     case "South Korea":
    //         teamTrack = 28;
    //         break;
    //     case "Spain":
    //         teamTrack = 29;
    //         break;
    //     case "Switzerland":
    //         teamTrack = 30;
    //         break;
    //     case "United States":
    //         teamTrack = 31;
    //         break;
    //     case "Uruguay":
    //         teamTrack = 32;
    //         break;
    //     default:
    //         teamTrack = 50;
    // }