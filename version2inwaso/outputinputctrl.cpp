#include "outputinputctrl.h"

//TODO: RS485 motor control
//TODO: MU001 and 002
//TODO: Motor Relays and wiring
bool modbusoutputtransmit = false;
 int digitalInputsPins[][2] = {
  
    {I0_0,XV014R}, 
    {I0_1,XV017R}, 
    {I0_2,LSHH014}, 
    {I0_11,XV015R},
    {I0_12, XV016R},
    {I1_0,LSLL015},
    {I1_1,LSHH002},
    {I1_2,LSLL003},
    {I1_3,LSLL005},
    {I1_4,LSLL004},
    {I1_7,XV018R}, 
    {I1_8,XV019R}, 
    {I2_0, LSHH009},
    {I2_1, LSLL008},
    {I2_2,LSHH011},
    {I2_3,LSLL012}

  
  };
  
  static int analogInputsPins[][2] = {
  
    {I0_7,TT001},
    {I0_8,TT002},
    {I0_9,TT003},
   // {I0_10,},
    {I1_12,AT003},
    //{I2_7,AT004ABC},
    //{I2_8,AT005ABC},
    {I2_9,AT004ABC},
    {I2_10,AT005ABC}
  };
  bool digitalInputs[numDigitalInputs];
  uint16_t analogInputs[numAnalogInputs];  
bool outputinputctrl::SetXV001(int Value)
{
  //correct
  digitalWrite(Q0_0,Value);
  delay(300);
   modbus.prit("changing valve 1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!zzzzzzzzzzzzzzzzzzzzz \n");
  return true;
}
bool outputinputctrl::SetXV002(int Value)
{
  digitalWrite(Q1_6,Value);
  return true;
}
bool outputinputctrl::SetXV003(int Value)
{
  digitalWrite(Q0_4,Value);
  return true;
}
bool outputinputctrl::SetXV004(int Value)
{
  digitalWrite(Q0_6,Value);
  return true;
}
bool outputinputctrl::SetXV009(int Value)
{
  digitalWrite(Q1_0,Value);
  return true;
}
bool outputinputctrl::SetXV010(int Value)
{
  digitalWrite(Q0_2,Value);
  return true;
}
bool outputinputctrl::SetXV011(int Value)
{
  digitalWrite(Q1_4,Value);
  return true;
}
bool outputinputctrl::SetXV012(int Value)
{
  digitalWrite(Q1_2,Value);
  return true;
}
bool outputinputctrl::SetXV013(int Value)
{
  digitalWrite(Q2_0,Value);
  return true;
}
bool outputinputctrl::SetXV014(int Value)
{
  digitalWrite(Q2_5,Value);
  return true;
}
bool outputinputctrl::SetXV015(int Value)
{
  digitalWrite(Q2_2,Value);
  return true;
}
bool outputinputctrl::SetXV016(int Value)
{
  digitalWrite(Q2_6,Value);
  return true;
}

bool outputinputctrl::SetXV017(int Value)
{
  if(buff[XV017M]==!Value)
  modbusoutputtransmit=true;
  buff[XV017M]=Value;
  return Value;
}
bool outputinputctrl::SetXV018(int Value)
{
  if(buff[XV018M]==!Value)
  modbusoutputtransmit=true;
  buff[XV018M]=Value;
  return true;
}
bool outputinputctrl::SetXV019(int Value)
{
  
  if(buff[XV019M]==!Value)
  modbusoutputtransmit=true;
  buff[XV019M]=Value;
  if(modbusoutputtransmit)
  modbus.prit("Changing XV019................... \n");
  return true;
  
}
void outputinputctrl::SetPC003(int Value)
{
  if(buff[PC003M]==!Value)
  {
    modbusoutputtransmit=true;
    modbus.prit("PC003 output transmit \n");
  }
  buff[PC003M]=Value;
}

