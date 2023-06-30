
#include "Ds1820Adv.h"

Ds1820Adv::Ds1820Adv(OneWire* _oneWire){
      _wire = _oneWire;
}

int Ds1820Adv::dsSearch (){
  int dsCounter = 0;
  while  (_wire->search(addr)){
    dsCounter++;
  }
  _wire->reset_search();
  delay(250);
  dsCount = dsCounter;
  return dsCounter;
}

void Ds1820Adv::dsCreateArrays(int count){
  if (dsCount == 0) return;
  dsAddr = new byte*[count];
  dsData = new byte*[count];
  dsTemp = new float[count];
  for (int i = 0; i<count; i++){
    dsAddr[i] = new byte[8];
    dsData[i] = new byte[9];
  }
}

void Ds1820Adv::dsDeleteArrays(int count){
  if (dsCount == 0) return;
  for (int i = 0; i<count; i++){
    delete[] dsAddr[i];
    delete[] dsData[i];
  }
  delete[] dsAddr;
  delete[] dsData;
}

void Ds1820Adv::dsFillAddr(){
  if (dsCount == 0) return;
  for (byte i = 0; i <= dsCount; i++){
    _wire->search(dsAddr[i]);    
  }
}

void Ds1820Adv::dsStartConversion (){
  if (dsCount == 0) return;
  for (byte i = 0; i < dsCount; i++){
    _wire->reset();
    _wire->select(dsAddr[i]);
    _wire->write(0x44);
  }
}

void Ds1820Adv::dsReadData (){
  if (dsCount == 0) return;
  for (byte i = 0; i < dsCount; i++){
    _wire->reset();
    _wire->select (dsAddr[i]);
    _wire->write(0xBE);
    for (byte j = 0; j < 9; j++){
      dsData[i][j] = _wire->read();
    }
  }
}

void Ds1820Adv::dsCalcData(){
  int16_t raw;
  for (byte i = 0; i < dsCount; i++) {
    raw = (dsData[i][1] << 8) | dsData[i][0];
    raw = raw << 3;
    raw = (raw & 0xFFF0) + 12 - dsData[i][6];
    dsTemp[i] = (float)raw / 16.0;
  }
}

void Ds1820Adv::dsPrintAddr(){
  if (dsCount == 0) return;
  for (byte i = 0; i < dsCount; i++){
    Serial << "Dev " << i+1 << ", addr: ";
    for (byte j = 0; j < 8; j++){
      Serial << _HEX(dsAddr[i][j]) << " ";
    }
    Serial << endl;
  }
  Serial << endl;
}

void Ds1820Adv::dsPrintData(){
  if (dsCount == 0) return;
  for (byte i = 0; i < dsCount; i++){
    Serial << "Dev " << i+1 << ", data: ";
    for (byte j = 0; j < 9; j++){
      Serial << _HEX(dsData[i][j]) << " ";
    }
    Serial << endl;
  }
  Serial << endl;
}

void Ds1820Adv::dsPrintTemp(){
  if (dsCount == 0) return;
  for (byte i = 0; i < dsCount; i++){
    Serial << "Dev " << i+1 << ", temp: ";  
    Serial << _FLOAT(dsTemp[i], 2) << " ";
    Serial << endl;
  }
  Serial << endl;
}
