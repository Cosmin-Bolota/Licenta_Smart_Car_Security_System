#include "ASW/Ambient_Light/ambient_light.h"
#include "BSW/HAL/Shift_Register/shift_register.h"
#include "RTE/rte.h"

static const char *TAG = "ASW AL";

void ASW_vTaskAmbientalLight(void)
{
	if(!RTE_bGet_ButtonSecurityStatus() || !RTE_bGet_ButtonFindMyCarStatus())
	{
		if(RTE_bGet_ButtonAmbientalLightsStatus())
		{
			RTE_vSetAmbientalLightsState(ON);
		}
		else{
			RTE_vSetAmbientalLightsState(OFF);
		}
	}
}