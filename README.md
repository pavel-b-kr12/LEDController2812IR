# LEDController2812IR
![](0.jpg)

Simple controller for ws2812b ws2811 stripes with IR control, includes a lot of effects.

### Сoncept

At power up Switch between "settings"  (IR) and "working" (faster) modes.

Choose effect, each has many settings to customize. It saves last.

In save/load presets by press numbers buttons in  "settings mode" / "working mode".

### Hardware and reference design:

pro mini or other

VS1838 (pins: D6, GND, VCC)

switch (pins: A4, GND)

LED stripe of WS2812  (pins: D2, GND)

3x7 IR keypad
![Infrared keypad](IR_3x7.jpg)

### Characteristics

power on 5v (VCC) can be as low as 3.3v LED also working.

atmega168 for 60-150 LEDs

atmega328 for 150-300 LEDs

atmega2560 for 1000-2000 LEDs

### basic instructions
0. Assemble the device
1. Install USB-COM programmer driver e.g. CP2102
2. use lightweight portable HEX uploader http://xloader.russemotto.com or compile from source
![Flashing with CP2102](Flashing_pro_mini_with_CP2102.jpg)
3. Choose hex, port, type of controller 168/328/.. Upload
4. Connect to stripe.
### Cautions
* Don't power stripe (e.g. longer than 15px with White light LEDs) through USB-programmer-controller boards. Disconnect "+" wire beetween stripe and controller or use separate power while connectiong USB
* Check + - and max 5v .
* Bad PSU can adds 1v noise to 5v output, so if you have to use cheap one - add diode (with enought power rating 1A-2-5-10A) to + wire so it down voltage a bit or use down DC-DC.
* Connect power AFTER all assembled with good GND wire connection
* Don't see on bright Blue LEDs (or white because it is from Blue) while testing if you need your eyes for a long life. Use diffuser, dim power, itc.
### Hints
* to mantain max quality (bit depth) regulate brightness not by program but via DC-DC down modules like XL4005 (without current limit)






