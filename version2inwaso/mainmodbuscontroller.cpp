#include "mainmodbuscontroller.h"

    //EthernetClient slave;
    
    ModbusRTUMaster master(RS485);
    
   // bool UpdateTableFromRaptor(char **sensorarray);
   // bool UpdateTableFromEEPROM(char **sensorarray);
 // Ethernet configuration values

  
  // Define the ModbusTCPMaster object
  
    //bool coils[NUM_COILS]={false};
    // Ethernet client object used to connect to the slave
    
    uint32_t lastSentTime = 0UL;
    uint32_t lastSentTimeDiscreteInputs = 0UL;
    uint32_t lastSentTimeOutput = 0UL;   
  #define DEBUG
mainmodbuscontroller::mainmodbus(uint16_t* _raptorholdingReg,int _sizeofHoldReg)
{
 // Serial.begin(115200);
 // Serial.println("Test");
 
// Serial.println(Ethernet.localIP());
 //allocate modbus space for Raptor input

}
bool mainmodbuscontroller::raptorStart(uint16_t* _raptorholdingReg,int _sizeofHoldReg)
{
  RS485.begin(9600UL, HALFDUPLEX, SERIAL_8E1);
  master.begin(9600UL);

}
/*
 * raptorsync step one: Update holding registor from raptors.
 * Check for update thresholds
 * Update Thresholds
 */
bool mainmodbuscontroller::raptorSync(uint16_t* _raptorholdingReg,int* _outputctrl,int* _outputsatus)
{

for(int i = 0; i < 15; i ++)
{

  _outputctrl[i] = bitRead(_raptorholdingReg[ValveControl],i);
  if(_outputctrl[i]==1)
  {
    prit("1");
  }
  else
  {
    prit("0");
  }


}
prit("\n");
//extras control
// for(int i = 0; i < 11; i ++)
// {
//   _outputctrl[i+15] =bitRead(_raptorholdingReg[ExtrasControl],i);
  
// }
/*copying from interlock cpp*/
 // testLT001(raptorholdingReg,_outputctrl);
  
  testINT1(_raptorholdingReg,_outputctrl);
  testINT2(_raptorholdingReg,_outputctrl);
 // testAT001(_raptorholdingReg,_outputctrl);
 // testINT36(_raptorholdingReg,_outputctrl);
  testINT3(_raptorholdingReg,_outputctrl);
  testINT4(_raptorholdingReg,_outputctrl);
  //testINT7(_raptorholdingReg,_outputctrl);
 // testINT8(_raptorholdingReg,_outputctrl);
 // testINT26(_raptorholdingReg,_outputctrl);
 // testINT27(_raptorholdingReg,_outputctrl);
  testINT28(_raptorholdingReg,_outputctrl);
  testINT29(_raptorholdingReg,_outputctrl);
//  testLT016(_raptorholdingReg,_outputctrl);
//  testAT006(_raptorholdingReg,_outputctrl);
  testINT34(_raptorholdingReg,_outputctrl);
  testINT35(_raptorholdingReg,_outputctrl);
//  testLT010(_raptorholdingReg,_outputctrl);
  testINT30(_raptorholdingReg,_outputctrl);
  testINT31(_raptorholdingReg,_outputctrl);
  testINT32(_raptorholdingReg,_outputctrl);
  testINT33(_raptorholdingReg,_outputctrl);
//  testLT013(raptorholdingReg,_outputctrl);

 /*this was the already implemented part*/ 
/* if(bitRead(_raptorholdingReg[LevelSwitchesReg],LSLL015))
 {  
   _outputctrl[PC003] = bitRead(_raptorholdingReg[ExtrasControl],PC003ctrl);
 }
 else
 {
  _outputctrl[PC003]=0;
 }
//_outputctrl[PC003] = bitRead(_raptorholdingReg[ExtrasControl],PC003ctrl);
if(!bitRead(_raptorholdingReg[LevelSwitchesReg],LSLL017))
{
  _outputctrl[PC005] = bitRead(_raptorholdingReg[ExtrasControl],PC005ctrl);
}
else
{
_outputctrl[PC005] = 0;
}
 if(!bitRead(_raptorholdingReg[LevelSwitchesReg],LSLL004))
 {
  if(bitRead(_raptorholdingReg[ExtrasControl],PC006ctrl))
  {
    _outputctrl[PC006] = 1;
    Serial.print("Pump 6 on!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
  }
  else
  {
    Serial.print("Pump 6 = off \n");
    _outputctrl[PC006] = 0;
  }
 }else
 {
    _outputctrl[PC006] = 0;
 }
  // _outputctrl[PC006] = bitRead(_raptorholdingReg[ExtrasControl],PC006ctrl);
 if(!bitRead(_raptorholdingReg[LevelSwitchesReg],LSLL005))
 {  
   _outputctrl[PC007] = bitRead(_raptorholdingReg[ExtrasControl],PC007ctrl);
 }
 else
 {
  _outputctrl[PC007]=0;
 }
  if(bitRead(_raptorholdingReg[LevelSwitchesReg],LSLL003))
 {  
  Serial.print(" PC001 =");
  Serial.println(_raptorholdingReg[PC001CTRL]);  
   _outputctrl[PC001]=_raptorholdingReg[PC001CTRL];
   _outputcontrol[XV002ctrl]=0;
 }
 else
 {
  _outputctrl[PC001]=0;
 }
  if(bitRead(_raptorholdingReg[LevelSwitchesReg],LSLL012))
 {  
  Serial.print(" PC002 =");
  Serial.println(_raptorholdingReg[PC002CTRL]);
  _outputctrl[PC002]=_raptorholdingReg[PC002CTRL];
 }
 else
 {
  Serial.print("pc002 offffffffffffffffffffff\n");
  _outputctrl[PC002]=0;
 }



if(bitRead(_raptorholdingReg[LevelSwitchesReg],LSLL008))
{
  _outputctrl[PC004]=_raptorholdingReg[PC004CTRL];
  Serial.print("Pump 4 can be controlled:   ");
  Serial.println(_outputctrl[PC004]);
  //prit("PC004 = 0 \n");
}
else
{
  //prit("PC004 2= ");
  Serial.println("Pump 4 off due to a level switch");
  _outputctrl[PC004]=0;
}*/

 
  return true;
}

bool mainmodbuscontroller::modbusSync(uint16_t* holdingReg)
{
  //prit("Reading modbus inputs \n");
  int x = 0;
  while(!ReadInputs(holdingReg)&&x<10)
  {
    //prit("1");
    delay(50);
    x++;
  }
  x=0;
  //prit("Reading modbus analog input \n");
  while(!ReadAnalogs(holdingReg)&&x<10)
  {
    //Serial.print(x,DEC);
    x++;
    delay(50);
  }
  x=0;
 // prit("Reading VFD1 \n");
  while(!ReadVFD1(holdingReg)&&x<10)
  {
    //prit("f1");
    x++;
    delay(50);
  }
  x=0;
  //prit("Reading VFD2 \n");
  while(!ReadVFD2(holdingReg)&&x<10)
  {
    //prit("f2");
    x++;
    delay(50);
  }
  x=0;
  //prit("Reading VFD3 \n");
  while(!ReadVFD3(holdingReg)&&x<10)
  {
    //prit("f3");
    x++;
    delay(50);
  }

  return true;

}

