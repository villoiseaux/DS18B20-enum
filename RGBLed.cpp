#include "RGBLed.h"

RgbLed::RgbLed(int redPin, int greenPin, int bluePin){
    _redPin=redPin;       pinMode(_redPin,OUTPUT);
    _greenPin=greenPin;   pinMode(_greenPin,OUTPUT);
    _bluePin=bluePin;     pinMode(_bluePin,OUTPUT);
  // initial value
    set(HIGH,HIGH,HIGH);
    updateLeds();
}


void RgbLed::set(int r, int g, int b){
    int _red=r;
    int _green=g;
    int _blue=b;      
}

void RgbLed::updateLeds(){
  digitalWrite(_redPin,_red);
  digitalWrite(_greenPin,_green);
  digitalWrite(_bluePin,_blue);  
}

void RgbLed::green(){
    set(LOW,HIGH,LOW);
    updateLeds();  
}

