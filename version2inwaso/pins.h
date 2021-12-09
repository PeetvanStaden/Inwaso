//SensorIDs each sensor should have an ID, leaving out the Flow transmitters: Flow transmitters are interrupts
//#define DEBUG 
//#define WATCHDOG
#define AT001    0
#define AT002    1
#define AT003    2
#define AT004ABC 3
#define AT005ABC 4
#define AT006    5
#define AT007    6
#define AT008    7
#define AT009    8
#define LT001    9
#define LT010    10
#define LT013    11
#define LT016    12
#define PT001    13
#define PT002    14
#define PT003    15
#define PT004    16
#define PT005    17
#define PT006    18
#define PT007    19
#define TT001    20
#define TT002    21
#define TT003    22



#define LevelSwitchesReg          23
#define LSH018   0
#define LSH020   1
#define LSHH002  2
#define LSHH009  3
#define LSHH011  4
#define LSHH014  5
#define LSHH019  6
#define LSLL003  7
#define LSLL004  8
#define LSLL005  9
#define LSLL008  10
#define LSLL012  11
#define LSLL015  12
#define LSLL017  13
#define ValveStatus               24
//modbus registors for valve checks.
#define XV001R   0
#define XV002R   1
#define XV003R   2
#define XV004R   3
#define XV009R   4
#define XV010R   5
#define XV011R   6
#define XV012R   7
#define XV013R   8
#define XV014R   9
#define XV015R   10
#define XV016R   11
#define XV017R   12
#define XV018R   13
#define XV019R   14
#define ExtrasStatus              25
#define PC003ST  	0
#define PC005ST 	1
#define PC006ST 	2
#define PC007ST 	3
#define VER001ST 	4
#define VER002ST 	5
#define MU001ST 	6
#define MU002ST 	7

#define PC001Speed                26
#define PC002Speed                27
#define PC004Speed                28

#define ValveAlarms               29
#define ValveControl              30
#define XV001ctrl 0
#define XV002ctrl 1
#define XV003ctrl 2
#define XV004ctrl 3
#define XV009ctrl 4
#define XV010ctrl 5
#define XV011ctrl 6
#define XV012ctrl 7
#define XV013ctrl 8
#define XV014ctrl 9
#define XV015ctrl 10
#define XV016ctrl 11
#define XV017ctrl 12
#define XV018ctrl 13
#define XV019ctrl 14

#define PC003   15
#define PC005   16
#define PC006   17
#define PC007   18
#define VER001  19
#define VER002  20
#define MU001   21
#define MU002   22
#define MU002   23
#define PC001   24
#define PC002   25
#define PC004   26

#define ExtrasControl             31
#define PC003ctrl  	0
#define PC005ctrl 	1
#define PC006ctrl 	2
#define PC007ctrl 	3
#define VER001ctrl 	4
#define VER002ctrl 	5
#define MU001ctrl 	6
#define MU002ctrl 	7
#define MU002ctrl   8
#define PC001CTRL                 32
#define PC002CTRL                 33
#define PC004CTRL                 34


#define FT001		              35
#define FT002		              36
#define FT003		              37
#define FT004		              38
#define FT005		              39
#define FT006		              40



#define FlowReset                 41
#define FT001R	0
#define FT002R	1
#define FT003R	2
#define FT004R	3
#define FT005R	4
#define FT006R	5
#define AlarmH1                   42
#define AlarmH2                   43
#define AlarmHH1                  44
#define AlarmHH2                  45
#define AlarmL1                   46
#define AlarmL2                   47
#define AlarmLL1                  48
#define AlarmLL2                  49

#define LT001SP                   151
#define LT010SP                   152
#define LT013SP                   153
#define LT016SP                   154

#define FT001SP                   165
#define FT002SP                   166
#define FT003SP                   167
#define FT004SP                   168
#define FT005SP                   169
#define FT006SP                   170

#define InterlockA                42
#define INT1    0
#define INT2    1
#define INT3    2
#define INT4    3
#define INT7    4
#define INT8    5

