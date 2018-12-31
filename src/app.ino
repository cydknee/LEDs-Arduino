#include "FastLED.h"

#define DATA_PIN    3
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    12 * 12
#define BRIGHTNESS  40
#define SPEED       20

CRGB leds[NUM_LEDS];
CRGB targetColour[NUM_LEDS];

CRGB colourPallete[4] = {CRGB::Aqua, CRGB::Blue, CRGB::DarkBlue, CRGB::DodgerBlue};

void setup()
{
    Serial.begin(4800); // For debugging

    FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    setupMood();  
}

void loop()
{
    mood();  
}