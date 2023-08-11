#include "ASW/Horn/horn.h"

#include "RTE/rte.h"

int flagHorn=0;
int flagBuzzerTest=0;
extern bool BuzzerStatusSecurity;

void ASW_vTaskBuzzer(void)
{
	if(!RTE_bGet_ButtonFindMyCarStatus() && !RTE_bGetBuzzerStatusSecurity())
	{
		if (RTE_bGet_ButtonHonkStatus())
		{
			RTE_vSetBuzzerDutyCycle(BUZZER_LVL5);
		}
		else
		{
			RTE_vSetBuzzerDutyCycle(BUZZER_OFF);
		}
	}
}
