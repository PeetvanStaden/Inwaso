#include "interlock.h"

interlock::interlock()
{
  
}
void interlock::startup(uint16_t* raptorholdingReg,int sizeofHoldReg,int* _outputcontrol,int* _outputstatus)
{
  modbus.prit("hello world\n");
  modbus.raptorStart(raptorholdingReg,sizeofHoldReg);
  modbus.mainmodbus(raptorholdingReg,sizeofHoldReg);
 
  Serial.println("Modbus registered");
  //Get Sensor Array information from Raptor
  if(modbus.raptorSync(raptorholdingReg,_outputcontrol,_outputstatus)==false)
  {
    Serial.println("Raptor sync failed");
    
  }
  modbus.prit("Starting modbussync \n");
  modbus.modbusSync(raptorholdingReg); 
  modbus.prit("Ending mosbuss sync");
  return;
}
int interlock::CheckInterlocks(uint16_t* raptorholdingReg,int* _outputcontrol,int* _outputstatus)
{

  //TODO:raptorsync
  bool returnvalue=false;
  float now = millis()+1000;   
  if(millis()>raptor)
    {if(modbus.raptorSync(raptorholdingReg,_outputcontrol,_outputstatus)==true)
    {
      returnvalue= 1;
     // Serial.println("Raptor syinc success");
      }
     raptor = millis()+10;
    }
modbus.modbusSync(raptorholdingReg); 
if(raptorholdingReg[Startup]==0)
{
  modbus.prit("\n");
  modbus.prit("Starting interlocks\n");
  testLT001(raptorholdingReg,_outputcontrol);
  testINT1(raptorholdingReg,_outputcontrol);
  testINT1(raptorholdingReg,_outputcontrol);
  testINT2(raptorholdingReg,_outputcontrol);
  testAT001(raptorholdingReg,_outputcontrol);
  testINT36(raptorholdingReg,_outputcontrol);
  testINT3(raptorholdingReg,_outputcontrol);
  testINT4(raptorholdingReg,_outputcontrol);
  testINT7(raptorholdingReg,_outputcontrol);
  testINT8(raptorholdingReg,_outputcontrol);
  testINT26(raptorholdingReg,_outputcontrol);
  testINT27(raptorholdingReg,_outputcontrol);
  testINT28(raptorholdingReg,_outputcontrol);
  testINT29(raptorholdingReg,_outputcontrol);
  testLT016(raptorholdingReg,_outputcontrol);
  testAT006(raptorholdingReg,_outputcontrol);
  testINT34(raptorholdingReg,_outputcontrol);
  testINT35(raptorholdingReg,_outputcontrol);
  testLT010(raptorholdingReg,_outputcontrol);
  testINT30(raptorholdingReg,_outputcontrol);
  testINT31(raptorholdingReg,_outputcontrol);
  testINT32(raptorholdingReg,_outputcontrol);
  testINT33(raptorholdingReg,_outputcontrol);
  testLT013(raptorholdingReg,_outputcontrol);
  
}  
  //
  outputs.updateHardwareOutputs(_outputcontrol);
  modbus.modbusSync(raptorholdingReg); 
  outputs.updateHardwareInputs(raptorholdingReg);

  return returnvalue;
}

