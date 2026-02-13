#include <EEPROM.h>
#include "ID.h"

#define EEPROM_SIZE 512

void Id::generateNewId(){
  String allSymbols = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOASDFGHJKLZXCVBNM!?*";
  id = "";
  for(size_t i = 0;  i < 8; ++i){
    id += allSymbols[random(allSymbols.length())];
  }
  saveNewId();
  Serial.print("new id: ");
  Serial.println(id);
}

void Id::generateNewPassword(){
  String allSymbols = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOASDFGHJKLZXCVBNM!?*";
  password = "";
  for(size_t i = 0;  i < 8; ++i){
    password += allSymbols[random(allSymbols.length())];
  }
  saveNewPassword();
  Serial.print("new password: ");
  Serial.println(password);
}

void Id::saveNewId(){
  EEPROM.put(NULL, id);
  EEPROM.commit();
}

void Id::saveNewPassword(){
  EEPROM.put(EEPROM_SIZE / 2, password);
  EEPROM.commit();
}

void Id::init(){
  EEPROM.begin(EEPROM_SIZE);
  
  setIdFromEEPROM();
  generateNewId();

  setPasswordFromEEPROM();
  generateNewPassword();

}

void Id::setIdFromEEPROM(){
  String tempId;
  EEPROM.get(NULL, tempId);
  id = tempId;
}

void Id::setPasswordFromEEPROM(){
  String tempPassword;
  EEPROM.get(EEPROM_SIZE / 2, tempPassword);
  password = tempPassword;
}

String Id::getId(){ return id; }
String Id::getPassword(){ return password ;}


