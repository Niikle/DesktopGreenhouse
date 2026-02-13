class ReleTumbler{
private:
  int GPIO;
  bool isOn;

public:
  void turnON();
  void turnOFF();
  void reverse();
  bool isON();
  void init(int GPIO);
};