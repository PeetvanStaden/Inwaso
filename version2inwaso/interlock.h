#ifndef interlock_h
#define interlock_h
#include <Arduino.h>
#include <EEPROM.h>
#include "mainmodbuscontroller.h"
#include "outputinputctrl.h"
//extern char SensorsArray[36][12];
class interlock
{

      
  public:
  //lock(holdingRegisters,NUM_HOLDING_REGISTERS,SensorsArray,TotalSensors,12);
   interlock();
   
   void startup(uint16_t* raptorholdingReg,int sizeofHoldReg,int* _outputcontrol,int* _outputstatus);
   int CheckInterlocks(uint16_t* raptorholdingReg,int* _outputcontrol,int* _outputstatus);
   
  private:

  mainmodbuscontroller modbus;
  outputinputctrl outputs;
  bool buff[NUM_COILS]={false};  
  float raptor = 0;
  void testLT001(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT1(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT2(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testAT001(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT36(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT3(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT4(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT7(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT8(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT26(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT27(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT28(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT29(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testLT016(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testAT006(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT34(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT35(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testLT010(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT30(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT31(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT32(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testINT33(uint16_t* raptorholdingReg,int* _outputcontrol);
  void testLT013(uint16_t* raptorholdingReg,int* _outputcontrol);
  
   // char *_SensorArry;
   // bool UpdateTableFromRaptor(char **sensorarray);
   // bool UpdateTableFromEEPROM(char **sensorarray);
    
};
#endif
