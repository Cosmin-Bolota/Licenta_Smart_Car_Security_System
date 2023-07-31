#include "ASW/Horn/horn.h"

#include "RTE/rte.h"

int flagHorn=0;
int flagBuzzerTest=0;
extern bool BuzzerStatusSecurity;

void ASW_vTaskBuzzerTest(void)
{

    uint8_t p = RTE_u8Get_UserBuzzer();
	if (!RTE_bGet_ButtonHonkStatus())
	{
		if(RTE_bGet_ButtonFindMyCarStatus() == 0 && BuzzerStatusSecurity == 0) //set priority order(find my car is active)
		{
			if(p)
			{
				RTE_vSetBuzzerOn();
			}
			if(p==20) //if p is equal to the filling factor 20
			{
				RTE_vSetBuzzerDutyCycle(BUZZER_ON); //buzzer with a duty cycle of 20%
				flagBuzzerTest=1;
			}
			else if(p==40) //if p is equal to the filling factor 40
			{
				RTE_vSetBuzzerDutyCycle(BUZZER_LVL2); //buzzer with a duty cycle of 40%
				flagBuzzerTest=1;
			}
			else if(p==60) //if p is equal to the filling factor 60
			{
				RTE_vSetBuzzerDutyCycle(BUZZER_LVL3); //buzzer with a duty cycle of 60%
				flagBuzzerTest=1;
			}
			else if(p==80) //if p is equal to the filling factor 80
			{
				RTE_vSetBuzzerDutyCycle(BUZZER_LVL4); //buzzer with a duty cycle of 80%
				flagBuzzerTest=1;
			}
			else if(p==100) //if p is equal to the filling factor 100
			{
				RTE_vSetBuzzerDutyCycle(BUZZER_LVL5); //buzzer with a duty cycle of 100%
				flagBuzzerTest=1;
			}
			else if(flagHorn==0) //if p is equal to the filling factor 0
			{
				if(!RTE_bGetBuzzerStatus() && !RTE_bGetBuzzerStatusSecurity())
				{
					RTE_vSetBuzzerDutyCycle(BUZZER_OFF); //buzzer with a duty cycle of 0%
					RTE_vSetBuzzerOff();
				}
				flagBuzzerTest=0;
			}
			
			if(flagBuzzerTest)
			{
				vTaskDelay(500);
				RTE_vSetBuzzerDutyCycle(BUZZER_OFF); //buzzer with a duty cycle of 0%
				flagBuzzerTest = 0;
			}
		}
	}
	else
	{
		if(RTE_bGet_ButtonFindMyCarStatus() == 0 && BuzzerStatusSecurity == 0) //set priority order(find my car is active)
		{
			RTE_vSetBuzzerOn();
			RTE_vSetBuzzerDutyCycle(BUZZER_LVL5);
		}
	}
}
