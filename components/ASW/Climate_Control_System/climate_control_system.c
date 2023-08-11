#include "ASW/Climate_Control_System/climate_control_system.h"

#include "RTE/rte.h"

static const char *TAG = "ASW CCS";

static int flag=0;  //the flag will show the DCmotor status and if is taken by ASW_vTaskDCMs or ASW_vTaskDCMd
static int flagDCMs=0; //the flagDCMs will show if the DC motor is taken by ASW_vTaskDCMs
static int flagDCMd=0; //the flagDCMd will show if the DC motor is taken by ASW_vTaskDCMd
static int flagFanTempTreshold = 0;//the flagFanTempTreshold will show if the DC motor is taken by ASW_vTaskFanTempTreshold

uint8_t u8CalculateComfort(uint8_t u8Temp, uint8_t u8Hum)
{
	double d64HeatIndex = 0;
	double d64_C1 = -8.78469475556;
	double d64_C2 = 1.61139411;
	double d64_C3 = 2.33854883889;
	double d64_C4 = -0.14611605;
	double d64_C5 = -0.012308094;
	double d64_C6 = -0.0164248277778;
	double d64_C7 = 0.002211732;
	double d64_C8 = 0.00072546;
	double d64_C9 = -0.000003582;

	d64HeatIndex = d64_C1 + d64_C2 * u8Temp + d64_C3 * u8Hum
			+ d64_C4 * u8Temp * u8Hum + d64_C5 * u8Temp * u8Temp
			+ d64_C6 * u8Hum * u8Hum + d64_C7 * u8Temp * u8Temp * u8Hum
			+ d64_C8 * u8Temp * u8Hum * u8Hum
			+ d64_C9 * u8Temp * u8Temp * u8Hum * u8Hum;

	RTE_vSet_Comfort((uint8_t) d64HeatIndex);

	return (uint8_t) d64HeatIndex;
}

void ASW_vTaskFanTempTreshold()
{
	uint8_t temp = RTE_u8Get_Temperature();
	uint8_t tempUser = RTE_u8Get_UserTemperature();

	if(RTE_bGet_ButtonFanStatus())
	{
		if(temp > tempUser && flag==0 && flagDCMs==0 && flagDCMd==0)
		{
			flagFanTempTreshold = 1;
			if(temp - tempUser <= 5)
			{
				RTE_vSetDCMotorSpeed(DC_MOTOR_20);
			}
			else if(temp - tempUser <= 10)
			{
				RTE_vSetDCMotorSpeed(DC_MOTOR_40);
			}
			else if(temp - tempUser <= 15)
			{
				RTE_vSetDCMotorSpeed(DC_MOTOR_60);
			}
			else if(temp - tempUser <= 20)
			{
				RTE_vSetDCMotorSpeed(DC_MOTOR_80);
			}
			else
			{
				RTE_vSetDCMotorSpeed(DC_MOTOR_HIGH);
			}
			ESP_LOGI(TAG, "FanTempTreshold is active!");
		}
		else 
		{
			flagFanTempTreshold = 0;
		}
	}
	else
	{
		RTE_vSetDCMotorSpeed(DC_MOTOR_OFF);
	}
	
}