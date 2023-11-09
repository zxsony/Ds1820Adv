#include <OneWire.h>
#include <Streaming.h>
#include "Ds1820Adv.h"


OneWire oneWire(5);
Ds1820Adv sensors(&oneWire);

void setup(void) {
  Serial.begin(115200,SERIAL_8N1,SERIAL_TX_ONLY);
  Serial.println("");
  sensors.dsInit();
  Serial << "DS count " << sensors.dsCount << endl;
  sensors.dsPrintAddr();
}

void loop(void) {
delay (300);
if (sensors.dsQuery()){
    sensors.dsPrintTemp();
  }
}
