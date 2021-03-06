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
  prit("\n");
  prit("Valve command from raptor: ");
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
prit("........\n");
//extras control
// for(int i = 0; i < 11; i ++)
// {
//   _outputctrl[i+15] =bitRead(_raptorholdingReg[ExtrasControl],i);
  
// }
 if(bitRead(_raptorholdingReg[LevelSwitchesReg],LSLL015))
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
}

 
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
