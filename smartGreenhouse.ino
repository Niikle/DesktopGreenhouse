#include "Menu.h"
#include <GTimer.h>

#define BUTTON1_PIN 26
#define BUTTON2_PIN 25
#define SEND_MENU_TICK 150
#define SEND_MENU_SHOW 500

Menu menu(BUTTON1_PIN, BUTTON2_PIN);

GTimer<millis> timerMenuTick;
GTimer<millis> timerMenuShow;

void setup() {
  Serial.begin(115200);

  timerMenuTick.setMode(GTMode::Timeout);
  timerMenuTick.setTime(SEND_MENU_TICK);
  timerMenuTick.start();

  timerMenuShow.setMode(GTMode::Timeout);
  timerMenuShow.setTime(SEND_MENU_SHOW);
  timerMenuShow.start();

  menu.init();

  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

}

void loop() {  
  static GTimer<millis> timerMenuTick(SEND_MENU_TICK, true);
  static GTimer<millis> timerMenuShow(SEND_MENU_SHOW, true);
    
  if (timerMenuTick){
    menu.tick();
  }
  
  if (timerMenuShow){
    menu.show();
  }

}