bool mainmodbuscontroller:: ReadInputs(uint16_t* holdingReg)
{
  if(!_InputRequest)
  {
    master.readDiscreteInputs(31, 0, 14);
    _InputRequest = true;
  }
  if(_InputRequest)
  {
    if(master.isWaitingResponse())
    { 
    ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
            uint16_t TempBuff2[NUM_DISCRETE_INPUTS]={0};
            for (int i = 0; i < NUM_DISCRETE_INPUTS; ++i) 
            {
                TempBuff2[i]=response.isCoilSet(i);
          
            }

            UpdateSlaveInputs(TempBuff2,holdingReg);
            _InputRequest = false;
            return true;
        }
      }   
    }
  }
  return false;
}
bool mainmodbuscontroller:: ReadAnalogs(uint16_t* holdingReg)
{
  
  if(!_AnalogRequest)
  {
    master.readInputRegisters(31,0,15);
    _AnalogRequest = true;
  }
  if(_AnalogRequest)
  {
    if(master.isWaitingResponse())
    { 
      ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
          uint16_t TempBuff[NUM_INPUT_REGISTERS];
          for (int i = 0; i < NUM_INPUT_REGISTERS; ++i) 
          {
            TempBuff[i]=response.getRegister(i);
          }
          UpdateSlavemA(TempBuff,holdingReg);
          _AnalogRequest = false;
          prit("Sucesfull analog Read:\n");
          return true;
        }
      }
  
    }
  }
  
  return false;
}
bool mainmodbuscontroller::WriteOutputs(bool coils[NUM_COILS])
{
  if(!_WriteOutputs)
  {
    master.writeMultipleCoils(31, 0, coils,NUM_COILS);
    _WriteOutputs = true;
  }
  if(_WriteOutputs)
  {
    if(master.isWaitingResponse())
    { 
      ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
          _WriteOutputs = false;
          return true;
        }
      }
    
    }
  }
  return false;
}
bool mainmodbuscontroller::ReadVFD1(uint16_t* holdingReg)
{
  if(!_readvfd1)
  {
    master.readHoldingRegisters(1,23,1);
    _readvfd1 = true;
  }
  if(_readvfd1)
  {
    if(master.isWaitingResponse())
    { 
      ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
          //Serial.print("Response from VFD1: ");
          holdingReg[PC001Speed]=response.getRegister(0);;
          //Serial.println(in);    
          _readvfd1 = false;
          return true;
        }
      }
    
    }
  }
  return false;
}
bool mainmodbuscontroller::ReadVFD2(uint16_t* holdingReg)
{
  if(!_readvfd2)
  {
    master.readHoldingRegisters(2,23,1);
    _readvfd2 = true;
  }
  if(_readvfd2)
  {
    if(master.isWaitingResponse())
    { 
      ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
          //Serial.print("Response from VFD2: ");
          uint16_t in = response.getRegister(0);
          holdingReg[PC002Speed]=in;
          //Serial.println(in);    
          _readvfd2 = false;
          return true;
        }
      }
    
    }
  }
  return false;
}
bool mainmodbuscontroller::ReadVFD3(uint16_t* holdingReg)
{
  if(!_readvfd3)
  {
    master.readHoldingRegisters(4,23,1);
    _readvfd3 = true;
  }
  if(_readvfd3)
  {
    if(master.isWaitingResponse())
    { 
      ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
          Serial.println();
          Serial.print("Response from VFD3: ");
          
          uint16_t in = response.getRegister(0);
          holdingReg[PC004Speed]=in;
          Serial.println(in);    
          _readvfd3 = false;
          return true;
        }
      }
    
    }
  }
  return false;
}
bool mainmodbuscontroller::StartVFD1()
{
  if(!_startvfd1)
  {
    master.writeSingleRegister(1, 99, 1151);
    _startvfd1 = true;
  }
  if(_startvfd1)
  {
    if(master.isWaitingResponse())
    { 
      ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
          _startvfd1 = false;
          return true;
        }
      }
    }
  }
  return false;
}
bool mainmodbuscontroller:: StartVFD2()
{
  if(!_startvfd2)
  {
    master.writeSingleRegister(2, 99, 1151);
    _startvfd2 = false;
  }
  if(_startvfd2)
  {
    if(master.isWaitingResponse())
    { 
      ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
          _startvfd2 = false;
          prit("successfully started pump 2");
          return true;
        }
      }
    }
  }
  return false;

}
bool mainmodbuscontroller:: StartVFD3()
{
  if(!_startvfd3)
  {
    master.writeSingleRegister(4, 99, 1151);
    _startvfd3 = true;
  }
  if(_startvfd3)
  {
    if(master.isWaitingResponse())
    { 
      ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
          _startvfd3 = false;
          return true;
        }
      }
    }
  }
  return false;

}
bool mainmodbuscontroller::StopVFD1()
{
  if(!_stopvfd1)
  {
    master.writeSingleRegister(1, 99, 1150);
    _stopvfd1 = true;
  }
  if(_stopvfd1)
  {
    if(master.isWaitingResponse())
    { 
      ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
          _stopvfd1 = false;
          return true;
        }
      }
    }
  }
  return false;

}
bool mainmodbuscontroller::StopVFD2()
{
  if(!_stopvfd2)
  {
    master.writeSingleRegister(2, 99, 1150);
    _stopvfd2 = false;
  }
  if(_stopvfd2)
  {
    if(master.isWaitingResponse())
    { 
      ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
          _stopvfd2 = false;
          prit("successfully stopped pump 2");
          return true;
        }
      }
    }
  }
  return false;

}
bool mainmodbuscontroller::StopVFD3()
{
  if(!_stopvfd3)
  {
    master.writeSingleRegister(4, 99, 1150);
    _stopvfd3 = true;
  }
  if(_stopvfd3)
  {
    if(master.isWaitingResponse())
    { 
      ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
          _stopvfd3 = false;
          return true;
        }
      }
    }
  }
  return false;


}
bool mainmodbuscontroller::SpeedVFD1(int speedset)
{
  unsigned int postvalue = map(speedset,0,100,34,68)*218.44;
  if(!_speedvfd1)
  {

    master.writeSingleRegister(1, 2, postvalue);
    _speedvfd1 = true;
  }
  if(_speedvfd1)
  {
    if(master.isWaitingResponse())
    { 
      ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
          _speedvfd1 = false;
          return true;
        }
      }
    }
  }
  return false;

}
bool mainmodbuscontroller::SpeedVFD2(int speedset)
{
  unsigned int postvalue = map(speedset,0,100,34,70)*327.7;
  if(!_speedvfd2)
  {
    prit("Updating speed---------------- \n");
    master.writeSingleRegister(2, 2, postvalue);
    _speedvfd2 = true;
  }
  if(_speedvfd2)
  {
    if(master.isWaitingResponse())
    { 
      ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
          _speedvfd2 = false;
          return true;
        }
      }
    }
  }
  return false;
  

}
bool mainmodbuscontroller::SpeedVFD3(int speedset)
{
  unsigned int postvalue = map(speedset,0,100,50,50)*327.7;
  if(!_speedvfd3)
  {

    master.writeSingleRegister(4, 2, postvalue);
    _speedvfd3 = true;
  }
  if(_speedvfd3)
  {
    if(master.isWaitingResponse())
    { 
      ModbusResponse response = master.available();
      if(response)
      {

        if(response.hasError())
        {
          Serial.println("Fault message");
        }
        else
        {
          _speedvfd3 = false;
          return true;
        }
      }
    }
  }
  return false;

}
      
                           
void mainmodbuscontroller::UpdateSlavemA(uint16_t *Buffer,uint16_t* holdingReg)
{
    float litervalue = 0;
    float ph001 = Buffer[0]*0.055 - 25.8194;
    if(ph001>14)
    {
      ph001 = 14;
    }else if(ph001<0)
    {
      ph001 = 0;
    }
     holdingReg[AT001] = ph001;

//   //Serial.println();                                                                     
//   //Serial.print("AT001 value:  ");
//   //Serial.println(Buffer[0]);
    float at002temp = Buffer[1]*0.0554;
    at002temp = 85.93 - at002temp;
    holdingReg[AT002] = at002temp*100;//map(Buffer[1],0,1023,0,199);

//   //Serial.println();                                                                     
//   //Serial.print("AT002 value:  ");
//   //Serial.println(Buffer[1]);
    float ph002 = Buffer[2]*0.055 - 25.8194;
    if(ph002>14)
    {
      ph002 = 14;
    }else if(ph002<0)
    {
      ph002 = 0;
    }
    holdingReg[AT006] = ph002;
 
//   //Serial.println();                                                                     
//   //Serial.print("AT006 value:  ");
//   //Serial.println(Buffer[2]);
    float at007temp = Buffer[3]*0.0554;
    at007temp = 85.93 - at007temp;
    holdingReg[AT007] = at007temp*100;//TODO: Rearange stuff - fix slave

//   //Serial.println();                                                                     
//   //Serial.print("AT007 value:  ");
//   //Serial.println(Buffer[3]);
    litervalue =Buffer[4] * 1.77;
    litervalue = litervalue- 267.74;
    if((litervalue<0)?litervalue=10:litervalue=litervalue);
    holdingReg[LT001] = litervalue;

//   //Serial.println();                                                                     
//   //Serial.print("LT001 value:  ");
//   //Serial.println(Buffer[4]);
    litervalue =Buffer[5] * 2.2455;
    litervalue = litervalue- 482.51497;
    if((litervalue<55)?litervalue=0:litervalue=litervalue);
    holdingReg[LT010] = litervalue;//Buffer[5];//litervalue;
 //  sensorTable[convert(rows,col,LT010,SensorValue)]=Buffer[4];
   litervalue =Buffer[6] * 2.3;
   litervalue = litervalue- 483.067;
   holdingReg[LT013] = litervalue;
//   litervalue = litervalue - 608;
//   sensorTable[convert(rows,col,LT013,SensorValue)]=litervalue;
//   //Serial.print("Liter value 1: ");
//   //Serial.print(litervalue);
//   //Serial.print(" mm");
   litervalue =Buffer[7] * 2.21788;
   litervalue = litervalue- 509.8581;
   if(litervalue>999||litervalue<0)
   {litervalue = 0;}
   holdingReg[LT016] = Buffer[7];//litervalue;

//   //Serial.println();                                                                     
//   //Serial.print("LT016 value:  ");
//   //Serial.println(Buffer[9]);
  float pt001 = (Buffer[8]*0.16) - 37.378;
    if(pt001>60)
    {
      pt001 = 60;
    }
    else if(pt001<0)
    {
      pt001 = 0;
    }
    
    holdingReg[PT001] = pt001;

//   //Serial.println();                                                                     
//   //Serial.print("PT001 value:  ");
//   //Serial.println(Buffer[10]);  
    float pt002 = Buffer[9]*0.14 - 31.79;
    if(pt002>60)
    {
      pt002 = 60;
    }
    else if(pt002<0)
    {
      pt002 = 0;
    }
    holdingReg[PT002] =pt002;
    float pt003 = Buffer[10]*0.11 - 10.48;
    if(pt003>60)
    {
      pt003 = 60;
    }
    else if(pt003<0)
    {
      pt003 = 0;
    }
    if(Buffer[10]>310)
    {
      bitWrite(holdingReg[ExtrasStatus],PC003ST,1);
    }
    else if(holdingReg[FT005FR]<1)
    {
      bitWrite(holdingReg[ExtrasStatus],PC003ST,0);
    }

//   //Serial.println();                                                                     
//   //Serial.print("PT002 value:  ");
//   //Serial.println(Buffer[11]);
   holdingReg[PT003] = pt003;

//   //Serial.println();                                                                     
//   //Serial.print("PT003 value:  ");
//   //Serial.println(Buffer[12]);
    float pt004 = Buffer[11]*0.1 - 15.75;
    if(pt004>10000)
    {
      pt004 = 10000;
    }
    else if(pt004<0)
    {
      pt004 = 0;
    }
    
    holdingReg[PT004] = pt004;
    float pt005 = Buffer[14]*0.144 - 36.93;
    if(pt005>60)
    {
      pt005 = 60;
    }
    else if(pt005<0)
    {
      pt005 = 0;
    }
    if(Buffer[14]>310)
    {
      bitWrite(holdingReg[ExtrasStatus],PC005ST,1);
    }
    else
    {
      bitWrite(holdingReg[ExtrasStatus],PC005ST,0);
    }
    holdingReg[PT005] = pt005;
    float pt006 = Buffer[12]* 0.21 - 91.97;
    if(pt006>80)
    {
      pt006 = 80;
    }
    else if(pt006<0)
    {
      pt006 = 0;
    }
    if(Buffer[12]>310)
    {
      bitWrite(holdingReg[ExtrasStatus],PC006ST,1);
    }
    else
    {
      bitWrite(holdingReg[ExtrasStatus],PC006ST,0);
    }
    holdingReg[PT006] = pt006;
    float pt007 = Buffer[13]*0.15 - 39.61;//*10.91 - 2500;
    if(pt007>10000)
    {
      pt007 = 10000;
    }
    else if(pt007<0)
    {
      pt007 = 0;
    }
    if(Buffer[13]>310)
    {
      bitWrite(holdingReg[ExtrasStatus],PC007ST,1);
    }
    else
    {
      bitWrite(holdingReg[ExtrasStatus],PC007ST,0);
    }
    holdingReg[PT007] = pt007;
}


