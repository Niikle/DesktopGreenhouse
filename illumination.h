class Illumination{
private:
  int data;
  int GPIO;
  
private:
  void calculate();
  bool autoIllumination;

public:
  void init(int GPIO);
  int read();
  bool isAutoIllumination();

  void autoIlluminationTurnON();
  void autoIlluminationTurnOFF();
  void autoIlluminationReverse();
};