void mood()
{
  int colourIndex = random(4);
  int numPixelsToUpdate = random(8);

  for (int i = 1; i < numPixelsToUpdate; i++) 
  {
    int pos = random(NUM_LEDS);
    targetColour[pos] = colourPallete[colourIndex];
  }
  
  for (int i = 0; i < NUM_LEDS; i++) 
  {
    fadeTowardColor(leds[i], targetColour[i], 5);
  }

  FastLED.show();  
  FastLED.delay(SPEED);
}

void setupMood()
{
  for (int i = 0; i < NUM_LEDS; i++) 
  {
    leds[i] = targetColour[i] = colourPallete[random(4)];
  }

  FastLED.show();  
}