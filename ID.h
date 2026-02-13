#include <Arduino.h>

class Id {
private:
  String id, password;
  void setIdFromEEPROM();
  void setPasswordFromEEPROM();
  void saveNewId();
  void saveNewPassword();

public:
  void init();
  void generateNewId();
  void generateNewPassword();
  String getId();
  String getPassword();
  
};