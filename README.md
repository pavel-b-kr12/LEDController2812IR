# LEDController2812IR
Simple controller for ws2812b ws2811 stripes with IR control, includes a lot of effects.

### Сoncept
At power up Switch between "settings"  (IR) and "working" (faster) modes.
Choose effect, each has many settings to customize. It saves last.
In save/load presets by press numbers buttons in  "settings mode" / "working mode".

### Hardware and reference design:
pro mini or orher
VS1838 (pins: D6, GND, VCC)
switch (pins: A4, GND)

### Characteristics
power on 5v (VCC) can be as low as 3.3v LED also working.
atmega168 for 130-150 LEDs
atmega328 for 300 LEDs
atmega2560 for 1500-2000 LEDs


