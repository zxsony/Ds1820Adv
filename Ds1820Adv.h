#include "Arduino.h"
#include <OneWire.h>
#include <Streaming.h>
class Ds1820Adv {
public:
  Ds1820Adv(OneWire*);
  int dsSearch();
  void dsCreateArrays(int count);
  void dsDeleteArrays(int count);
  void dsFillAddr();
  void dsStartConversion ();
  void dsReadData();
  void dsCalcData();
  void dsPrintAddr();
  void dsPrintData();
  void dsPrintTemp();
    byte addr[8];
    byte** dsAddr;
    byte** dsData;
    int dsCount = 0;
    unsigned long lastTime = 0;
    float* dsTemp;
private:
    OneWire* _wire;
};
