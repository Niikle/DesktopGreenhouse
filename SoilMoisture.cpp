#include "SoilMoisture.h"
#include <Arduino.h>

void SoilMoisture::init(int GPIO){
  this->GPIO = GPIO;
  pinMode(GPIO, INPUT);
}

int SoilMoisture::soil(){
  soilMoisture = analogRead(GPIO);
  soilMoisture = map(soilMoisture, 4095, 2220, 0, 100);
  if(soilMoisture >= 0 && soilMoisture < 100) return soilMoisture;
  else return 100;
}