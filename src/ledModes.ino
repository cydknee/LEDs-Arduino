void mood()
{
  int colourIndex = random16(255);
  int numPixelsToUpdate = random(8);

  for (int i = 1; i < numPixelsToUpdate; i++) 
  {
    int pos = random16(NUM_LEDS);
    leds[pos] = ColorFromPalette(currentPalette, colourIndex);
  }
  
  FastLED.show();  
  FastLED.delay(100000/FRAMES_PER_SECOND);
}

void setupMood()
{
  for (int i = 0; i < NUM_LEDS; i++) 
  {
    leds[i] = ColorFromPalette(currentPalette, random16(255));
  }

  FastLED.show();  
}