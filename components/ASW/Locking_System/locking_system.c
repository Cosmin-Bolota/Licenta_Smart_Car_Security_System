#include "ASW/Locking_System/locking_system.h"

#include "RTE/rte.h"

static const char *TAG = "ASW LOCK";

void ASW_vTaskDoorLockCheck()
{
    if(RTE_bGet_ButtonDoorLockStatus())
    {
        RTE_vSet_Locked(true);
        if(RTE_bGet_ButtonSecurityStatus())
        {
            RTE_vSetShiftRegisterOutput(LOCK_RED, ON);
            RTE_vSetShiftRegisterOutput(LOCK_GREEN, ON);
        }
        else
        {
            RTE_vSetShiftRegisterOutput(LOCK_RED, ON);
            RTE_vSetShiftRegisterOutput(LOCK_GREEN, OFF);
        }
    }
    else{
        RTE_vSet_Locked(false);
        RTE_vSetShiftRegisterOutput(LOCK_RED, OFF);
        RTE_vSetShiftRegisterOutput(LOCK_GREEN, ON);
    }
}
