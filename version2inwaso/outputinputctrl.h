#ifndef outputinputctrl_h
#define outputinputctrl_h
#include <Arduino.h>
#include "pins.h"
#include "mainmodbuscontroller.h"


#define numDigitalInputs int(sizeof(digitalInputsPins) / sizeof digitalInputsPins[0])
#define numAnalogInputs int(sizeof(analogInputsPins) / sizeof analogInputsPins[0])

//extern char SensorsArray[36][9];
   


class outputinputctrl
{
  public:
   // interlock();//char **sensorarray);
   void sensorToOutput(uint16_t* holdingReg);
   void updateHardwareInputs(uint16_t holdingReg[]); 
   int updateHardwareOutputs(int OutputCtrl[]);
   int updateHardwareStatus(int OutputStatus[]);
  private:
    int ChangingBit(int Value,int place,bool value);
    mainmodbuscontroller modbus;
    bool SetXV001(int Value);
    bool SetXV002(int Value);
    bool SetXV003(int Value);
    bool SetXV004(int Value);
    bool SetXV009(int Value);
    bool SetXV010(int Value);
    bool SetXV011(int Value);
    bool SetXV012(int Value);
    bool SetXV013(int Value);
    bool SetXV014(int Value);
    bool SetXV015(int Value);
    bool SetXV016(int Value);
    bool SetXV017(int Value);
    bool SetXV018(int Value);
    bool SetXV019(int Value);
    void SetPC003(int Value);
    void SetPC005(int Value);
    void SetPC006(int Value);
    void SetPC007(int Value);
    void SetPC001(int Value);
    void SetPC002(int Value);
    void SetPC004(int Value);    
    void SetMU001(int Value);
    void SetMU002(int Value);
    void SetMU003(int Value);
    bool buff[NUM_COILS]={true};
    uint8_t VFDSpeed[3]={0};
    bool vfd1start = false;
    bool vfd2start = false;
    bool vfd3start = false;
    uint8_t VFDP[3]={99,99,99};
    const int tempDEC[81]={
      843,
      830,
      816,
      802,
      788,
      774,
      759,
      745,
      730,
      716,
      701,
      687,
      672,
      658,
      643,
      629,
      614,
      600,
      586,
      572,
      558,
      544,
      531,
      517,
      504,
      491,
      478,
      465,
      453,
      440,
      428,
      416,
      405,
      393,
      382,
      371,
      361,
      350,
      340,
      330,
      320,
      311,
      302,
      293,
      284,
      276,
      267,
      259,
      251,
      244,
      237,
      229,
      222,
      215,
      209,
      203,
      196,
      190,
      185,
      179,
      173,
      168,
      163,
      158,
      153,
      149,
      144,
      140,
      135,
      131,
      127,
      124,
      120,
      116,
      113,
      110,
      106,
      103,
      100,
      97,
      94
    };

     
};
#endif