void outputinputctrl::SetPC005(int Value)
{
  if(buff[PC005M]==!Value)
  {
    modbusoutputtransmit=true;
    modbus.prit("PC005 output transmit \n");
  }
  buff[PC005M]=Value;
  
}
void outputinputctrl::SetPC006(int Value)
{
  if(buff[PC006M]==!Value)
  {
    modbusoutputtransmit=true;
   
  }
  buff[PC006M]=Value;
}
void outputinputctrl::SetPC007(int Value)
{
  if(buff[PC007M]==!Value)
  modbusoutputtransmit=true;
  buff[PC007M]=Value;
}
void outputinputctrl::SetPC001(int Value)
{
  VFDSpeed[0]=Value;
  //Serial.println("SetPC001 to speed:");
  //Serial.println(Value,DEC);
}
void outputinputctrl::SetPC002(int Value)
{
  VFDSpeed[1]=Value;
  //Serial.println("SetPC002 to speed:");
  //Serial.println(Value,DEC);
}
void outputinputctrl::SetPC004(int Value)
{
  VFDSpeed[2]=Value;
  //Serial.println("SetPC004 to speed:");
  //Serial.println(Value,DEC);
}
void outputinputctrl::SetMU001(int Value)
{
  //Serial.println("Setting Mu001");
}
void outputinputctrl::SetMU002(int Value)
{
 //Serial.println("Setting Mu002"); 
}
//void outputinputctrl::SetMU003(bool Value)
//{
// Serial.println("Setting Mu003"); 
//}
//Checking the trips and interlocks to know what 
void outputinputctrl::sensorToOutput(uint16_t* holdingReg)
{
  //check the H and HH thresholds-set alrams accordingly
//  for(int i = 0; i<TotalThresholdSensors;i++)
//  {
//    if(sensorTable[modbus.convert(rows,col,i,SensorValue)]>=sensorTable[modbus.convert(rows,col,i,HTHRESH)])
//    {
//      if(sensorTable[modbus.convert(rows,col,i,SensorValue)]>=sensorTable[modbus.convert(rows,col,i,HHTHRESH)])
//      {
//        sensorTable[modbus.convert(rows,col,i,AlarmStatus)]== 1;
//      }
//      else
//      {
//        sensorTable[modbus.convert(rows,col,i,AlarmStatus)]== 0;
//      }
//    }
//    //check the lower thresholds and set the alarms accordingly
//    else if(sensorTable[modbus.convert(rows,col,i,SensorValue)]<=sensorTable[modbus.convert(rows,col,i,LTHRESH)])
//    {
//      if(sensorTable[modbus.convert(rows,col,i,SensorValue)]<=sensorTable[modbus.convert(rows,col,i,LLTHRESH)])
//      {
//        sensorTable[modbus.convert(rows,col,i,AlarmStatus)]== 3;
//      }
//      else
//      {
//        sensorTable[modbus.convert(rows,col,i,AlarmStatus)]== 2;
//      }      
//    }
//    else
//    {
//      sensorTable[modbus.convert(rows,col,i,AlarmStatus)]== 4;
//    }
//  }
//  //go through the alarm table and act out the trip information.
//  for(int i = 0; i<TotalThresholdSensors;i++)
//  {
//    if(sensorTable[modbus.convert(rows,col,i,AlarmStatus)]==1)
//    {
//      byte OutputData[4];
//      OutputData[0]= sensorTable[modbus.convert(rows,col,i,ControlVar0)];
//      OutputData[1]= sensorTable[modbus.convert(rows,col,i,ControlVar1)];
//      OutputData[2]= sensorTable[modbus.convert(rows,col,i,ControlVar2)];
//      OutputData[3]= sensorTable[modbus.convert(rows,col,i,ControlVar3)];
//      int PushtoHardware[TotalOutputs];
//      for(int x = 0;x<4;x++)
//      {
//        for(int y = 0;y<8;y++)
//        {
//          PushtoHardware[(x*8)+y]=(OutputData[x]>>(8-y))&0xFE;
//        }
//      }
//      updateHardwareOutputs(PushtoHardware);
//   
//    }
//    if(sensorTable[modbus.convert(rows,col,i,AlarmStatus)]==3)
//    {
//      byte OutputData[4];
//      OutputData[0]= sensorTable[modbus.convert(rows,col,i,ControlVar4)];
//      OutputData[1]= sensorTable[modbus.convert(rows,col,i,ControlVar5)];
//      OutputData[2]= sensorTable[modbus.convert(rows,col,i,ControlVar6)];
//      OutputData[3]= sensorTable[modbus.convert(rows,col,i,ControlVar7)];
//      int PushtoHardware[TotalOutputs];
//      for(int x = 0;x<4;x++)
//      {
//        for(int y = 0;y<8;y++)
//        {
//          PushtoHardware[(x*8)+y]=(OutputData[x]>>(8-y))&0xFE;
//        }
//      }
//      updateHardwareOutputs(PushtoHardware);
//   
//    }
//    
//  }
    
}
void outputinputctrl::updateHardwareInputs(uint16_t* holdingReg)
{
  // Serial.print(" in hardwareinputs update sync:");
  // Serial.println(holdingReg[ValveStatus],BIN);
  int ValvePins[] = {0,1,3,4,10,11};
  int SwitchPins[] = {2,5,6,7,8,9,12,13,14,15};
  //sensorTable[convert(rows,col,AT001,SensorValue)]=Buffer[0];
 // Serial.println("reading digital inputs");
     int Test = digitalInputsPins[ValvePins[0]][1];
   // Serial.println(Test,DEC);
  for (int i = 0; i <6; i++) {
    //digitalInputs[i] = digitalRead(digitalInputsPins[i]);

      bool input=digitalRead(digitalInputsPins[ValvePins[i]][0]);
      bitWrite(holdingReg[ValveStatus],digitalInputsPins[ValvePins[i]][1],!input);
     // Serial.println(holdingReg[ValveStatus],BIN);
  }
  
  for (int i = 0; i < 10; ++i) {
    //digitalInputs[i] = digitalRead(digitalInputsPins[i]);

    if(!(digitalInputsPins[i][1]>=TotalSensors))
    {
      bool input=digitalRead(digitalInputsPins[SwitchPins[i]][0]);
      bitWrite(holdingReg[LevelSwitchesReg],digitalInputsPins[SwitchPins[i]][1],input);
      
    }
  }
  
  for (int i = 0; i < numAnalogInputs; ++i) {
   // analogInputs[i] = analogRead(analogInputsPins[i][0]);
   //modbus.convert(rows,col,analogInputsPins[i][1],SensorValue)
    int analogsensor = analogRead(analogInputsPins[i][0]);
    if(analogInputsPins[i][1]==TT001||analogInputsPins[i][1]==TT002||analogInputsPins[i][1]==TT003)
    {
      //slope = -0.18
      // intercept = 110.89
      if(analogInputPins[i][1]== TT002)
      {
        Serial.println();
        Serial.print("Temperature for TT002: ");
        Serial.println(analogsensor);
      }
      for(int x = 0; x<81;x++)
      {
        if(analogsensor>tempDEC[x])
        {
          holdingReg[analogInputsPins[i][1]]=x;
          break;
        }
      }
      //100 scaling factor for temp.
      //holdingReg[TT001]=var;
    }
/*     else if(analogInputsPins[i][1]==TT002)
    {
      //slope = -0.13
      // intercept = 95.06
      holdingReg[TT002]=analogsensor;
      float var = analogsensor*(-0.13);
      Serial.print(" Temp 002");
      Serial.print(var,DEC);
      var = var+95.06;
      Serial.print("  ");
      Serial.print(var,DEC);
      var = var * 100;
      Serial.print("  ");
      Serial.println(var,DEC);
      //100 scaling factor for temp.
      //holdingReg[TT002]=var;

    }
    else if(analogInputsPins[i][1]==TT003)
    {
      //slope = -0.15
        // intercept = 100.08
        holdingReg[TT003]=analogsensor;
        float var = analogsensor*(-0.15);
        Serial.print(" Temp 003");
        Serial.print(var,DEC);
        var = var+100.08;
        Serial.print("   ");
        Serial.print(var,DEC);
        var = var * 100;
        Serial.print("  ");
        Serial.println(var,DEC);
        //100 scaling factor for temp.
       // holdingReg[TT003]=var;

    } */
    else{
      if(analogInputsPins[i][1]==AT004ABC)
      {
        if(analogsensor>100)
        {
          holdingReg[analogInputsPins[i][1]]= 1;
        }
        else{
          holdingReg[analogInputsPins[i][1]]=0;
        }
      }
      else if(analogInputsPins[i][1]==AT005ABC)
      {
        if(analogsensor>100)
        {
          holdingReg[analogInputsPins[i][1]]= 1;
        }
        else{
          holdingReg[analogInputsPins[i][1]]=0;
        }

      }
      else
      {
        holdingReg[analogInputsPins[i][1]]=analogsensor;//analogRead(analogInputsPins[i][0]);
      }
    }
   //SensorsArray[analogInputsPins[i][1]][SensorValue]=analogRead(analogInputsPins[i][0]);
  }
//  Serial.print("hardwareinputs at end sync:");
//  Serial.println(holdingReg[ValveStatus],DEC);  

  //22
  
}
int outputinputctrl::ChangingBit(int Value,int place,bool value)
{
  if(value)
  {
    return value |= 1UL << place;
  }
  else
  {
    return value &= ~(1UL << place);
  }
}
//TODO: write a function that will check the status of the outputs
int outputinputctrl::updateHardwareStatus(int OutputStatus[])
{
  
}
int outputinputctrl::updateHardwareOutputs(int OutputCtrl[])
{
  int ValveErrorValue=0;
  if(!SetXV001(OutputCtrl[XV001ctrl]))
  {
    ValveErrorValue=ValveErrorValue+1;
  }
  if(!SetXV002(OutputCtrl[XV002ctrl]))
  {
    ValveErrorValue=ValveErrorValue+2;
  }
  if(!SetXV003(OutputCtrl[XV003ctrl]))
  {
    ValveErrorValue=ValveErrorValue+4;
  }
  if(!SetXV004(OutputCtrl[XV004ctrl]))
  {
    ValveErrorValue=ValveErrorValue+8;
  }
  if(!SetXV009(OutputCtrl[XV009ctrl]))
  {
    ValveErrorValue=ValveErrorValue+16;
  }
  if(!SetXV010(OutputCtrl[XV010ctrl]))
  {
    ValveErrorValue=ValveErrorValue+32;
  }
  if(!SetXV011(OutputCtrl[XV011ctrl]))
  {
    ValveErrorValue=ValveErrorValue+64;
  }
  if(!SetXV012(OutputCtrl[XV012ctrl]))
  {
    ValveErrorValue=ValveErrorValue+128;
  }
  if(!SetXV013(OutputCtrl[XV013ctrl]))
  {
    ValveErrorValue=ValveErrorValue+256;
  }
  if(!SetXV014(OutputCtrl[XV014ctrl]))
  {
    ValveErrorValue=ValveErrorValue+512;
  }
  if(!SetXV015(OutputCtrl[XV015ctrl]))
  {
    ValveErrorValue=ValveErrorValue+1024;
  }
  if(!SetXV016(OutputCtrl[XV016ctrl]))
  {
    ValveErrorValue=ValveErrorValue+2048;
  }
  if(!SetXV017(OutputCtrl[XV017ctrl]))
  {
    ValveErrorValue=ValveErrorValue+4096;
  }
  if(!SetXV018(OutputCtrl[XV018ctrl]))
  {
    ValveErrorValue=ValveErrorValue+8192;
  }
  if(!SetXV019(OutputCtrl[XV019ctrl]))
  {
    ValveErrorValue=ValveErrorValue+16384;
  }
  SetPC003(OutputCtrl[PC003]);
  SetPC005(OutputCtrl[PC005]);
  SetPC006(OutputCtrl[PC006]);
  SetPC007(OutputCtrl[PC007]);
  SetMU001(OutputCtrl[MU001]);
  SetMU002(OutputCtrl[MU002]);
  SetPC001(OutputCtrl[PC001]);
  SetPC002(OutputCtrl[PC002]);
  SetPC004(OutputCtrl[PC004]);
  //memset(buff,true,sizeof(buff));
  
  if(modbusoutputtransmit)
  {
    int i = 0;
    while(!modbus.WriteOutputs(buff)&&i++<10)delay(50);
    
  
  }
  modbusoutputtransmit=false;

    if(VFDSpeed[0]!=VFDP[0])
    {
      VFDP[0]=VFDSpeed[0];
      if(VFDSpeed[0]== 0)
      {
        vfd1start = false;
        int i = 0;
        while(!modbus.StopVFD1()&&i++<10)delay(50);
        modbus.prit("Stopping VFD1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
      }
      else if(vfd1start)
      {
        int i = 0;
        while(!modbus.SpeedVFD1(VFDSpeed[0])&&i++<10)delay(50);
        modbus.prit("Updating Speed for VFD1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
      }
      else
      {
        VFDP[0] = 1;
        vfd1start = true;
        int i = 0;
        while(!modbus.StartVFD1()&&i++<10)delay(50);
        modbus.prit("Starting VFD1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
        

      }
    }
    if(VFDSpeed[1]!=VFDP[1])
    {
      VFDP[1]=VFDSpeed[1];
      if(VFDSpeed[1]== 0)
      {
        vfd2start = false;
        int i = 0;
        while(!modbus.StopVFD2()&&i++<10)delay(50);
        modbus.prit("Stopping VFD2\n");
      }
      else if(vfd2start)
      {
        int i = 0;
        while(!modbus.SpeedVFD2(VFDSpeed[1])&&i++<10)delay(50);
        modbus.prit("Updating Speed for VFD2\n");
      }
      else
      {
        VFDP[1] = 1;
        vfd2start = true;
        int i = 0;
        while(!modbus.StartVFD2()&&i++<10)delay(50);
        modbus.prit("Starting VFD2 \n");
        

      }
    }
    if(VFDSpeed[2]!=VFDP[2])
    {
      VFDP[2]=VFDSpeed[2];
      if(VFDSpeed[2]== 0)
      {
        vfd3start = false;
        int i = 0;
        while(!modbus.StopVFD3()&&i++<10)delay(50);
        modbus.prit("Stopping VFD3\n");
      }
      else if(vfd3start)
      {
        int i = 0;
        while(!modbus.SpeedVFD3(VFDSpeed[2])&&i++<10)delay(50);
        modbus.prit("Updating Speed for VFD3\n");
      }
      else
      {
        VFDP[2] = 1;
        vfd3start = true;
        int i = 0;
        while(!modbus.StartVFD3()&&i++<10)delay(50);
        modbus.prit("Starting VFD3 \n");
        

      }
    }      
 
}
