#include "FastLED.h"
#include <SoftwareSerial.h>
#include <protothreads.h>

#define DATA_PIN    3
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    12 * 12
#define BRIGHTNESS  40
#define SPEED       20

CRGB leds[NUM_LEDS];
CRGB targetColour[NUM_LEDS];

CRGB colourPallete[4] = {CRGB::Aqua, CRGB::Blue, CRGB::DarkBlue, CRGB::DodgerBlue};

SoftwareSerial mySerial(6,5); // pins for bluetooth

static struct pt pt1, pt2; // declare protothreads

void setup()
{
    PT_INIT(&pt1);
    PT_INIT(&pt2);

    Serial.begin(9600); //open the serial port for debugging
    mySerial.begin(9600); // open the bluetooth serial port

    FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    setupMood();  
}

static int readSerialThread(struct pt *pt, int interval) {
    static unsigned long timestamp = 0;
    PT_BEGIN(pt);
        while(1) {
        PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
        timestamp = millis(); // take a new timestamp
        if(mySerial.available()){
            Serial.println(mySerial.readString()); // send from serial to bluetooth
        }
    }
    PT_END(pt);
}

static int moodThread(struct pt *pt, int interval) {
    static unsigned long timestamp = 0;
    PT_BEGIN(pt);
    while(1) {
        PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
        timestamp = millis();
        mood(); 
    }
    PT_END(pt);
}

void loop()
{
    readSerialThread(&pt1, 900);
    moodThread(&pt2, 100);
}