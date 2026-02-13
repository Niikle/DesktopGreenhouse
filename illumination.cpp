#include <Arduino.h>
#include "illumination.h"

void Illumination::init(int GPIO){
  this->autoIllumination = false;
  this->GPIO = GPIO;
  pinMode(GPIO, INPUT_PULLUP);
}

void Illumination::calculate(){
  data = analogRead(GPIO);
  //data = map(data, 4095, 0, 0, 100);
}

int Illumination::read(){
  calculate();
  return data;
}

bool Illumination::isAutoIllumination(){
  return autoIllumination;
}

void Illumination::autoIlluminationTurnON(){
  this->autoIllumination = true;
}

void Illumination::autoIlluminationTurnOFF(){
  this->autoIllumination = false;
}

void Illumination::autoIlluminationReverse(){
  if(isAutoIllumination()) autoIlluminationTurnOFF();
  else autoIlluminationTurnON();
}