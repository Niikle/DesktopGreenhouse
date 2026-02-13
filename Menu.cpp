#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>
#include "SoilMoisture.h"
#include "ID.h"
#include "Menu.h"
#include "illumination.h"
// #include "fan.h"
// #include "light.h"
#include "releTumbler.h"

#define DHT_PIN 14
#define ILLUMINATION_PIN 27
#define SOIL_MOISTURE1 13
#define SOIL_MOISTURE2 33
#define SOIL_MOISTURE3 32
#define LONG_PRESS_TIME 5000
#define NO_INFO "no information"
#define MENU_POINTS 7
#define FAN_PIN 18
#define LAPM_PIN 19

#define ILLUMINATION_RHRESHOLD 1200
#define ILLUMINATION_DIFFERENCE 600

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHT_PIN, DHT11);
SoilMoisture soil1, soil2, soil3;
Id id;
Illumination illumination;
ReleTumbler fan, lamp;

void Button::setGPIO(int GPIO){
  this->GPIO = GPIO;
}

int Button::getGPIO(){
  return GPIO;
}

bool Button::isClicked(){
  return clicked;
}

bool Button::isLongClicked(){
  return longClicked;
}

int Button::getCountClick(){
  return countClicked;
}

void Button::tick(){
  clicked = !digitalRead(GPIO);
  countClicked += clicked;
  if(lastState == LOW && clicked == HIGH) pressedTime = millis();
  else if(lastState == HIGH && clicked == LOW){
    freeTime = millis();
    if(freeTime - pressedTime > LONG_PRESS_TIME){
      longClicked = !longClicked;
      if (longClicked){
        longClick();
      }
    }
    //else longClicked = false;
  }
  lastState = clicked;  
}

void Button::longClick(){
  id.generateNewId();
}

int Button::getCountClickToMenu(){
  return countClicked % MENU_POINTS;
}

void Menu::tick(){
  buttonSelect.tick();
  buttonAction.tick();

  switch(buttonSelect.getCountClickToMenu()){
  case 3:
    if(illumination.isAutoIllumination()){
      if(!lamp.isON()){
        if(illumination.read() < ILLUMINATION_RHRESHOLD){
          lamp.turnON();
          Serial.println("lamp.turnON();");
        }
        else{
          lamp.turnOFF();
          Serial.println("lamp.turnOFF();");
        }
      }
      else{
        if(illumination.read() < ILLUMINATION_RHRESHOLD + ILLUMINATION_DIFFERENCE){
          lamp.turnON();
          Serial.println("lamp.turnON();");
        }
        else{
          lamp.turnOFF();
          Serial.println("lamp.turnOFF();");
        }
      }
    }
    Serial.println(illumination.read());
    if(buttonAction.isClicked()){
      illumination.autoIlluminationReverse();
    }
    break;
  case 4:
    if(buttonAction.isClicked()){
      fan.reverse();
    }
    break;
  case 5:
    if(buttonAction.isClicked()){
      lamp.reverse();
    }
  default:
    Serial.println("1");
    break;
  }
}

Menu::Menu(int buttonSelectPin, int buttonActionPin){
  buttonSelect.setGPIO(buttonSelectPin);
  buttonAction.setGPIO(buttonActionPin);

  mods[0] = "temperature";
  mods[1] = "humidity";
  mods[2] = "soil humidity";
  mods[3] = "auto light";
  mods[4] = "fan";
  mods[5] = "light";
  mods[6] = "ID";
}

void Menu::init(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  id.init();
  illumination.init(ILLUMINATION_PIN);
  dht.begin();
  fan.init(FAN_PIN);
  lamp.init(LAPM_PIN);

  soil1.init(SOIL_MOISTURE1);
  soil2.init(SOIL_MOISTURE2);
  soil3.init(SOIL_MOISTURE3);

  pinMode(SOIL_MOISTURE1, INPUT_PULLUP);
  pinMode(SOIL_MOISTURE2, INPUT_PULLUP);
  pinMode(SOIL_MOISTURE3, INPUT_PULLUP);

}

void Menu::show(){
  lcd.clear();
  lcd.setCursor(0, 0);

  if(buttonAction.isLongClicked()){
    lcd.print("last ID was del");
    lcd.setCursor(0, 1);
    lcd.print("new ID: ");
    lcd.print(id.getId());
  }
  else{
    lcd.print(mods[buttonSelect.getCountClickToMenu()] + ":");
    calculateIndications();

    lcd.setCursor(0, 1);
    lcd.print(indications);
  }
}

void Menu::calculateIndications(){
  indications = NO_INFO;
  switch(buttonSelect.getCountClickToMenu()){
  case 0:
    indications = String(dht.readTemperature()) + "*C";
    break;
  case 1:
    indications = String(dht.readHumidity()) + "%";
    break;
  case 2:
    indications = String(soil1.soil()) + "% " +
                  String(soil2.soil()) + "% " +
                  String(soil3.soil()) + "% ";
    break;
  case 3:
    //indications = String(illumination.read()) + "% ";
    if(!illumination.isAutoIllumination()) indications = "OFF";
    else indications = "ON";
    break;
  case 4:
    if(fan.isON()) indications = "deactivate";
    else indications = "activate";
    break;
  case 5:
    if(lamp.isON()) indications = "deactivate";
    else indications = "activate";
    break;
  case 6:
    indications = id.getId();
    break;
  default:
    indications = "activate";
    break;
  }
}
