#include "Menu.h"

#define BUTTON1_PIN 26
#define BUTTON2_PIN 25
#define TIMER_TICK 200

Menu menu(BUTTON1_PIN, BUTTON2_PIN);

unsigned long previousMillisTick = 0;

void setup() {
  Serial.begin(115200);

  menu.init();

  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

}

void loop() {  
  menu.tick();
  delay(250);
  menu.show();
}


