#include <Arduino.h>
#include "releTumbler.h"

void ReleTumbler::init(int GPIO){
  pinMode(GPIO, OUTPUT);
  this->GPIO = GPIO;
  turnOFF();
}

void ReleTumbler::turnON(){
  digitalWrite(GPIO, LOW);
  isOn = true;
}

void ReleTumbler::turnOFF(){
  digitalWrite(GPIO, HIGH);
  isOn = false;
}

bool ReleTumbler::isON(){
  return isOn;
}

void ReleTumbler::reverse(){
  if(isOn) turnOFF();
  else turnON();
}