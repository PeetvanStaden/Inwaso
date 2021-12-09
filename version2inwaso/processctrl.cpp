#include "processctrl.h"

processctrl::processctrl(uint16_t* raptorholdingReg,int* OutputCtrl,int* OutputStatus)
{
    _raptorHoldingReg = raptorholdingReg;
    _OutputCtrl = OutputCtrl;
    _OutputStatus = OutputStatus;
}

void processctrl::process1()
{
    switch(_PC1TURN){
    case 0:
    if(bitRead(_raptorHoldingReg[Process_1],PC_1start)==1)
    {
        bitWrite(_raptorHoldingReg[Process_1],PC1_Task_Complete,0);
        bitRead(_raptorHoldingReg[Process_1],PC_1start);
        if(_OutputStatus[XV017ctrl]==1|_OutputStatus[XV018ctrl]==1?bitWrite(_raptorHoldingReg[Process_1],PC1_Alarm_TK2,1):bitWrite(_raptorHoldingReg[Process_1],PC1_Alarm_TK2,0));
        if(_OutputStatus[XV011ctrl]==1|_OutputStatus[XV019ctrl]==1?bitWrite(_raptorHoldingReg[Process_1],PC1_Alarm_VS1,1):bitWrite(_raptorHoldingReg[Process_1],PC1_Alarm_VS1,0));
        if(_OutputStatus[XV013ctrl]==1?bitWrite(_raptorHoldingReg[Process_1],PC1_Alarm_SU1,1):bitWrite(_raptorHoldingReg[Process_1],PC1_Alarm_SU1,0));
        if(_OutputStatus[XV016ctrl]==1?bitWrite(_raptorHoldingReg[Process_1],PC1_Alarm_TK3,1):bitWrite(_raptorHoldingReg[Process_1],PC1_Alarm_TK3,0));
        _OutputCtrl[XV001ctrl] = 1;
        if(bitRead(_raptorHoldingReg[Process_1],PC1_Option)?_PC1TURN = 2:_PC1TURN=1);
        _raptorHoldingReg[FT001] = 0;

    }
    break;
    case 1: //Option 1 is selected
    if(bitRead(_raptorHoldingReg[InterlockA],INT2))
    {
        _OutputCtrl[XV001ctrl] = 0;
        _PC1TURN = 0;
    }
    if(_raptorHoldingReg[LT001]>_raptorHoldingReg[LT001SP])
    {
        bitWrite(_raptorHoldingReg[Process_1],PC1_Task_Complete,1);
        _PC1TURN = 0;
    }
    break;
    case 2: //Option 2 is selected
    if(bitRead(_raptorHoldingReg[InterlockA],INT2))
    {
        _OutputCtrl[XV001ctrl] = 0;
        _PC1TURN = 0;
    }
    if(_raptorHoldingReg[FT001]>_raptorHoldingReg[FT001SP])
    {
        bitWrite(_raptorHoldingReg[Process_1],PC1_Task_Complete,1);
        _PC1TURN = 0;
    }        
    break;
    default:
    break;
    }
    
}
void processctrl::process2tk1()
{
    if(bitRead(_raptorHoldingReg[InterlockA],INT2)|
    bitRead(_raptorHoldingReg[InterlockB],INT26)|
    bitRead(_raptorHoldingReg[InterlockB],INT27)|
    bitRead(_raptorHoldingReg[InterlockB],INT29))
    {
        _PC2TK1TURN = 0;
        return;
    }
    switch (_PC2TK1TURN)
    {
    case 0:
        if(bitRead(_raptorHoldingReg[TK001SRC],start_pc))
        {        
            if(bitRead(_raptorHoldingReg[TK001SRC],ver001_pc))
            {
                _PC2TK1TURN = 1;                
            }
            if(bitRead(_raptorHoldingReg[TK001SRC],ver002_pc))
            {
                _PC2TK1TURN = 2;                
            }

        }
        break;
    case 1://Destination VER-001
        if(bitRead(_raptorHoldingReg[TK001SRC],start_pc))
        {        
            switch (speedcontrolstage)
            {
            case 0: //start motor at 1% pace - 34KHz mapped

                _raptorHoldingReg[PC001CTRL] = 1;
                bitWrite(_raptorHoldingReg[ValveControl],XV002ctrl,1);
                bitWrite(_raptorHoldingReg[ValveControl],XV003ctrl,1);
                bitWrite(_raptorHoldingReg[ValveControl],XV004ctrl,0);
                speedcontrolstage = 0; //when speed control is implimented change the variable to 1
                break;
            case 1: //do the vfd speed change in comparison to VFD set point variable
                break;
            default:
                break;
            }
        }
        else
        {
            _raptorHoldingReg[PC001CTRL]=0;
            _PC2TK1TURN = 0;
            speedcontrolstage = 0; 
            bitWrite(_raptorHoldingReg[ValveControl],XV002ctrl,0);
            bitWrite(_raptorHoldingReg[ValveControl],XV003ctrl,0);
            bitWrite(_raptorHoldingReg[ValveControl],XV004ctrl,0);
        }
    case 2://Destination VER-002
        if(bitRead(_raptorHoldingReg[TK001SRC],start_pc))
        {        
            switch (speedcontrolstage)
            {
            case 0: //start motor at 1% pace - 34KHz mapped

                _raptorHoldingReg[PC001CTRL] = 1;
                bitWrite(_raptorHoldingReg[ValveControl],XV002ctrl,1);
                bitWrite(_raptorHoldingReg[ValveControl],XV003ctrl,0);
                bitWrite(_raptorHoldingReg[ValveControl],XV004ctrl,1);
                speedcontrolstage = 0; //when speed control is implimented change the variable to 1
                break;
            case 1: //do the vfd speed change in comparison to VFD set point variable
                break;
            default:
                break;
            }
        }
        else
        {
            _raptorHoldingReg[PC001CTRL]=0;
            _PC2TK1TURN = 0;
            speedcontrolstage = 0; 
            bitWrite(_raptorHoldingReg[ValveControl],XV002ctrl,0);
            bitWrite(_raptorHoldingReg[ValveControl],XV003ctrl,0);
            bitWrite(_raptorHoldingReg[ValveControl],XV004ctrl,0);
        }
        break;
    default:
    break;
    }
}
void processctrl::process2tk2()
{
    if(bitRead(_raptorHoldingReg[InterlockB],INT30)|
    bitRead(_raptorHoldingReg[InterlockB],INT31)|
    bitRead(_raptorHoldingReg[InterlockB],INT26)|
    bitRead(_raptorHoldingReg[InterlockB],INT27)|
    bitRead(_raptorHoldingReg[InterlockB],INT32)|
    bitRead(_raptorHoldingReg[InterlockB],INT29))
    {
        _PC2TK2TURN = 0;
        _PC2OptionTK3 = 0;
        //valves xv003
        bitWrite(_raptorHoldingReg[ValveControl],XV017ctrl,0);
        bitWrite(_raptorHoldingReg[ValveControl],XV004ctrl,0);
        bitWrite(_raptorHoldingReg[ValveControl],XV003ctrl,0);
        bitWrite(_raptorHoldingReg[ValveControl],XV018ctrl,0);
        return;
    }
    switch (_PC2TK2TURN)
    {
    case 0: //process start detect
        if(bitRead(_raptorHoldingReg[TK002SRC],start_pc))
        {   
            if(bitRead(_raptorHoldingReg[TK002SRC],tk001_pc))
            {
                _PC2TK2TURN = 1;                
            }     
            if(bitRead(_raptorHoldingReg[TK002SRC],ver001_pc))
            {
                _PC2TK2TURN = 2;                
            }
            if(bitRead(_raptorHoldingReg[TK002SRC],ver002_pc))
            {
                _PC2TK2TURN = 3;                
            }
            if(bitRead(_raptorHoldingReg[TK002SRC],tk003_pc))
            {
                _PC2TK2TURN = 4;                
            }
        }    
        break;
    case 1: //Destination TK001  Open valve XV018
        _TK2toTK1Options();
        break;
    case 2: //Destinatnion VER-001   Open valve XV017 and XV003
                //only 1 possible option to select
        bitWrite(_raptorHoldingReg[ValveControl],XV017ctrl,1);
        bitWrite(_raptorHoldingReg[ValveControl],XV003ctrl,1);
        if(!bitRead(_raptorHoldingReg[TK002SRC],start_pc))
        {
            _raptorHoldingReg[PC002CTRL] = 0;
            bitWrite(_raptorHoldingReg[ValveControl],XV017ctrl,0);
            bitWrite(_raptorHoldingReg[ValveControl],XV003ctrl,0);
            _PC2TK1TURN = 0;
        }        
        break;
    case 3: //Destination VER-002   Open valve XV017 and XV004
        bitWrite(_raptorHoldingReg[ValveControl],XV017ctrl,1);
        bitWrite(_raptorHoldingReg[ValveControl],XV004ctrl,1);
        if(!bitRead(_raptorHoldingReg[TK002SRC],start_pc))
        {
            _raptorHoldingReg[PC002CTRL] = 0;
            bitWrite(_raptorHoldingReg[ValveControl],XV017ctrl,0);
            bitWrite(_raptorHoldingReg[ValveControl],XV004ctrl,0);
            _PC2TK1TURN = 0;
        }        
        break;
    case 4: //Destination TK-003   Open valv XV014
        _TK2toTK3Options();
        break;
    default:
        break;
    } 
}
void processctrl::_TK2toTK1Options()
{
    switch (_PC2OptionTK1)
    {
    case 0: //Read what option was selected.
        /* code */
        if(bitRead(_raptorHoldingReg[TK002SRC],options1_pc))
        {
            _PC2OptionTK1 = 1;
            bitWrite(_raptorHoldingReg[ValveControl],XV018ctrl,1);
            _raptorHoldingReg[PC002CTRL]=1;
        } else if(bitRead(_raptorHoldingReg[TK002SRC],options2_pc))
        {
            _PC2OptionTK1 = 2;
            bitWrite(_raptorHoldingReg[ValveControl],XV018ctrl,1);
            _raptorHoldingReg[PC002CTRL]=1;
            _raptorHoldingReg[FT003] = 0;
        }else if(bitRead(_raptorHoldingReg[TK002SRC],options2_pc))
        {
            _PC2OptionTK1 = 3;
            bitWrite(_raptorHoldingReg[ValveControl],XV018ctrl,1);
            _raptorHoldingReg[PC002CTRL]=1;
            _raptorHoldingReg[FT003] = 0;                
        }else if(bitRead(_raptorHoldingReg[TK002SRC],options4_pc))
        {
            _PC2OptionTK1 = 4;
        }
        break;
    case 1: //Option 1 is selected.
        //Fill tk001 to specified level    
        if(_raptorHoldingReg[LT001]>_raptorHoldingReg[LT001SP])
        {
            _raptorHoldingReg[PC002CTRL] = 0;
            bitWrite(_raptorHoldingReg[ValveControl],XV018ctrl,0);
            _PC2OptionTK1 = 0;
            _PC2TK2TURN = 0;
        }
        break;    
    case 2: //Option 2 is selected
    //Fill tank to specified level
        if(_raptorHoldingReg[FT003]>_raptorHoldingReg[FT003SP])
        {
            _raptorHoldingReg[PC002CTRL] = 0;
            bitWrite(_raptorHoldingReg[ValveControl],XV018ctrl,0);
            _PC2OptionTK1 = 0;
            _PC2TK2TURN = 0;
            bitWrite(_raptorHoldingReg[TK002SRC],start_pc,0);
        }
        break;
    case 3: //Option 3 is selected
    //Fill tank at specified feed
        //TODO speed control
        if(!bitRead(_raptorHoldingReg[TK002SRC],start_pc))
        {
            _raptorHoldingReg[PC002CTRL] = 0;
            bitWrite(_raptorHoldingReg[ValveControl],XV018ctrl,0);
            _PC2OptionTK1 = 0;
            _PC2TK2TURN = 0;

        }
        break;
    case 4: //Option is selected
        _PC2OptionTK1 = 0;
        _PC2TK2TURN = 0;
        break;
    default:
        break;
    }
}
/*void processctrl::_TK3toOBLOptions()
{
    switch (_PC2TK3OBLOption)
    {
    case 0:
        if(bitRead(_raptorHoldingReg[TK003SRC],options1_pc))
        {
            _PC2TK3OBLOption = 1;
            bitWrite(_raptorHoldingReg[ValveControl],XV015ctrl,1);
            bitWrite(_raptorHoldingReg[ExtrasControl],PC003ctrl,1);  
        } else
        {
            _PC2TK3OBLOption = 2;
            bitWrite(_raptorHoldingReg[ValveControl],XV015ctrl,1);
            bitWrite(_raptorHoldingReg[ExtrasControl],PC003ctrl,1);  
        }              
        break;
    case 1:
        if(bitRead(_raptorHoldingReg[TK003SRC],tk003_pc))
        {
            bitWrite(_raptorHoldingReg[ExtrasControl],PC003ctrl,1);
            bitWrite(_raptorHoldingReg[ValveControl],XV015ctrl,1); 
        }
        else
        {
            bitWrite(_raptorHoldingReg[ExtrasControl],PC003ctrl,0);
            bitWrite(_raptorHoldingReg[ValveControl],XV015ctrl,0); 
            _PC2TK3OBLOption = 0;
        }

    default:
        break;
    }
}
void processctrl::_TK3toTK1Options()
{

}*/
void processctrl::_TK2toTK3Options()
{
    switch (_PC2OptionTK3)
    {
    case 0: //Read what option was selected.
        /* code */
        if(bitRead(_raptorHoldingReg[TK002SRC],options1_pc))
        {
            _PC2OptionTK3 = 1;
            bitWrite(_raptorHoldingReg[ValveControl],XV014ctrl,1);
            _raptorHoldingReg[PC002CTRL]=1;
        } else if(bitRead(_raptorHoldingReg[TK002SRC],options2_pc))
        {
            _PC2OptionTK3 = 2;
            bitWrite(_raptorHoldingReg[ValveControl],XV014ctrl,1);
            _raptorHoldingReg[PC002CTRL]=1;
        }else if(bitRead(_raptorHoldingReg[TK002SRC],options3_pc))
        {
            bitWrite(_raptorHoldingReg[ValveControl],XV014ctrl,1);
            _raptorHoldingReg[PC002CTRL]=1;
            _PC2OptionTK3 = 3;
        }else if(bitRead(_raptorHoldingReg[TK002SRC],options4_pc))
        {
            bitWrite(_raptorHoldingReg[ValveControl],XV014ctrl,1);
            _raptorHoldingReg[PC002CTRL]=1;
            _PC2OptionTK3 = 3;
        }
        break;
    case 1: //Option 1 is selected.
        if(_raptorHoldingReg[LT013]>_raptorHoldingReg[LT013SP])
        {
            _raptorHoldingReg[PC002CTRL] = 0;
            bitWrite(_raptorHoldingReg[ValveControl],XV014ctrl,0);
            _PC2OptionTK1 = 0;
            _PC2TK2TURN = 0;
        }
              
        break;    
    case 2: //Option 2 is selected
        if(_raptorHoldingReg[FT003]>_raptorHoldingReg[FT003SP])
        {
            _raptorHoldingReg[PC002CTRL] = 0;
            bitWrite(_raptorHoldingReg[ValveControl],XV018ctrl,0);
            _PC2OptionTK1 = 0;
            _PC2TK2TURN = 0;
            bitWrite(_raptorHoldingReg[TK002SRC],start_pc,0);
        }
        break;
    case 3: //Option 3 is selected

        break;
    case 4: //Option 4 is selected
        break;
    default:
        break;
    }
}
void processctrl::process2tk3()
{
    if(bitRead(_raptorHoldingReg[InterlockA],INT32)|
    bitRead(_raptorHoldingReg[InterlockB],INT33)|
    bitRead(_raptorHoldingReg[InterlockB],INT27))    
    {
        _PC2TK3TURN = 0;
        return;
    }
    switch (_PC2TK3TURN)
    {
    case 0:
        if(bitRead(_raptorHoldingReg[TK003SRC],start_pc))
        {        
            if(bitRead(_raptorHoldingReg[TK003SRC],OBL_pc))
            {
                _PC2TK3TURN = 1;
            }
            if(bitRead(_raptorHoldingReg[TK003SRC],tk001_pc))
            {
                _PC2TK3TURN = 2;

            }

        }
        /* code */
        break;
    case 1:  //Destination OBL was selected
       // _TK3toOBLOptions();
        break;
    case 2:
       // _TK3toTK1Options();
        break;
    
    default:
        break;
    }
}
void processctrl::process2ver1()
{
    if(bitRead(_raptorHoldingReg[InterlockA],INT3)|
    bitRead(_raptorHoldingReg[InterlockB],INT26)|
    bitRead(_raptorHoldingReg[InterlockB],INT27)|
    bitRead(_raptorHoldingReg[InterlockB],INT35))
    {
        _raptorHoldingReg[VER1RE]=0;
        bitWrite(_raptorHoldingReg[ExtrasControl],PC006ctrl,0);
        return;
    }

    if(bitRead(_raptorHoldingReg[VER001SRC],start_pc))
    {
        bitWrite(_raptorHoldingReg[ExtrasControl],PC006ctrl,1);
        _raptorHoldingReg[VER1RE]=1;
    }
    else
    {
        bitWrite(_raptorHoldingReg[ExtrasControl],PC006ctrl,0);
        _raptorHoldingReg[VER1RE]=0;
    }

}
void processctrl::process2ver2()
{
    /*if(bitRead(_raptorHoldingReg[InterlockA],INT3)|
    bitRead(_raptorHoldingReg[InterlockB],INT26)|
    bitRead(_raptorHoldingReg[InterlockB],INT27)|
    bitRead(_raptorHoldingReg[InterlockB],INT27)|
    bitRead(_raptorHoldingReg[InterlockB],INT35))
    {
        _raptorHoldingReg[VER2RE]=0;
        bitWrite(_raptorHoldingReg[ExtrasControl],PC007ctrl,0);
        return;
    }*/

    if(bitRead(_raptorHoldingReg[VER002SRC],start_pc))
    {
        bitWrite(_raptorHoldingReg[ExtrasControl],PC007ctrl,1);
        _raptorHoldingReg[VER2RE]=1;
    }
    else
    {
        bitWrite(_raptorHoldingReg[ExtrasControl],PC007ctrl,0);
        _raptorHoldingReg[VER2RE]=0;
    }

}
void processctrl::process2vs1()
{
    sr.prit("Entering process 2vs1\n");
    if(bitRead(_raptorHoldingReg[InterlockB],INT28)|
    bitRead(_raptorHoldingReg[InterlockB],INT29))
    {
        _PC2VS1TURN = 0;
        //valves xv003
        bitWrite(_raptorHoldingReg[ValveControl],XV009ctrl,0);
        bitWrite(_raptorHoldingReg[ValveControl],XV010ctrl,0);
        bitWrite(_raptorHoldingReg[ValveControl],XV011ctrl,0);
        bitWrite(_raptorHoldingReg[ValveControl],XV019ctrl,0);
        bitWrite(_raptorHoldingReg[ValveControl],XV003ctrl,0);
        bitWrite(_raptorHoldingReg[ValveControl],XV004ctrl,0);
        return;
    }
    switch (_PC2VS1TURN)
    {
    case 0:   //Process initialiser - here I check what Destination was selected
        sr.prit("Entering process 2vs1 case 0\n");
        if(bitRead(_raptorHoldingReg[TK002SRC],start_pc))
        {   
            if(bitRead(_raptorHoldingReg[VS001SRC],tk003_pc))
            {
                _PC2VS1TURN = 1;                
            }     
            if(bitRead(_raptorHoldingReg[VS001SRC],tk002_pc))
            {
                _PC2VS1TURN = 2;                
            }
            if(bitRead(_raptorHoldingReg[VS001SRC],tk001_pc))
            {
                _PC2VS1TURN = 3;                
            }
            if(bitRead(_raptorHoldingReg[VS001SRC],ver001_pc))
            {
                _PC2VS1TURN = 4;                
            }
            if(bitRead(_raptorHoldingReg[VS001SRC],ver002_pc))
            {
                _PC2VS1TURN = 5;                
            }
            if(bitRead(_raptorHoldingReg[VS001SRC],su001_pc))
            {
                _PC2VS1TURN = 6;                
            }
        }         
        break;
    case 1:  //pump to tk3 Open XV009
        sr.prit("Entering process 2vs1 case 1\n");
        if(bitRead(_raptorHoldingReg[VS001SRC],start_pc))
        {
            _raptorHoldingReg[PC004CTRL] = 1;
            bitWrite(_raptorHoldingReg[ValveControl],XV009ctrl,1);
        }
        else
        {
            _PC2VS1TURN = 0;
            _raptorHoldingReg[PC004CTRL] = 0;
            bitWrite(_raptorHoldingReg[ValveControl],XV009ctrl,0);
        }
        break;
    case 2: //pump to tk2  Open XV010
        sr.prit("Entering process 2vs1 case 2\n");
        if(bitRead(_raptorHoldingReg[VS001SRC],start_pc))
        {
            _raptorHoldingReg[PC004CTRL] = 1;
            bitWrite(_raptorHoldingReg[ValveControl],XV010ctrl,1); 
        }
        else
        {
            _PC2VS1TURN = 0;
            _raptorHoldingReg[PC004CTRL] = 0;
            bitWrite(_raptorHoldingReg[ValveControl],XV010ctrl,0);
        }
        break;
    case 3: //pump to tk1  Open XV011
        sr.prit("Entering process 2vs1 case 3\n");
        if(bitRead(_raptorHoldingReg[VS001SRC],start_pc))
        {
            _raptorHoldingReg[PC004CTRL] = 1;
            bitWrite(_raptorHoldingReg[ValveControl],XV011ctrl,1);
        }
        else
        {
            _PC2VS1TURN = 0;
            _raptorHoldingReg[PC004CTRL]=0;
            bitWrite(_raptorHoldingReg[ValveControl],XV011ctrl,0);
        }
        break;
    case 4: //pump to ver001 Open XV019 and XV003
        sr.prit("Entering process 2vs1 case 4\n");
        if(bitRead(_raptorHoldingReg[VS001SRC],start_pc))
        {
            _raptorHoldingReg[PC004CTRL] = 1;
            bitWrite(_raptorHoldingReg[ValveControl],XV019ctrl,1);
            bitWrite(_raptorHoldingReg[ValveControl],XV003ctrl,1);
        }
        else
        {
            _PC2VS1TURN = 0;
            _raptorHoldingReg[PC004CTRL] = 0;
            bitWrite(_raptorHoldingReg[ValveControl],XV019ctrl,0);
            bitWrite(_raptorHoldingReg[ValveControl],XV003ctrl,0);

        }    
        break;
    case 5: //pump to ver002 Open XV019 and XV004
        sr.prit("Entering process 2vs1 case 5\n");
        if(bitRead(_raptorHoldingReg[VS001SRC],start_pc))
        {
            _raptorHoldingReg[PC004CTRL] = 1;
            bitWrite(_raptorHoldingReg[ValveControl],XV019ctrl,1);
            bitWrite(_raptorHoldingReg[ValveControl],XV004ctrl,1);
        }
        else
        {
            _PC2VS1TURN = 0;
            _raptorHoldingReg[PC004CTRL] = 0;
            bitWrite(_raptorHoldingReg[ValveControl],XV019ctrl,0);
            bitWrite(_raptorHoldingReg[ValveControl],XV004ctrl,0);

        }  
        break;
    case 6: //gravity drainging, Open XV007
        sr.prit("Entering process 2vs1 case 6\n");
        if(bitRead(_raptorHoldingReg[VS001SRC],start_pc))
        {
            _PC2VS1TURN = 0;
        }
        else
        {
            _PC2VS1TURN = 0;
        }
        break;

    default:
        break;
    }
    sr.prit("Exiting process 2vs1\n");
}
/*void processctrl::process2su1()
{
    if(bitRead(_raptorHoldingReg[InterlockA],INT2)|
    bitRead(_raptorHoldingReg[InterlockB],INT26)|
    bitRead(_raptorHoldingReg[InterlockB],INT27)|
    bitRead(_raptorHoldingReg[InterlockB],INT29))
    {
        _PC2SU1TURN = 0;
        return;
    }
    switch (_PC2SU1TURN)
    {
    case 0:
        if(bitRead(_raptorHoldingReg[SU001SRC],start_pc))
        {        
            if(bitRead(_raptorHoldingReg[SU001SRC],OBL_pc))
            {
                _PC2SU1TURN = 1;                
            }
            if(bitRead(_raptorHoldingReg[SU001SRC],tk001_pc))
            {
                _PC2SU1TURN = 2;                
            }

        }
        break;
    case 1://Destination OBL
        if(bitRead(_raptorHoldingReg[TK001SRC],start_pc))
        {        

            bitWrite(_raptorHoldingReg[ExtrasControl],PC005ctrl,1)
            bitWrite(_raptorHoldingReg[ValveControl],XV012ctrl,1);
            _raptorHoldingReg[SU1RES] = 1;
            break;

        }
        else
        {
            bitWrite(_raptorHoldingReg[ExtrasControl],PC005ctrl,0)
            bitWrite(_raptorHoldingReg[ValveControl],XV012ctrl,0);
            _raptorHoldingReg[SU1RES] = 0;
            break;
        }
    case 2://Destination TK-001
        if(bitRead(_raptorHoldingReg[TK001SRC],start_pc))
        {        

            bitWrite(_raptorHoldingReg[ExtrasControl],PC005ctrl,1)
            bitWrite(_raptorHoldingReg[ValveControl],XV013ctrl,1);
            _raptorHoldingReg[SU1RES] = 1;
            break;

        }
        else
        {
            bitWrite(_raptorHoldingReg[ExtrasControl],PC005ctrl,0)
            bitWrite(_raptorHoldingReg[ValveControl],XV013ctrl,0);
            _raptorHoldingReg[SU1RES] = 0;
            break;
        }
    default:
    break;
    }
}*/
