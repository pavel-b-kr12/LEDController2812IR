
void movingBlendRGB()
{
  for (NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
  {
       uint8_t red = (millis() / 10) + (i * 12);                    // speed, length
       if (red > effLength) red = 0;
       uint8_t green = (millis() / 5) - (i * 12);                    // speed, length
       if (green > 128) green = 0;
       uint8_t blue = (i *32) ;                    // speed, length
       //uint8_t blue =sin8( (millis() / 5)) + (i *32) ;                    // speed, length
      if (blue > 128) blue = 0;
      //leds[i] = CRGB(red, green, blue);
      leds[i] = CRGB(red, green, blue* beatsin8(effSpeed/8)/255);
  }
}
void movingBlendRGB_A()
{
  for (NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
  {
      uint8_t red = (i *8) * (millis() /128); if (red > effLength) red = 0;
      uint8_t green = (i *16) * (millis() /128); if (green > effLength) green = 0;
      uint8_t blue = (i *32) * (millis() /128); if (blue > effLength) blue = 0;
      leds[i] = CRGB(red, green, blue);
      //!! blur(effSpeed)
  }
}