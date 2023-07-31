#include "SRVL/SCHEDULER/scheduler.h"

#include "global.h"

void app_main(void)
{
  
  SYSTEM_vInit();
  
  SYSTEM_vTaskScheduler();

}
