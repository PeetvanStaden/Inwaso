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

  
   // char *_SensorArry;
   // bool UpdateTableFromRaptor(char **sensorarray);
   // bool UpdateTableFromEEPROM(char **sensorarray);
    
};
#endif
