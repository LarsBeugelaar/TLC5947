
/*
TLC5947 - A library for the Texas Instuments TLC5947 24-ch linear constant current PWM led driver
Created by Lars Beugelaar, May, 2013
Released into the public domain.
*/

#include "Arduino.h"


#ifndef TLC5947_h
#define TLC5947_h

class TLC5947
{
  private:
  // private vars
  uint16_t channel[24]; // 24 TLC5947 channels
  uint8_t dim[24]; // dim per channel
  uint8_t dimTotal; // general dim channel
  
  public:
  // public vars
  uint8_t DATAPIN;
  uint8_t CLOCKPIN;
  uint8_t LATCHPIN;
  
  private:
  // private vars
  uint8_t colorSequence[3];
  uint8_t colorSequenceChar[3];
  
  public:
  //Constructor
  TLC5947(uint8_t _DATAPIN, uint8_t _CLOCKPIN, uint8_t _LATCHPIN);
  TLC5947(uint8_t _CLOCKPIN, uint8_t _DATAPIN, uint8_t _LATCHPIN, uint8_t _COLOR1, uint8_t _COLOR2, uint8_t _COLOR3);
  
  private:
  // private functions
  void shift(uint16_t* shiftChannel);
  uint16_t* setSequence(uint16_t* channelSource, uint16_t* channelTarget);
  uint16_t* setDim(uint16_t* channelSource, uint16_t* channelTarget);
  
  public:
  // public functions
  void updateAll();
  void clearAll();
  void setChannel(uint8_t n, uint8_t l);
  void setAll(uint8_t l);
  void setAll(uint8_t r, uint8_t g, uint8_t b);
  void setAll(uint8_t color[3]);
  void setSingleColor(uint8_t n, char c, uint8_t v);
  void setLed(uint8_t n, uint8_t r, uint8_t g, uint8_t b);
  void setLed(uint8_t n, uint8_t color[3]);
  void dimChannel(uint8_t n, uint8_t l);
  void dimLed(uint8_t n, uint8_t l);
  void dimAll(uint8_t l);
};
#endif