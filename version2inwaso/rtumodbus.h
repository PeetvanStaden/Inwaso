#ifndef rtumodbus_h
#define rtumodbus_h
#include <Arduino.h>
#include <ModbusRTUMaster.h>
#include <RS485.h>

ModbusRTUMaster masterrtu(RS485);
ModbusTCPMaster master;
class rtumodbus
{
  public:
    initialise(int baudrate);
};    

#endif
