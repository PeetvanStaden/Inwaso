#ifndef processctrl_h
#define processctrl_h
#include <Arduino.h>
#include "mainmodbuscontroller.h"
#include "outputinputctrl.h"
#include "pins.h"

class processctrl
{
   
  public:
  processctrl(uint16_t* raptorholdingReg,int* OutputCtrl,int* OutputStatus);
  void process1();
  void process2tk1();
  void process2tk2();
  void process2tk3();
  void process2vs1();
  void process2ver1();
  void process2ver2();
  void process2su1();
private:
mainmodbuscontroller sr;
bool buff[NUM_COILS]={false};  
uint16_t* _raptorHoldingReg;
int* _OutputCtrl;
int* _OutputStatus;
int _PC1TURN = 0;

int _PC2TK1TURN = 0;

int _PC2TK2TURN = 0;
void _TK2toTK1Options();
void _TK2toTK3Options();
void _TK3toOBLOptions();
void _TK3toTK1Options();

int _PC2TK3TURN = 0;

int _PC2VER1TURN = 0;

int _PC2VER2TURN = 0;

int _PC2VS1TURN = 0;

int _PC2VS2TURN = 0;

int _PC2SU1TURN = 0;
int speedcontrolstage = 0;
int _PC2OptionTK1 = 0;
int _PC2OptionTK3 = 0;
int _PC2TK3TK1Option = 0;
int _PC2TK3OBLOption = 0;
   
};
#endif