void mainmodbuscontroller::UpdateSlaveInputs(uint16_t *Buffer,uint16_t* holdingReg)
{

   bitWrite(holdingReg[LevelSwitchesReg],LSLL017,Buffer[0]);
   bitWrite(holdingReg[LevelSwitchesReg],LSH018,Buffer[1]);
   bitWrite(holdingReg[LevelSwitchesReg],LSHH019,Buffer[2]);
   bitWrite(holdingReg[LevelSwitchesReg],LSH020,Buffer[3]);
   if(Buffer[4]>0?Buffer[4]=0:Buffer[4]=1);
   bitWrite(holdingReg[ValveStatus],XV001R,Buffer[4]);
   if(Buffer[11]>0?Buffer[11]=0:Buffer[11]=1);
   bitWrite(holdingReg[ValveStatus],XV002R,Buffer[11]);
   if(Buffer[6]>0?Buffer[6]=0:Buffer[6]=1);
   bitWrite(holdingReg[ValveStatus],XV003R,Buffer[6]);
   if(Buffer[7]>0?Buffer[7]=0:Buffer[7]=1);
   bitWrite(holdingReg[ValveStatus],XV004R,Buffer[7]);
   if(Buffer[8]>0?Buffer[8]=0:Buffer[8]=1);
   bitWrite(holdingReg[ValveStatus],XV009R,Buffer[8]);
   if(Buffer[5]>0?Buffer[5]=0:Buffer[5]=1);
   bitWrite(holdingReg[ValveStatus],XV010R,Buffer[5]);
   if(Buffer[10]>0?Buffer[10]=0:Buffer[10]=1);
   bitWrite(holdingReg[ValveStatus],XV011R,Buffer[10]);
   if(Buffer[9]>0?Buffer[9]=0:Buffer[9]=1);
   bitWrite(holdingReg[ValveStatus],XV012R,Buffer[9]);
   if(Buffer[12]>0?Buffer[12]=0:Buffer[12]=1);
   bitWrite(holdingReg[ValveStatus],XV013R,Buffer[12]);
  //Serial.println(holdingReg[ValveStatus],BIN);
   
   /*sensorTable[convert(rows,col,LSLL017,SensorValue)]=Buffer[0];
   sensorTable[convert(rows,col,LSH018,SensorValue)]=Buffer[1];
   sensorTable[convert(rows,col,LSHH019,SensorValue)]=Buffer[2];
   sensorTable[convert(rows,col,LSH020,SensorValue)]=Buffer[3];
   sensorTable[convert(rows,col,XV001R,SensorValue)]=Buffer[4];
//   Serial.print("-----------------------------------");
//   Serial.println(Buffer[4],DEC);
   //Serial.println(sensorTable[convert(rows,col,XV001R,SensorValue)]);
   sensorTable[convert(rows,col,XV002R,SensorValue)]=Buffer[11];
   sensorTable[convert(rows,col,XV003R,SensorValue)]=Buffer[6];
   sensorTable[convert(rows,col,XV004R,SensorValue)]=Buffer[7];
   sensorTable[convert(rows,col,XV009R,SensorValue)]=Buffer[8];
   sensorTable[convert(rows,col,XV010R,SensorValue)]=Buffer[5];
   sensorTable[convert(rows,col,XV011R,SensorValue)]=Buffer[10];
   sensorTable[convert(rows,col,XV012R,SensorValue)]=Buffer[9];
   sensorTable[convert(rows,col,XV013R,SensorValue)]=Buffer[12];*/
   
   //4   
}

                 
void mainmodbuscontroller::prit(char* input)
{
  #ifdef DEBUG
  Serial.print(input);
  #endif
  return;
}
//old modbus sync code:
/* 
 // Serial.print(" Whos turn: ");
 // Serial.println(WhosTurn);
  int vfdresponse = 0;
  bool vfdsuccess = false;
  if(millis()>timestamp)
  {
  //Serial.print(" Whos turn: ");
  //Serial.println(WhosTurn);    
    timestamp=millis()+slaveRefresh;
    switch(WhosTurn){
    case 0:
    master.readInputRegisters(31,0,14);
    break;
    case 1:
        if(!master.readDiscreteInputs(31, 0, 14))
        {
          Serial.println("Read Discrete Inputs fail");
        }
    break;
    case 2:
      Serial.println("Sending command");
      if(!master.readHoldingRegisters(1,23,1))
      {
        Serial.println("Reading VFD 1 failed");
      }
    break;
    case 3:
      master.readHoldingRegisters(2,2,1);
   
    break;
    case 4:
      master.readHoldingRegisters(4,23,1);
    break;
    case 5:
      master.writeMultipleCoils(31, 0, coils,NUM_COILS);
    break;
    case 6:
        if(VFD[0]!=VFDP[0])
        {
          
          vfdresponse = 0;
           VFDP[vfdresponse]=VFD[vfdresponse];
          unsigned int postvalue = map(VFD[0],0,100,34,70)*327.7;
            if(VFD[0] ==1)
            {
              master.writeSingleRegister(1, 99, 1151);
            }
            else if(VFD[0]==0)
            {
              master.writeSingleRegister(1, 99, 1150);
        
            }
        }
     
        else if(VFD[1]!=VFDP[1])
        {
          //Serial.print("Change - pump 2");
          vfdresponse = 1;
          VFDP[vfdresponse]=VFD[vfdresponse];
          unsigned int postvalue = map(VFD[1],0,100,34,70)*327.7;

            //do vfd start command
            if(VFD[1] == 1) 
            {
              master.writeSingleRegister(2, 99, 1151);
   
            }
             else if(VFD[0] == 0){
                   
              master.writeSingleRegister(2, 99, 1150);
             }
                                            
    
        }

        else if(VFD[2]!=VFDP[2])
        {
          vfdresponse = 2;
           VFDP[vfdresponse]=VFD[vfdresponse];
          
          //Serial.println("Change - pump 4");
            if(VFD[2]==1)
            {
            //do vfd start command 
            if (!master.writeSingleRegister(4, 99,1151)) 
            {
              // Failure treatment
                
            }
            else{
               //Serial.println("Request vfd write 4 ON");               
            }
            }else if(VFD[2]==0)
            {
            if (!master.writeSingleRegister(4, 99,1150)) 
            {
              // Failure treatment
                
            }
            else{
               //Serial.println("Request vfd write 4 OFF");               
            }              
            }
          
        }
        else
        {
            WhosTurn = 0;
        }

      break;
      default:
      WhosTurn = 0;
      break;
    } */
    /*   }


  if(master.isWaitingResponse())
  {
    ModbusResponse response = master.available();
    if(response)
    {

      if(response.hasError())
      {
        Serial.println("Fault message");
      }
      else
      {
        Serial.println(WhosTurn);
        switch (WhosTurn){
              
        case 0:
          WhosTurn = 1;
          uint16_t TempBuff[NUM_INPUT_REGISTERS];
          for (int i = 0; i < NUM_INPUT_REGISTERS; ++i) 
          {
            TempBuff[i]=response.getRegister(i);
          }
          UpdateSlavemA(TempBuff,holdingReg);
          
          break;
        case 1:
          uint16_t TempBuff2[NUM_DISCRETE_INPUTS]={0};
          for (int i = 0; i < NUM_DISCRETE_INPUTS; ++i) 
          {
              TempBuff2[i]=response.isCoilSet(i);
         
          }

          UpdateSlaveInputs(TempBuff2,holdingReg);
          WhosTurn = 0;
        break;
        case 2:
          Serial.print("Response from VFD1: ");
          WhosTurn = 0;
          uint16_t in = response.getRegister(0);
          holdingReg[PC001]=in;
          Serial.println(in);          
        break;
        case 3:
          Serial.print("Response from VFD2: ");
          in = response.getRegister(0);
          holdingReg[PC002]=in;
          Serial.println(in);
          WhosTurn = 4;
        break;
        case 4:
          holdingReg[PC004]=response.getRegister(0);
          WhosTurn = 0;
        break;    
        case 5:
          WhosTurn = 0;
        break;
      case 6:
          VFDP[response]=VFD[response];
          WhosTurn = 2;
      break;   
      default:
      Serial.print("Whos Turn error: ");
      Serial.println(WhosTurn);
      WhosTurn = 0;
      break;        
    
      }
    } */