#define InterlockB                 43
#define INT26   0
#define INT27   1
#define INT28   2
#define INT29   3
#define INT30   4
#define INT31   5
#define INT32   6
#define INT33   7
#define INT34   8
#define INT35   9
#define INT36   10
#define FT001FR                 44
#define FT002FR                 45
#define FT003FR                 46
#define FT004FR                 47
#define FT005FR                 48
#define FT006FR                 49
#define Process_1               111
#define PC_1start               0
#define PC1_Status              1           
#define PC1_Alarm_TK2           2
#define PC1_Alarm_TK3           3
#define PC1_Alarm_SU1           4
#define PC1_Alarm_VS1           5
#define PC1_Option              6                       //0 =  Option 1    1 = Option 2
#define PC1_Task_Complete       7
#define TK001SRC                184
#define options4_pc             0
#define options3_pc             1
#define options2_pc             2
#define options1_pc             3
#define OBL_pc                  4
#define su001_pc                5
#define vs002_pc                6
#define vs001_pc                7
#define tk003_pc                8
#define tk002_pc                9
#define tk001_pc                10
#define ver002_pc               11
#define ver001_pc               12
#define start_pc                13

#define TK002SRC                185
#define TK003SRC                186
#define VER001SRC               187
#define VER002SRC               188
#define VS001SRC                189
#define VS002SRC                190
#define SU001SRC                191


#define TK1RES                192
#define TK2RES                193
#define TK3RES                194
#define VER1RE                195
#define VER2RE                196
#define VS1RES                197
#define VS2RES                198
#define SU1RES                199
#define Startup               50

#define TotalThresholdVariables   23
#define TotalThresholdSensors     37
#define TotalSensors              52




//Postion in SensorArray[][x]

#define SensorValue 0
#define HTHRESH     1
#define HHTHRESH    2
#define LTHRESH     3
#define LLTHRESH    4
#define SETPOINT    5
//is the sensor on a interlock 0=no   1=yes
#define Lockable    6
//Alarmstatus indicates the state of the alarm
//0=H   1=HH   2=L   3=LL 4=No Alarm
#define AlarmStatus 7
#define ControlVar0 8
#define ControlVar1 9
#define ControlVar2 10
#define ControlVar3 11
#define ControlVar4 12
#define ControlVar5 13
#define ControlVar6 14
#define ControlVar7 15
#define ArrayWidth  16
//To ID the controll OUTPUT



#define TotalOutputs 26
//#define XV001 0
//#define XV002 1
//#define XV003 2
//#define XV004 3
//#define XV009 4
//#define XV010 5
//#define XV011 6
//#define XV012 7
//#define XV013 8
//#define XV014 9
//#define XV015 10
//#define XV016 11
//#define PC003 12
//#define PC005 13
//#define PC006 14
//#define PC007 15
//#define MU001 16
//#define MU002 17
//
////Modbus RTU OUTPUTs
//#define PC001 0
//#define PC002 1
//#define PC004 2
//
//
////Modbus to Raptor OUTPUTS
//#define VER001 0
//#define VER002 0
//
//Modbus To Slave
#define XV017Coil 0
#define XV018Coil 1
#define XV019Coil 2
#define MU001Coil 3
#define MU002Coil 4

//modbus rtu extras
#define NUM_COILS 22
#define NUM_INPUT_REGISTERS 15
#define NUM_DISCRETE_INPUTS 14
#define slaveRefresh  800
#define slaveRefreshDiscreteInputs 1000
#define slaveRefreshOutput 2000

#define XV017M 0
#define XV018M 2
#define XV019M 4
#define PC003M 16
#define PC005M 17
#define PC006M 18
#define PC007M 19

//Raptor updates
#define NUM_HOLDING_REGISTERS   250
#define RaptorUpdateThresholds  416
#define RaptorUpdateOutputs     497
#define RaptorProcessStart      500
#define HAlarmOffset            50
#define HHAlarmOffset           73
#define LAlarmOffset            96
#define LLAlarmOffset           119
//#define HOfset                  23                        
//#define HHOfset                 46              
//#define LOfset                  69
//#define LLOfset                 92
