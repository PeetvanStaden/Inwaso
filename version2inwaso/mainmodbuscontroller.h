#ifndef mainmodbuscontroller_h
#define mainmodbuscontroller_h
#include <Arduino.h>
#include "pins.h"

#include <ModbusRTUMaster.h> 
#include <RS485.h>





 // extern uint16_t holdingRegisters[NUM_HOLDING_REGISTERS];
  
//  extern char SensorsArray[TotalSensors][12];
//  extern bool OutputCtrl[TotalOutputs];    


class mainmodbuscontroller
{
 
  public:
      mainmodbus(uint16_t* _raptorholdingReg,int _sizeofHoldReg);
      bool raptorStart(uint16_t* _raptorholdingReg,int _sizeofHoldReg);
    
      bool modbusSync(uint16_t holdingReg[]);
      bool ReadInputs(uint16_t* holdingReg);
      bool ReadAnalogs(uint16_t* holdingReg);
      bool WriteOutputs(bool coils[NUM_COILS]);
      bool ReadVFD1(uint16_t* holdingReg);
      bool ReadVFD2(uint16_t* holdingReg);
      bool ReadVFD3(uint16_t* holdingReg);
      bool StartVFD1();
      bool StartVFD2();
      bool StartVFD3();
      bool StopVFD1();
      bool StopVFD2();
      bool StopVFD3();
      bool SpeedVFD1(int speedset);
      bool SpeedVFD2(int speedset);
      bool SpeedVFD3(int speedset);

      bool raptorSync(uint16_t _raptorholdingReg[],int _outputctrl[],int _outputsatus[]);
      int convert(int rows,int col,int rowpointer,int colpointer);
      void prit(char* input);
  private:
    
    
    int WhosTurn=0;
    void UpdateSlavemA(uint16_t *Buffer,uint16_t* holdingReg);
    void UpdateSlaveInputs(uint16_t *Buffer,uint16_t* holdingReg); 
    uint8_t VFDP[3]={99,99,99};
    unsigned long timestamp=0;   
    int ChangingBit(int Value,int place,bool value);  
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
    bool _InputRequest = false;
    bool _AnalogRequest = false;
    bool _WriteOutputs = false;
    bool _readvfd1  = false;
    bool _readvfd2 = false;
    bool _readvfd3 = false;
    bool _startvfd1 = false;
    bool _startvfd2 = false;
    bool _startvfd3 = false;
    bool _stopvfd1 = false;
    bool _stopvfd2 = false;
    bool _stopvfd3 = false;
    bool _speedvfd1 = false;
    bool _speedvfd2 = false;
    bool _speedvfd3 = false;
      
};
#endif