/*   }

  }
  else
  {
     if(outputupdate == true)
    {
      WhosTurn = 5;
    }
    if(vfdupdate == true)
    {
      WhosTurn = 6;
    }

  }

return true; */

////Serial.println("Test");
//  if (!slave.connected()) {
//    slave.stop();
//    slave.connect(slaveIp, slavePort);
//  }
// Send a request every 1000ms if connected to slave
void mainmodbuscontroller::testLT001(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(raptorholdingReg[LT001]>raptorholdingReg[LT001+HAlarmOffset] && raptorholdingReg[LT001]<raptorholdingReg[LT001+HHAlarmOffset] )
    {
      if(LT001>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],LT001-16,1);
        bitWrite(raptorholdingReg[AlarmHH2],LT001-16,0);
        bitWrite(raptorholdingReg[AlarmL2],LT001-16,0);
        bitWrite(raptorholdingReg[AlarmLL2],LT001-16,0);
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],LT001,1);
        bitWrite(raptorholdingReg[AlarmHH1],LT001,0);
        bitWrite(raptorholdingReg[AlarmL1],LT001,0);
        bitWrite(raptorholdingReg[AlarmLL1],LT001,0);
      }
    }
    else if (raptorholdingReg[LT001]>raptorholdingReg[LT001+HHAlarmOffset])
    {
      if(LT001>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],LT001-16,0);
        bitWrite(raptorholdingReg[AlarmHH2],LT001-16,1);
        bitWrite(raptorholdingReg[AlarmL2],LT001-16,0);
        bitWrite(raptorholdingReg[AlarmLL2],LT001-16,0);
        _outputcontrol[XV001ctrl]=0;
        _outputcontrol[XV011ctrl]=0; 
        _outputcontrol[XV013ctrl]=0; 
        _outputcontrol[XV016ctrl]=0; 
        _outputcontrol[XV018ctrl]=0; 
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],LT001,0);
        bitWrite(raptorholdingReg[AlarmHH1],LT001,1);
        bitWrite(raptorholdingReg[AlarmL1],LT001,0);
        bitWrite(raptorholdingReg[AlarmLL1],LT001,0);
        _outputcontrol[XV001ctrl]=0;
        _outputcontrol[XV011ctrl]=0; 
        _outputcontrol[XV013ctrl]=0; 
        _outputcontrol[XV016ctrl]=0; 
        _outputcontrol[XV018ctrl]=0; 
      }    
    }
    else if(raptorholdingReg[LT001]<raptorholdingReg[LT001+LAlarmOffset] && raptorholdingReg[LT001]>raptorholdingReg[LT001+LLAlarmOffset])
    {
      if(LT001>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],LT001-16,0);
        bitWrite(raptorholdingReg[AlarmHH2],LT001-16,0);
        bitWrite(raptorholdingReg[AlarmL2],LT001-16,1);
        bitWrite(raptorholdingReg[AlarmLL2],LT001-16,0);
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],LT001,0);
        bitWrite(raptorholdingReg[AlarmHH1],LT001,0);
        bitWrite(raptorholdingReg[AlarmL1],LT001,1);
        bitWrite(raptorholdingReg[AlarmLL1],LT001,0);
        
      }  
    }
    else if(raptorholdingReg[LT001]<raptorholdingReg[LT001+LLAlarmOffset])
    {
      if(LT001>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],LT001-16,0);
        bitWrite(raptorholdingReg[AlarmHH2],LT001-16,0);
        bitWrite(raptorholdingReg[AlarmL2],LT001-16,0);
        bitWrite(raptorholdingReg[AlarmLL2],LT001-16,1);
        _outputcontrol[XV002ctrl]=0;
        _outputcontrol[PC001] = 0; 
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],LT001,0);
        bitWrite(raptorholdingReg[AlarmHH1],LT001,0);
        bitWrite(raptorholdingReg[AlarmL1],LT001,0);
        bitWrite(raptorholdingReg[AlarmLL1],LT001,1);
        _outputcontrol[XV002ctrl]=0;
        _outputcontrol[PC001] = 0; 
      }  
      
    }

   }
