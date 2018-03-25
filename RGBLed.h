#ifndef RGBLED
 #define RGBLED
 #include <stdint.h>
 #include <Arduino.h>
  
 class RgbLed {
  public:
    RgbLed(int redPin, int greenPin, int bluePin);
    void set(int r, int g, int b);
    void updateLeds();
    void green();
  private:
  // Connections
    int _redPin;
    int _greenPin;
    int _bluePin;
  // light value
    int _red;
    int _green;
    int _blue;
 };
#endif