void interlock::testLT001(uint16_t* raptorholdingReg,int* _outputcontrol)
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
void interlock::testINT1(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSHH002))
  {
    bitWrite(raptorholdingReg[InterlockA],INT1,1);
    _outputcontrol[XV001ctrl]=0;
    _outputcontrol[XV011ctrl]=0; 
    _outputcontrol[XV013ctrl]=0; 
    _outputcontrol[XV016ctrl]=0; 
    _outputcontrol[XV018ctrl]=0; 
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockA],INT1,0);
  }
  
}
void interlock::testINT2(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSLL003))
  {
    bitWrite(raptorholdingReg[InterlockA],INT2,1);
    _outputcontrol[XV002ctrl]=0;
    _outputcontrol[PC001]= 0;
    raptorholdingReg[PC001CTRL] = 0;
   // modbus.prit("STOPPING PC001 DUE TO AN INTERLOCK!!!!! \n");    
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockA],INT2,0);
  }
}
void interlock::testAT001(uint16_t* raptorholdingReg,int* _outputcontrol)
{

}
void interlock::testINT36(uint16_t* raptorholdingReg,int* _outputcontrol)
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

      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],TT001,0);
        bitWrite(raptorholdingReg[AlarmHH1],TT001,1);
        bitWrite(raptorholdingReg[ExtrasControl],VER001ctrl,0);
        bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);     
        bitWrite(raptorholdingReg[InterlockB],INT36,1);
      }    
    }
    else
    {
      bitWrite(raptorholdingReg[InterlockB],INT36,0);
    }    
}
void interlock::testINT3(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSLL004))
  {
    bitWrite(raptorholdingReg[InterlockA],INT3,1);
    bitWrite(raptorholdingReg[ExtrasControl],VER001ctrl,0);
    _outputcontrol[PC006] = 0;     
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockA],INT3,0);
  }
}
void interlock::testINT4(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSLL005))
  {
    bitWrite(raptorholdingReg[InterlockA],INT4,1);
    bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
    _outputcontrol[PC007] = 0;     
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockA],INT4,0);
  }
}
void interlock::testINT7(uint16_t* raptorholdingReg,int* _outputcontrol)
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
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],TT002,0);
        bitWrite(raptorholdingReg[AlarmHH1],TT002,1);
        bitWrite(raptorholdingReg[ExtrasControl],VER001ctrl,0);
        bitWrite(raptorholdingReg[InterlockA],INT7,1);     
     
      }    
    }
    else
    {
      bitWrite(raptorholdingReg[InterlockA],INT7,0); 
    }
}
void interlock::testINT8(uint16_t* raptorholdingReg,int* _outputcontrol)
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
      }
      else
      {
        bitWrite(raptorholdingReg[AlarmH1],TT003,0);
        bitWrite(raptorholdingReg[AlarmHH1],TT003,1);
        bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);   
        bitWrite(raptorholdingReg[InterlockA],INT8,1);   
     
      }    
    }
    else
    {
      bitWrite(raptorholdingReg[InterlockA],INT8,0);   
    }
}
void interlock::testINT26(uint16_t* raptorholdingReg,int* _outputcontrol)
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
void interlock::testINT27(uint16_t* raptorholdingReg,int* _outputcontrol)
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
void interlock::testINT28(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(bitRead(raptorholdingReg[LevelSwitchesReg],LSLL008))
  {
    bitWrite(raptorholdingReg[InterlockB],INT28,1);
    bitWrite(raptorholdingReg[InterlockB],INT29,0);
      // _outputcontrol[XV009ctrl]=0;
      // _outputcontrol[XV010ctrl]=0; 
      // _outputcontrol[XV011ctrl]=0; 
      // _outputcontrol[XV019ctrl]=0; 
    
      //raptorholdingReg[PC004CTRL] = 0;
      _outputcontrol[PC004]=0;
      modbus.prit("Interlock 28 ACTIVATED PC004 SHOULD STOP\n");

  }
  else
  {
    //if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSHH009))
    bitWrite(raptorholdingReg[InterlockB],INT28,0);
  }
}
void interlock::testINT29(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSHH009))
  {
    bitWrite(raptorholdingReg[InterlockB],INT29,1);
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
      modbus.prit("Interlock 29 ACTIVATED PC004 SHOULD START");
    }
    else
    {
        modbus.prit("Interlock 29 ACTIVATED PC004 wont start, valves will close");
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
void interlock::testLT016(uint16_t* raptorholdingReg,int* _outputcontrol)
{

}
void interlock::testAT006(uint16_t* raptorholdingReg,int* _outputcontrol)
{

}
void interlock::testINT34(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSLL017))
  {
    bitWrite(raptorholdingReg[InterlockB],INT34,1);
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
void interlock::testINT35(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSHH019))
  {
    bitWrite(raptorholdingReg[InterlockB],INT35,1);
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
void interlock::testLT010(uint16_t* raptorholdingReg,int* _outputcontrol)
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
void interlock::testINT30(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSHH011))
  {
    bitWrite(raptorholdingReg[InterlockB],INT30,1);
    //bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
    _outputcontrol[XV010ctrl] = 0;     
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockB],INT30,0);
  }
}
void interlock::testINT31(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSLL012))
  {
    bitWrite(raptorholdingReg[InterlockB],INT31,1);
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
void interlock::testINT32(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSHH014))
  {
    bitWrite(raptorholdingReg[InterlockB],INT32,1);
    //bitWrite(raptorholdingReg[ExtrasControl],VER002ctrl,0);
    _outputcontrol[XV009ctrl] = 0;
    _outputcontrol[XV014ctrl] = 0;
  }
  else
  {
    bitWrite(raptorholdingReg[InterlockB],INT32,0);
  }
}
void interlock::testINT33(uint16_t* raptorholdingReg,int* _outputcontrol)
{
  if(!bitRead(raptorholdingReg[LevelSwitchesReg],LSLL015))
  {
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
void interlock::testLT013(uint16_t* raptorholdingReg,int* _outputcontrol)
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
   
