#include "interlock.h"
#include "pins.h"
#include "outputinputctrl.h"
#include <ModbusTCPSlave.h>
#include "processctrl.h"
#include "mainmodbuscontroller.h"
#include <avr/wdt.h>
ModbusTCPSlave Raptorslave(504);
uint16_t holdingRegisters[NUM_HOLDING_REGISTERS];
//int SensorsArray[TotalThresholdSensors][ArrayWidth];
uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
uint8_t ip[] = { 192, 168, 4, 69 };
bool interrupt = true;
int FlowSensor[6]={0};
int OutputCtrl[TotalOutputs]={0};
int OutputStatus[TotalOutputs]={0};
unsigned long ft01fr = 0;
unsigned long ft02fr = 0;
unsigned long ft03fr = 0;
unsigned long ft04fr = 0;
unsigned long ft05fr = 0;
unsigned long ft06fr = 0;
unsigned long ft01frprv = 0;
unsigned long ft02frprv = 0;
unsigned long ft03frprv = 0;
unsigned long ft04frprv = 0;
unsigned long ft05frprv = 0;
unsigned long ft06frprv = 0;
int ftpulse5 = 0;
mainmodbuscontroller sr;
interlock lock;
processctrl process(holdingRegisters,OutputCtrl,OutputStatus);
outputinputctrl outputs;
int delayprint = 10;
int bigpulse = 1;
float smallpulse = 22.2;
//test

float now=0;
void setup() {
  Serial.begin(115200);
  cli();
  settimerdefaults();
  sei();
  Ethernet.begin(mac,ip);
  Serial.println(Ethernet.localIP());
  sr.prit("Helooooo \n");
  Raptorslave.begin();
  
  Raptorslave.setHoldingRegisters(holdingRegisters,NUM_HOLDING_REGISTERS);
  Raptorslave.update(); 
  sr.prit("Raptor not breaking\n");
  holdingRegisters[Startup] = 0;
  holdingRegisters[Startupfeedback]=0;
  lock.startup(holdingRegisters,NUM_HOLDING_REGISTERS,OutputCtrl,OutputStatus);
  sr.prit("Lock startup did not break \n");
  attachInterrupt(digitalPinToInterrupt(I0_5),FT001counter,RISING);
  attachInterrupt(digitalPinToInterrupt(I0_6),FT002counter,RISING);
  attachInterrupt(digitalPinToInterrupt(I1_5),FT003counter,RISING);
  attachInterrupt(digitalPinToInterrupt(I1_6),FT004counter,RISING);
  attachInterrupt(digitalPinToInterrupt(I2_5),FT005counter,RISING);
  attachInterrupt(digitalPinToInterrupt(I2_6),FT006counter,RISING);
  now = millis()+delayprint;
  #ifdef WATCHDOG
  wdt_enable(WDTO_8S);
  #endif

}

int prev1 = 0;
int prev2 = 0;
int prev3 = 0;

void loop() {
  #ifdef WATCHDOG
  wdt_reset();
  #endif
  
  if(interrupt== true)
  {
    //Serial.print("Valve status before update: ");
    //Serial.println(holdingRegisters[24]);
    //Raptorslave.update();
    //Serial.print("Valve status after update: ");
    //Serial.println(holdingRegisters[24]);
    interrupt = false;
    if(millis()-ft01frprv>20000)
    {
      holdingRegisters[FT001FR]= 0;
    }
    else
    {

    }
    if(millis()-ft02frprv>20000)
    {
      holdingRegisters[FT002FR]= 0;
    }
    if(millis()-ft03frprv>20000)
    {
      holdingRegisters[FT003FR]= 0;
    }
    if(millis()-ft04frprv>20000)
    {
      holdingRegisters[FT004FR]= 0;
    }
    if(millis()-ft05frprv>20000)
    {
      holdingRegisters[FT005FR]= 0;
    }
    else
    {
      bitWrite(holdingRegisters[ExtrasStatus],PC003ST,1);
    }
    if(millis()-ft06frprv>20000)
    {
      holdingRegisters[FT006FR]= 0;
    }
/*     Serial.print("AT-001 pH Sensor:  ");
    Serial.println(holdingRegisters[AT001]);
    Serial.print("AT-002 conductivity sensor:  ");
    Serial.println(holdingRegisters[AT002]);
    Serial.print("AT-003 Turbidity Sensor:  ");
    Serial.println(holdingRegisters[AT003]);
    Serial.print("AT-004 Hydrogen Sensor ABC:  ");
    Serial.println(holdingRegisters[AT004ABC]);
    Serial.print("AT-005 Hydrogen Sensor ABC:  ");
    Serial.println(holdingRegisters[AT005ABC]);
    Serial.print("AT-006 pH Sensors:  ");
    Serial.println(holdingRegisters[AT006]);
    Serial.print("AT-007 conductivity sensor:  ");
    Serial.println(holdingRegisters[AT007]);
    Serial.print("LT-001 level transmitter:  ");
    Serial.println(holdingRegisters[LT001]);
    Serial.print("LT-010 level transmitter:  ");
    Serial.println(holdingRegisters[LT010]);
    Serial.print("LT-013 level transmitter:  ");
    Serial.println(holdingRegisters[LT013]);
    Serial.print("LT-016 level transmitter:  ");
    Serial.println(holdingRegisters[LT016]);

    Serial.print("PT-001:  ");
    Serial.println(holdingRegisters[PT001]);
    Serial.print("PT-002:  ");
    Serial.println(holdingRegisters[PT002]);
    Serial.print("PT-003:  ");
    Serial.println(holdingRegisters[PT003]);
    Serial.print("PT-004:  ");
    Serial.println(holdingRegisters[PT004]);
    Serial.print("PT-005:  ");
    Serial.println(holdingRegisters[PT005]);
    Serial.print("PT-006:  ");
    Serial.println(holdingRegisters[PT006]);
    Serial.print("PT-007:  ");
    Serial.println(holdingRegisters[PT007]);  */
/*      Serial.print("TT-001:  ");
     Serial.println(holdingRegisters[TT001]);
     Serial.print("TT002:  ");
     Serial.println(holdingRegisters[TT002]);
     Serial.print("TT003:  ");
     Serial.println(holdingRegisters[TT003]); */
    if(holdingRegisters[PC001Speed]!=prev1)
    {
      Serial.print("PC-001 Frequency:  ");
      Serial.println(holdingRegisters[PC001Speed]);
    }
    if(holdingRegisters[PC002Speed]!=prev2)
    {
      Serial.print("  PC-002 Frequency:  ");
      Serial.println(holdingRegisters[PC002Speed]);
    }
    if(holdingRegisters[PC004Speed]!=prev3)
    {
      Serial.print("  PC-004 Frequency:  ");
      Serial.println(holdingRegisters[PC004Speed]);
    }
    prev1=holdingRegisters[PC001Speed];
    prev2=holdingRegisters[PC002Speed];
    prev3=holdingRegisters[PC004Speed];
  }
  if(millis()>now)
  {
    //Serial.print("Checking interlocks");
    lock.CheckInterlocks(holdingRegisters,OutputCtrl,OutputStatus);
    Raptorslave.update();
//    process.process1();
//    process.process2tk1();
//    process.process2tk2();
//    process.process2tk3();
//    process.process2ver1();
//    process.process2ver2();
//      process.process2vs1();
//    process.process2su1();
    now=millis()+delayprint;
    holdingRegisters[Startup] = 1;
    //Serial.println("Exiting interlock check");
  }
}

