#include <Arduino.h>

class Button{
private:
  int GPIO;
  int countClicked;
  int lastState = LOW;
  bool clicked;
  bool longClicked;

  unsigned long pressedTime = 0;  
  unsigned long freeTime = 0;

public:
  void setGPIO(int GPIO);
  int getGPIO();

  int getCountClick();
  int getCountClickToMenu();
  bool isClicked();
  bool isLongClicked();
  void tick();
  void longClick();

};

class Menu{
private:
  enum Mode{
    showTemperature,
    showHumidity, 
    showSoilHumidity,
    showIsAutoLight,
    activateFan,
    activateLight,
    showID,
    showPassword
  };

private:
  Button buttonSelect;
  Button buttonAction;
  Mode mode;
  String mods[8];
  String indications;

private:
  void calculateIndications();

public:
  Menu(int buttonSelectPin, int buttonActionPin);
  void show();
  void init();
  void tick();

};