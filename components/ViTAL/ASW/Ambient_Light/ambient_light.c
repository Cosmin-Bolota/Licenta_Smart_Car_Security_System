#include "ASW/Ambient_Light/ambient_light.h"
#include "BSW/HAL/Shift_Register/shift_register.h"
#include "RTE/rte.h"

static const char *TAG = "ASW AL";


void ASW_vTaskShiftRegControlTest(void)
{
	if(RTE_bGet_ButtonFindMyCarStatus() == 0) //set priority order(find my car is active)
	{
		//if the button is pressed
		if (RTE_bGet_ButtonShiftRegStatus())
		{
			int8_t i8Index = 1;
			uint8_t lastdata=0;
			for (; i8Index <= 8; i8Index++)
			{
				lastdata = lastdata + (1 << i8Index);
				SHIFTREG_vOutput8Bits(lastdata); 
				vTaskDelay(100);
			}
		}
		else if(!RTE_bGet_ButtonRLedStatus() && !RTE_bGet_ButtonGLedStatus() && !RTE_bGet_ButtonBLedStatus() && !RTE_bGet_ButtonAmbientalLightsStatus())
		{
			RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
		}
	}	
}

void ASW_vTaskRGBLedControlTest(void)
{
	if(RTE_bGet_ButtonFindMyCarStatus() == 0) //set priority order(find my car is active)
	{
		//if one of the buttons is pressed
		if(!RTE_bGet_ButtonAmbientalLightsStatus() && !RTE_bGet_ButtonShiftRegStatus())
		{
			RTE_vSetRGBLedState();
		}
	}
	
}

void ASW_vTaskAmbientalLight(void)
{
	if(!RTE_bGet_IsLocked())
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