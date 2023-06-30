#include <OneWire.h>
#include <Streaming.h>
#include "Ds1820Adv.h"

OneWire oneWire(5);
Ds1820Adv sensors(&oneWire);

void setup(void) {
  Serial.begin(115200,SERIAL_8N1,SERIAL_TX_ONLY);
  Serial.println("");
  sensors.dsSearch();
  Serial << "DS count " << sensors.dsCount << endl;
  sensors.dsCreateArrays (sensors.dsCount);
  sensors.dsFillAddr();
  sensors.dsPrintAddr();
}

void loop(void) {
  if (sensors.lastTime == 0) {
    sensors.dsStartConversion();
    sensors.lastTime = millis();
  }
  if ((millis() - sensors.lastTime) > 1000) {
    sensors.dsReadData();
//    dsCalcData();
    sensors.dsStartConversion();
    sensors.lastTime = millis();
    //dsPrintData();
    sensors.dsCalcData();
    sensors.dsPrintTemp();
  }
}
