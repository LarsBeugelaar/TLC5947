
/*
TLC5947 - A library for the Texas Instuments TLC5947 24-ch linear constant current PWM led driver
Created by Lars Beugelaar, May, 2013
Released into the public domain.
*/


#include "Arduino.h"
#include "TLC5947.h"


TLC5947 :: TLC5947(uint8_t _CLOCKPIN, uint8_t _DATAPIN, uint8_t _LATCHPIN)
{
  CLOCKPIN = _CLOCKPIN;
  DATAPIN = _DATAPIN;
  LATCHPIN = _LATCHPIN;
  
  uint8_t colorSequence[3] = { 0, 1, 2 };
  
  for (uint8_t i=0; i<24; i++)
  {
    dim[i] = 255;
  }
  dimTotal =  255;
}
TLC5947 :: TLC5947(uint8_t _CLOCKPIN, uint8_t _DATAPIN, uint8_t _LATCHPIN, uint8_t _COLOR1, uint8_t _COLOR2, uint8_t _COLOR3)
{
  CLOCKPIN = _CLOCKPIN;
  DATAPIN = _DATAPIN;
  LATCHPIN = _LATCHPIN;
  
    char colorSequenceChar[3] = { _COLOR1, _COLOR2, _COLOR3 };

    switch(_COLOR1)
    {
      case 'R': colorSequence[0] = 0;
      break;
      case 'G': colorSequence[0] = 1;
      break;
      case 'B': colorSequence[0] = 2;
      break;
      default:
      break;
    }
    switch(_COLOR2)
    {
      case 'R': colorSequence[1] = 0;
      break;
      case 'G': colorSequence[1] = 1;
      break;
      case 'B': colorSequence[1] = 2;
      break;
      default:
      break;
    }
        switch(_COLOR3)
    {
      case 'R': colorSequence[2] = 0;
      break;
      case 'G': colorSequence[2] = 1;
      break;
      case 'B': colorSequence[2] = 2;
      break;
      default:
      break;
    }
    
  for (uint8_t i=0; i<24; i++)
  {
    dim[i] = 255;
  }
  dimTotal =  255;
}

void TLC5947 :: updateAll()
{
  uint16_t shiftChannel[24]; // (valid within updateAll)
  shift(setDim(setSequence(channel, shiftChannel), shiftChannel));
}

uint16_t* TLC5947 :: setSequence(uint16_t* channelSource, uint16_t* channelTarget)
{
  for(uint8_t i=0; i<8; i++)
  {
    for(uint8_t j=0; j<3; j++)
    {
    *(channelTarget+i+i+i+j) = *(channelSource+i+i+i+ *(colorSequence+j));
    }
  }
  return channelTarget;
}

uint16_t* TLC5947 :: setDim(uint16_t* channelSource, uint16_t* channelTarget)
{
    for (uint8_t i=0; i<24; i++)
    {
      if (dimTotal != 255 || *(dim+i) != 255) *(channelTarget+i) = (uint16_t) ((uint32_t) ((*(channelSource+i) * dimTotal * (*(dim+i))) >> 16));
    }
  return channelTarget;
}

void TLC5947 :: shift(uint16_t *dataPtr)
{
  for (uint8_t i=24; i>0; i--)
  {
      uint16_t *currentColor = dataPtr+i-1;
      for(uint8_t j=0; j<12; j++)
      {
        uint16_t x = ((uint16_t)2048) & (*currentColor << j);
      
        if (x) digitalWrite(DATAPIN, HIGH);
        else digitalWrite(DATAPIN, LOW);
      
        digitalWrite(CLOCKPIN, HIGH);
        digitalWrite(CLOCKPIN, LOW);
      }
  }
  digitalWrite(LATCHPIN, HIGH);
  digitalWrite(LATCHPIN, LOW);
}

void TLC5947 :: clearAll()
{
  for (uint8_t i=0; i<24; i++)
  {
    *(channel+i) = 0;
  }
}

void TLC5947 :: setChannel(uint8_t n, uint8_t l)
{
  *(channel+n) = l << 4;
}

void TLC5947 :: setAll(uint8_t l)
{
  for(uint8_t i=0; i<24; i++)
  {
    *(channel+i) = l << 4;
  }
}

void TLC5947 :: setAll(uint8_t color[3])
{
  for(uint8_t i=0; i<8; i++)
  {
    for(uint8_t j=0; j<3; j++)
    {
      *(channel+i+i+i+j) = *(color+j) << 4;
    }
  } 
}

void TLC5947 :: setAll(uint8_t r, uint8_t g, uint8_t b)
{
  for(uint8_t i=0; i<8; i++)
  {
    *(channel+i+i+i) = r << 4;
    *(channel+i+i+i+1) = g << 4;
    *(channel+i+i+i+2) = b << 4;
  }
}

void TLC5947 :: setSingleColor(uint8_t n, char c, uint8_t v)
{
    if (c == 'R') *(channel+n+n+n) = v << 4;
    else if (c == 'G') *(channel+n+n+n+1) = v << 4;
    else if (c == 'B') *(channel+n+n+n+2) = v << 4;
}

void TLC5947 :: setLed(uint8_t n, uint8_t color[3])
{
  for(uint8_t i=0; i<3; i++)
  {
    *(channel+n+n+n+i) = *(color+i) << 4;
  }
}

void TLC5947 :: setLed(uint8_t n, uint8_t r, uint8_t g, uint8_t b)
{
  *(channel+n+n+n) = r << 4;
  *(channel+n+n+n+1) = g << 4;
  *(channel+n+n+n+2) = b << 4;
}

void TLC5947 :: dimChannel(uint8_t n, uint8_t l)
{
  *(dim+n) = l;
}

void TLC5947 :: dimLed(uint8_t n, uint8_t l)
{
  for(uint8_t i=0; i<3; i++)
  {
    *(dim+n+n+n+i) = l;
  }
}

void TLC5947 :: dimAll(uint8_t l)
{
  dimTotal = l;
}