void FT001counter(){
  if(bitRead(holdingRegisters[FlowReset],FT001R))
  {
    bitWrite(holdingRegisters[FlowReset],FT001R,0);
    holdingRegisters[FT001] = 0;
  }
  ft01fr = millis()-ft01frprv;
  ft01frprv = millis();
  int Flowrate = (60000/ft01fr);
  holdingRegisters[FT001]+=bigpulse;
  holdingRegisters[FT001FR]=Flowrate;
  Serial.print("FT101:.... ");
  Serial.print(Flowrate,DEC);
  Serial.print("- Flow total =");
  Serial.println(bigpulse,DEC);
  if(Flowrate < 1)
  {
    //set pump status;
  }
}
void FT002counter(){
  if(bitRead(holdingRegisters[FlowReset],FT002R))
  {
    bitWrite(holdingRegisters[FlowReset],FT002R,0);
    holdingRegisters[FT002] = 0;
  }
  ft02fr = millis()-ft02frprv;
  ft02frprv = millis();
  float Flowrate = (60000/ft02fr);
  Serial.print("FT002 ::::::::::::::::::::::::::::::  ");
  Serial.print(Flowrate,DEC);
  Serial.print("- Flow total =");
  Serial.println(bigpulse,DEC);
  holdingRegisters[FT002]+=bigpulse;
  holdingRegisters[FT002FR]=Flowrate;

}
void FT003counter(){
  if(bitRead(holdingRegisters[FlowReset],FT003R))
  {
    bitWrite(holdingRegisters[FlowReset],FT003R,0);
    holdingRegisters[FT003] = 0;
  }
  ft03fr = millis()-ft03frprv;
  Serial.print("------ ");
  Serial.println(ft03fr,DEC);
  ft03frprv = millis();
  float Flowrate = (60000/ft03fr);
  holdingRegisters[FT003]+=bigpulse;
  holdingRegisters[FT003FR]=Flowrate;
  Serial.print("FT303 : ");
  Serial.println(Flowrate);
  
 
}
void FT004counter(){
  if(bitRead(holdingRegisters[FlowReset],FT004R))
  {
    bitWrite(holdingRegisters[FlowReset],FT004R,0);
    holdingRegisters[FT004] = 0;
  }
  ft04fr = millis()-ft04frprv;
  ft04frprv = millis();
  int Flowrate = (60000/ft04fr);
  holdingRegisters[FT004]+=bigpulse;
  holdingRegisters[FT004FR]=Flowrate;
  Serial.print("FT404 ................");
  Serial.print(Flowrate,DEC);
  Serial.print("- Flow total =");
  Serial.println(bigpulse,DEC);
 
}
void FT005counter(){
  ftpulse5++;
  if(ftpulse5 == 10)
  {
  ft05fr = millis()-ft05frprv;
  ft05frprv = millis();
  float Flowrate = (smallpulse/ft05fr)*60;
  holdingRegisters[FT005]+=(smallpulse/1000);
  holdingRegisters[FT005FR]=Flowrate*100;
  //Serial.print("Flowrate:  ");
  //Serial.println(Flowrate);

  ftpulse5 = 0;
  }
}
void FT006counter(){
  ft06fr = millis()-ft06frprv;
  ft06frprv = millis();
  int Flowrate = (60000/ft06fr);
  holdingRegisters[FT006]+=bigpulse;
  holdingRegisters[FT006FR]=Flowrate;
  Serial.println("FT606 ");
  Serial.print(Flowrate,DEC);
  Serial.print("- Flow total =");
  Serial.println(bigpulse,DEC);

}
void settimerdefaults(void)
{
//set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
// set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
}
ISR(TIMER1_COMPA_vect){
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  interrupt = true;
  
}
