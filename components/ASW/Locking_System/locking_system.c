#include "ASW/Locking_System/locking_system.h"

#include "RTE/rte.h"

static const char *TAG = "ASW LOCK";

void ASW_vTaskDoorLockCheck()
{
    if(RTE_bGet_ButtonDoorLockStatus())
    {
        RTE_vSet_Locked(true);
    }
    else{
        RTE_vSet_Locked(false);
    }
}