void mainmodbuscontroller::testINT1(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSHH002))
  {
    bitWrite(raptorholdingReg[InterlockA],INT1,1);
    _outputcontrol[XV001ctrl]=0;
    _outputcontrol[XV011ctrl]=0; 
    _outputcontrol[XV013ctrl]=0; 
    _outputcontrol[XV016ctrl]=0; 
    _outputcontrol[XV018ctrl]=0; 
    prit("INTERLOCK: INT1 active \n"); 
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockA],INT1,0);
  }
  
}
void mainmodbuscontroller::testINT2(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSLL003))
  {
    bitWrite(raptorholdingReg[InterlockA],INT2,1);
    _outputcontrol[XV002ctrl]=0;
    _outputcontrol[PC001]= 0;
    raptorholdingReg[PC001CTRL] = 0;
   prit("INTERLOCK: INT2 active \n");    
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockA],INT2,0);
  }
}
void mainmodbuscontroller::testAT001(uint16_t* raptorholdingReg,int* _outputcontrol)
{

}
void mainmodbuscontroller::testINT36(uint16_t* raptorholdingReg,int* _outputcontrol)
{
 if(raptorholdingReg[TT001]>raptorholdingReg[TT001+HAlarmOffset] && raptorholdingReg[TT001]<raptorholdingReg[TT001+HHAlarmOffset] )
    {
      if(TT001>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],TT001-16,1);
        bitWrite(raptorholdingReg[AlarmHH2],TT001-16,0);

      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],TT001,1);
        bitWrite(raptorholdingReg[AlarmHH1],TT001,0);

      }
      bitWrite(raptorholdingReg[InterlockB],INT36,0);
    }
    else if (raptorholdingReg[TT001]>raptorholdingReg[TT001+HHAlarmOffset])
    {
      if(TT001>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],TT001-16,0);
        bitWrite(raptorholdingReg[AlarmHH2],TT001-16,1);
        bitWrite(raptorholdingReg[ExtrasControl],VER001ctrl,0);
        bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
        bitWrite(raptorholdingReg[InterlockB],INT36,1);  
        prit("INTERLOCK: INT36 active \n");    

      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],TT001,0);
        bitWrite(raptorholdingReg[AlarmHH1],TT001,1);
        bitWrite(raptorholdingReg[ExtrasControl],VER001ctrl,0);
        bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);     
        bitWrite(raptorholdingReg[InterlockB],INT36,1);
        prit("INTERLOCK: INT36 active \n"); 
      }    
    }
    else
    {
      bitWrite(raptorholdingReg[InterlockB],INT36,0);
    }    
}
void mainmodbuscontroller::testINT3(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSLL004))
  {
    bitWrite(raptorholdingReg[InterlockA],INT3,1);
    prit("INTERLOCK: INT3 active \n"); 
    bitWrite(raptorholdingReg[ExtrasControl],VER001ctrl,0);
    _outputcontrol[PC006] = 0;     
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockA],INT3,0);
  }
}
void mainmodbuscontroller::testINT4(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSLL005))
  {
    bitWrite(raptorholdingReg[InterlockA],INT4,1);
    prit("INTERLOCK: INT4 active \n");
    bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
    _outputcontrol[PC007] = 0;     
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockA],INT4,0);
  }
}
void mainmodbuscontroller::testINT7(uint16_t* raptorholdingReg,int* _outputcontrol)
{
 if(raptorholdingReg[TT002]>raptorholdingReg[TT002+HAlarmOffset] && raptorholdingReg[TT002]<raptorholdingReg[TT002+HHAlarmOffset] )
    {
      if(TT002>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],TT002-16,1);
        bitWrite(raptorholdingReg[AlarmHH2],TT002-16,0);

      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],TT002,1);
        bitWrite(raptorholdingReg[AlarmHH1],TT002,0);

      }
      bitWrite(raptorholdingReg[InterlockA],INT7,0);
    }
    else if (raptorholdingReg[TT002]>raptorholdingReg[TT002+HHAlarmOffset])
    {
      if(TT002>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],TT002-16,0);
        bitWrite(raptorholdingReg[AlarmHH2],TT002-16,1);
        bitWrite(raptorholdingReg[ExtrasControl],VER001ctrl,0);
        bitWrite(raptorholdingReg[InterlockA],INT7,1);
        prit("INTERLOCK: INT7 active \n"); 
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],TT002,0);
        bitWrite(raptorholdingReg[AlarmHH1],TT002,1);
        bitWrite(raptorholdingReg[ExtrasControl],VER001ctrl,0);
        bitWrite(raptorholdingReg[InterlockA],INT7,1);   
        prit("INTERLOCK: INT7 active \n");   
     
      }    
    }
    else
    {
      bitWrite(raptorholdingReg[InterlockA],INT7,0); 
    }
}
void mainmodbuscontroller::testINT8(uint16_t* raptorholdingReg,int* _outputcontrol)
{
 if(raptorholdingReg[TT003]>raptorholdingReg[TT003+HAlarmOffset] && raptorholdingReg[TT003]<raptorholdingReg[TT003+HHAlarmOffset] )
    {
      if(TT003>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],TT003-16,1);
        bitWrite(raptorholdingReg[AlarmHH2],TT003-16,0);

      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],TT003,1);
        bitWrite(raptorholdingReg[AlarmHH1],TT003,0);

      }
      bitWrite(raptorholdingReg[InterlockA],INT8,0);
    }
    else if (raptorholdingReg[TT003]>raptorholdingReg[TT003+HHAlarmOffset])
    {
      if(TT003>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],TT003-16,0);
        bitWrite(raptorholdingReg[AlarmHH2],TT003-16,1);
        bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
        bitWrite(raptorholdingReg[InterlockA],INT8,1); 
        prit("INTERLOCK: INT8 active \n"); 
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],TT003,0);
        bitWrite(raptorholdingReg[AlarmHH1],TT003,1);
        bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);   
        bitWrite(raptorholdingReg[InterlockA],INT8,1);  
        prit("INTERLOCK: INT8 active \n"); 
     
      }    
    }
    else
    {
      bitWrite(raptorholdingReg[InterlockA],INT8,0);   
    }
}
void mainmodbuscontroller::testINT26(uint16_t* raptorholdingReg,int* _outputcontrol)
{
if(raptorholdingReg[AT004ABC]>raptorholdingReg[AT004ABC+HAlarmOffset])
    {
      if(AT004ABC>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],AT004ABC-16,1);
        bitWrite(raptorholdingReg[AlarmHH2],AT004ABC-16,0);
        bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
        bitWrite(raptorholdingReg[ExtrasControl],VER001ctrl,0);
        bitWrite(raptorholdingReg[InterlockB],INT26,1); 
        prit("INTERLOCK: INT26 active \n"); 
        for(int i = 0; i<26; i++)
        {
          _outputcontrol[i]=0;
        }


      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],AT004ABC,1);
        bitWrite(raptorholdingReg[AlarmHH1],AT004ABC,0);
        bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
        bitWrite(raptorholdingReg[ExtrasControl],VER001ctrl,0);
        bitWrite(raptorholdingReg[InterlockB],INT26,1); 
        prit("INTERLOCK: INT26 active \n"); 
        for(int i = 0; i<26; i++)
        {
          _outputcontrol[i]=0;
        }

      }
      
    }
    else
    {
      bitWrite(raptorholdingReg[InterlockB],INT26,0);
    }

}
void mainmodbuscontroller::testINT27(uint16_t* raptorholdingReg,int* _outputcontrol)
{
if(raptorholdingReg[AT005ABC]>raptorholdingReg[AT005ABC+HAlarmOffset])
    {
      if(AT005ABC>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],AT005ABC-16,1);
        bitWrite(raptorholdingReg[AlarmHH2],AT005ABC-16,0);
        bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
        bitWrite(raptorholdingReg[ExtrasControl],VER001ctrl,0);
        bitWrite(raptorholdingReg[InterlockB],INT27,1); 
        prit("INTERLOCK: INT27 active \n"); 
        for(int i = 0; i<26; i++)
        {
          _outputcontrol[i]=0;
        }


      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],AT005ABC,1);
        bitWrite(raptorholdingReg[AlarmHH1],AT005ABC,0);
        bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
        bitWrite(raptorholdingReg[ExtrasControl],VER001ctrl,0);
        bitWrite(raptorholdingReg[InterlockB],INT27,1); 
        prit("INTERLOCK: INT27 active \n"); 
        for(int i = 0; i<26; i++)
        {
          _outputcontrol[i]=0;
        }

      }
      
    }
    else
    {
      bitWrite(raptorholdingReg[InterlockA],INT27,0);
    }
}
void mainmodbuscontroller::testINT28(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(bitRead(_raptorholdingReg[LevelSwitchesReg],LSLL008))
  {
    _outputctrl[PC004]=_raptorholdingReg[PC004CTRL];
    Serial.print("Pump 4 can be controlled:   ");
    Serial.println(_outputctrl[PC004]);
    //prit("PC004 = 0 \n");
  }
  else
  {
    //prit("PC004 2= ");
    //Serial.println("Pump 4 off due to a level switch");
    //_outputctrl[PC004]=0;
  }
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSLL008))
  {
    bitWrite(raptorholdingReg[InterlockB],INT28,1);
    prit("INTERLOCK: INT28 active \n"); 
    bitWrite(raptorholdingReg[InterlockB],INT29,0);
      // _outputcontrol[XV009ctrl]=0;
      // _outputcontrol[XV010ctrl]=0; 
      // _outputcontrol[XV011ctrl]=0; 
      // _outputcontrol[XV019ctrl]=0; 
    
      //raptorholdingReg[PC004CTRL] = 0;
      _outputcontrol[PC004]=0;
      prit("Interlock 28 ACTIVATED PC004 SHOULD STOP\n");

  }
  else
  {
    //if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSHH009))
    bitWrite(raptorholdingReg[InterlockB],INT28,0);
    _outputctrl[PC004]=_raptorholdingReg[PC004CTRL];
    Serial.print("Pump 4 can be controlled:   ");
    Serial.println(_outputctrl[PC004]);
  }
}
void mainmodbuscontroller::testINT29(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSHH009))
  {
    bitWrite(raptorholdingReg[InterlockB],INT29,1);
    prit("INTERLOCK: INT29 active \n");
    bitWrite(raptorholdingReg[InterlockB],INT28,0);
    //bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
    // _outputcontrol[PC001] = 0; 
    // _outputcontrol[PC002] = 0;
    // _outputcontrol[XV002ctrl] = 0;
    // _outputcontrol[XV003ctrl] = 0;
    // _outputcontrol[XV004ctrl] = 0;
    // _outputcontrol[XV009ctrl] = 0;
    // _outputcontrol[XV010ctrl] = 0;
    // _outputcontrol[XV011ctrl] = 1;
    // _outputcontrol[XV017ctrl] = 0;
    // _outputcontrol[XV019ctrl] = 0;
    
    if(raptorholdingReg[PC004CTRL] >1)
    {
      
      //bitWrite(raptorholdingReg[ValveControl],XV011ctrl,1);
      if(!bitRead(raptorholdingReg[ValveControl],XV009ctrl)||!bitRead(raptorholdingReg[ValveControl],XV010ctrl)||!bitRead(raptorholdingReg[ValveControl],XV011ctrl)||!bitRead(raptorholdingReg[ValveControl],XV019ctrl))
      {
        bitWrite(raptorholdingReg[ValveControl],XV011ctrl,1);
      }
      _outputcontrol[PC004]=raptorholdingReg[PC004CTRL]; 
      //prit("Interlock 29 ACTIVATED PC004 SHOULD START");
    }
    else
    {
        //prit("Interlock 29 ACTIVATED PC004 wont start, valves will close");
        bitWrite(raptorholdingReg[InterlockB],INT29,1);
        _outputcontrol[XV002ctrl] = 0;
        _outputcontrol[XV003ctrl] = 0;
        _outputcontrol[XV004ctrl] = 0;
        _outputcontrol[XV009ctrl] = 0;
        _outputcontrol[XV010ctrl] = 0;
        _outputcontrol[XV011ctrl] = 0;
        _outputcontrol[XV017ctrl] = 0;
        _outputcontrol[XV019ctrl] = 0;
        _outputcontrol[PC001]     = 0;
        _outputcontrol[PC002]     = 0;      

    }
    
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockB],INT29,0);
  }
}
void mainmodbuscontroller::testLT016(uint16_t* raptorholdingReg,int* _outputcontrol)
{

}
void mainmodbuscontroller::testAT006(uint16_t* raptorholdingReg,int* _outputcontrol)
{

}
void mainmodbuscontroller::testINT34(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSLL017))
  {
    bitWrite(raptorholdingReg[InterlockB],INT34,1);
    prit("INTERLOCK: INT34 active \n");
    //bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
    _outputcontrol[XV012ctrl] = 0;     
    _outputcontrol[XV013ctrl] = 0;
    _outputcontrol[PC005] = 0;
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockB],INT34,0);
  }
}
void mainmodbuscontroller::testINT35(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSHH019))
  {
    bitWrite(raptorholdingReg[InterlockB],INT35,1);
    prit("INTERLOCK: INT35 active \n");
    bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
    bitWrite(raptorholdingReg[ExtrasControl],VER001ctrl,0);
    _outputcontrol[PC001] = 0; 
    _outputcontrol[PC002] = 0;
    _outputcontrol[PC003] = 0;
    _outputcontrol[PC004] = 0;
    _outputcontrol[PC006] = 0;
    _outputcontrol[PC007] = 0;
    _outputcontrol[MU001] = 0;
    _outputcontrol[MU002] = 0;
    _outputcontrol[XV001ctrl] = 0;
    _outputcontrol[XV002ctrl] = 0;
    _outputcontrol[XV003ctrl] = 0;
    _outputcontrol[XV004ctrl] = 0;
    _outputcontrol[XV009ctrl] = 0;
    _outputcontrol[XV010ctrl] = 0;
    _outputcontrol[XV011ctrl] = 0;
    _outputcontrol[XV014ctrl] = 0;
    _outputcontrol[XV015ctrl] = 0;
    _outputcontrol[XV016ctrl] = 0;
    _outputcontrol[XV017ctrl] = 0;
    _outputcontrol[XV018ctrl] = 0;
    _outputcontrol[XV019ctrl] = 0;
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockB],INT35,0);
  }
}
void mainmodbuscontroller::testLT010(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(raptorholdingReg[LT010]>raptorholdingReg[LT010+HAlarmOffset] && raptorholdingReg[LT010]<raptorholdingReg[LT010+HHAlarmOffset] )
    {
      if(LT010>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],LT010-16,1);
        bitWrite(raptorholdingReg[AlarmHH2],LT010-16,0);
        bitWrite(raptorholdingReg[AlarmL2],LT010-16,0);
        bitWrite(raptorholdingReg[AlarmLL2],LT010-16,0);
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],LT010,1);
        bitWrite(raptorholdingReg[AlarmHH1],LT010,0);
        bitWrite(raptorholdingReg[AlarmL1],LT010,0);
        bitWrite(raptorholdingReg[AlarmLL1],LT010,0);
      }
    }
    else if (raptorholdingReg[LT010]>raptorholdingReg[LT010+HHAlarmOffset])
    {
      if(LT010>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],LT010-16,0);
        bitWrite(raptorholdingReg[AlarmHH2],LT010-16,1);
        bitWrite(raptorholdingReg[AlarmL2],LT010-16,0);
        bitWrite(raptorholdingReg[AlarmLL2],LT010-16,0);
        _outputcontrol[XV001ctrl]=0;
        _outputcontrol[XV011ctrl]=0; 
        _outputcontrol[XV013ctrl]=0; 
        _outputcontrol[XV016ctrl]=0; 
        _outputcontrol[XV018ctrl]=0; 
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],LT010,0);
        bitWrite(raptorholdingReg[AlarmHH1],LT010,1);
        bitWrite(raptorholdingReg[AlarmL1],LT010,0);
        bitWrite(raptorholdingReg[AlarmLL1],LT010,0);
        _outputcontrol[XV001ctrl]=0;
        _outputcontrol[XV011ctrl]=0; 
        _outputcontrol[XV013ctrl]=0; 
        _outputcontrol[XV016ctrl]=0; 
        _outputcontrol[XV018ctrl]=0; 
      }    
    }
    else if(raptorholdingReg[LT010]<raptorholdingReg[LT010+LAlarmOffset] && raptorholdingReg[LT010]>raptorholdingReg[LT010+LLAlarmOffset])
    {
      if(LT010>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],LT010-16,0);
        bitWrite(raptorholdingReg[AlarmHH2],LT010-16,0);
        bitWrite(raptorholdingReg[AlarmL2],LT010-16,1);
        bitWrite(raptorholdingReg[AlarmLL2],LT010-16,0);
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],LT010,0);
        bitWrite(raptorholdingReg[AlarmHH1],LT010,0);
        bitWrite(raptorholdingReg[AlarmL1],LT010,1);
        bitWrite(raptorholdingReg[AlarmLL1],LT010,0);
        
      }  
    }
    else if(raptorholdingReg[LT010]<raptorholdingReg[LT010+LLAlarmOffset])
    {
      if(LT010>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],LT010-16,0);
        bitWrite(raptorholdingReg[AlarmHH2],LT010-16,0);
        bitWrite(raptorholdingReg[AlarmL2],LT010-16,0);
        bitWrite(raptorholdingReg[AlarmLL2],LT010-16,1);
        _outputcontrol[XV002ctrl]=0;
        _outputcontrol[PC001] = 0; 
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],LT010,0);
        bitWrite(raptorholdingReg[AlarmHH1],LT010,0);
        bitWrite(raptorholdingReg[AlarmL1],LT010,0);
        bitWrite(raptorholdingReg[AlarmLL1],LT010,1);
        _outputcontrol[XV002ctrl]=0;
        _outputcontrol[PC001] = 0; 
      }  
      
    }
}
void mainmodbuscontroller::testINT30(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSHH011))
  {
    bitWrite(raptorholdingReg[InterlockB],INT30,1);
    prit("INTERLOCK: INT30 active \n");
    //bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
    _outputcontrol[XV010ctrl] = 0;     
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockB],INT30,0);
  }
}
void mainmodbuscontroller::testINT31(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSLL012))
  {
    bitWrite(raptorholdingReg[InterlockB],INT31,1);
    prit("INTERLOCK: INT31 active \n");
    //bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
    raptorholdingReg[PC002CTRL] = 0;
    _outputcontrol[PC002] = 0;
   // _outputcontrol[XV014ctrl] = 0;
   // _outputcontrol[XV017ctrl] = 0;
   // _outputcontrol[XV018ctrl] = 0;
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockB],INT31,0);
  }
}
void mainmodbuscontroller::testINT32(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSHH014))
  {
    bitWrite(raptorholdingReg[InterlockB],INT32,1);
    prit("INTERLOCK: INT32 active \n");
    //bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
    _outputcontrol[XV009ctrl] = 0;
    _outputcontrol[XV014ctrl] = 0;
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockB],INT32,0);
  }
}
void mainmodbuscontroller::testINT33(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSLL015))
  {
    prit("INTERLOCK: INT33 active \n");
    bitWrite(raptorholdingReg[InterlockB],INT33,1);
    //bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
    bitWrite(raptorholdingReg[ExtrasControl],PC003ctrl,0);
    _outputcontrol[PC003] = 0;
    _outputcontrol[XV015ctrl] = 0;
    _outputcontrol[XV016ctrl] = 0;
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockB],INT33,0);
  }
}
void mainmodbuscontroller::testLT013(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(raptorholdingReg[LT013]>raptorholdingReg[LT013+HAlarmOffset] && raptorholdingReg[LT013]<raptorholdingReg[LT013+HHAlarmOffset] )
    {
      if(LT013>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],LT013-16,1);
        bitWrite(raptorholdingReg[AlarmHH2],LT013-16,0);
        bitWrite(raptorholdingReg[AlarmL2],LT013-16,0);
        bitWrite(raptorholdingReg[AlarmLL2],LT013-16,0);
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],LT013,1);
        bitWrite(raptorholdingReg[AlarmHH1],LT013,0);
        bitWrite(raptorholdingReg[AlarmL1],LT013,0);
        bitWrite(raptorholdingReg[AlarmLL1],LT013,0);
      }
    }
    else if (raptorholdingReg[LT013]>raptorholdingReg[LT013+HHAlarmOffset])
    {
      if(LT013>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],LT013-16,0);
        bitWrite(raptorholdingReg[AlarmHH2],LT013-16,1);
        bitWrite(raptorholdingReg[AlarmL2],LT013-16,0);
        bitWrite(raptorholdingReg[AlarmLL2],LT013-16,0);
        _outputcontrol[XV009ctrl]=0; 
        _outputcontrol[XV014ctrl]=0; 
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],LT013,0);
        bitWrite(raptorholdingReg[AlarmHH1],LT013,1);
        bitWrite(raptorholdingReg[AlarmL1],LT013,0);
        bitWrite(raptorholdingReg[AlarmLL1],LT013,0);
        _outputcontrol[XV009ctrl]=0;
        _outputcontrol[XV014ctrl]=0; 

      }    
    }
    else if(raptorholdingReg[LT013]<raptorholdingReg[LT013+LAlarmOffset] && raptorholdingReg[LT013]>raptorholdingReg[LT013+LLAlarmOffset])
    {
      if(LT013>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],LT013-16,0);
        bitWrite(raptorholdingReg[AlarmHH2],LT013-16,0);
        bitWrite(raptorholdingReg[AlarmL2],LT013-16,1);
        bitWrite(raptorholdingReg[AlarmLL2],LT013-16,0);
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],LT013,0);
        bitWrite(raptorholdingReg[AlarmHH1],LT013,0);
        bitWrite(raptorholdingReg[AlarmL1],LT013,1);
        bitWrite(raptorholdingReg[AlarmLL1],LT013,0);
        
      }  
    }
    else if(raptorholdingReg[LT013]<raptorholdingReg[LT013+LLAlarmOffset])
    {
      if(LT013>15)
      {
        bitWrite(raptorholdingReg[AlarmH2],LT013-16,0);
        bitWrite(raptorholdingReg[AlarmHH2],LT013-16,0);
        bitWrite(raptorholdingReg[AlarmL2],LT013-16,0);
        bitWrite(raptorholdingReg[AlarmLL2],LT013-16,1);
        _outputcontrol[XV015ctrl]=0;
        _outputcontrol[XV016ctrl]=0;
        _outputcontrol[PC003] = 0; 
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],LT013,0);
        bitWrite(raptorholdingReg[AlarmHH1],LT013,0);
        bitWrite(raptorholdingReg[AlarmL1],LT013,0);
        bitWrite(raptorholdingReg[AlarmLL1],LT013,1);
        _outputcontrol[XV015ctrl]=0;
        _outputcontrol[XV016ctrl]=0;
        _outputcontrol[PC003] = 0; 
      }  
      
    }
}
