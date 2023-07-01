#ifndef Ds1820Adv_h
#define Ds1820Adv_h

#ifndef DEBUG
#define DEBUG false
#endif

#include "Arduino.h"
#include <OneWire.h>
#include <Streaming.h>
class Ds1820Adv {
public:
  Ds1820Adv(OneWire*);
  void dsSearch();
  void dsCreateArrays();
  void dsDeleteArrays();
  void dsFillAddr();
  void dsInit();
  void dsStartConversion ();
  void dsReadData();
  void dsCalcData();
  bool dsQuery();
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
#endif
