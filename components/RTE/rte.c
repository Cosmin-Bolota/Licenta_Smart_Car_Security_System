#include "RTE/rte.h"

#include "BSW/HAL/Buzzer/buzzer.h"
#include "BSW/HAL/Com/com.h" 
#include "BSW/HAL/DC_Motor/dc_motor.h"
#include "BSW/HAL/Proximity_Sensor/proximity_sensor.h"
#include "BSW/HAL/Servo_Motor/servo_motor.h"
#include "BSW/HAL/Shift_Register/shift_register.h"

static const char *TAG = "RTE";

extern COM_GET_struct g_GET_DataStructure;
extern COM_POST_struct g_POST_DataStructure;

static bool sg_bIsAlarmOn = false;
static bool BuzzerStatus = false;
static bool BuzzerStatusSecurity = false;
static bool HeadLightsStatus = false;

bool RTE_bGet_ButtonFanStatus(void)
{
	return g_POST_DataStructure.bButtonFan;
}

bool RTE_bGet_ButtonHonkStatus(void)
{
	return g_POST_DataStructure.bButtonHonk;
}

bool RTE_bGet_ButtonSecurityStatus(void)
{
	return g_POST_DataStructure.bButtonSecurity;
}

bool RTE_bGet_ButtonDoorLockStatus(void)
{
	return g_POST_DataStructure.bButtonDoorLock;
}

uint8_t RTE_u8Get_UserTemperature(void)
{
	return g_POST_DataStructure.u8UserTemperature;
}

bool RTE_bGet_ButtonTrunkStatus(void)
{
	return g_POST_DataStructure.bButtonTrunk;
}

bool RTE_bGet_ButtonHeadlightsStatus(void)
{
	return g_POST_DataStructure.bButtonHeadlights;
}

uint8_t RTE_u8Get_Temperature(void)
{
	return g_GET_DataStructure.u8Temperature;
}

uint8_t RTE_u8Get_Humidity(void)
{
	return g_GET_DataStructure.u8Humidity;
}

uint8_t RTE_u8Get_Comfort(void)
{
	return g_GET_DataStructure.u8Comfort;
}

uint16_t RTE_u16Get_PhotoRes(void)
{
	return g_GET_DataStructure.u16PhotoRes;
}

bool RTE_bGet_IsLocked(void)
{
	return g_GET_DataStructure.bIsLocked;
}

bool RTE_bGet_IsOccupied(void)
{
	return g_GET_DataStructure.bIsOccupied;
}

void RTE_vSet_Temperature(uint8_t u8Data)
{
	g_GET_DataStructure.u8Temperature = u8Data;
}

void RTE_vSet_Humidity(uint8_t u8Data)
{
	g_GET_DataStructure.u8Humidity = u8Data;
}

void RTE_vSet_Comfort(uint8_t u8Data)
{
	g_GET_DataStructure.u8Comfort = u8Data;
}

void RTE_vSet_PhotoRes(uint16_t u16Data)
{
	g_GET_DataStructure.u16PhotoRes = u16Data;
}

void RTE_vSet_Locked(bool bStatus)
{
	g_GET_DataStructure.bIsLocked = bStatus;
}

void RTE_vSet_Occupied(bool bStatus)
{
	g_GET_DataStructure.bIsOccupied = bStatus;
}

void RTE_vSetBuzzerDutyCycle(uint32_t u32DutyCycle)
{
	BUZZER_vChangeDutyCycle(u32DutyCycle);
}

void RTE_vSet_ButtonHonkDone(void)
{
	g_POST_DataStructure.bButtonHonk = false;
}

void RTE_vSet_ButtonFindMyCarDone(void)
{
	g_POST_DataStructure.bButtonFindMyCar = false;
}

void RTE_vSetDCMotorSpeed(uint32_t u32Speed)
{
	DCMOT_vChangeSpeed(u32Speed);
}

void RTE_vSetDCMotorSpeedReverse(uint32_t u32Speed)
{
	DCMOT_vChangeSpeedReverse(u32Speed);
}

uint8_t RTE_u8Get_UserDCMs(void)
{
	return g_POST_DataStructure.u8UserdataDCMs;
}

uint8_t RTE_u8Get_UserDCMd(void)
{
	return g_POST_DataStructure.u8UserdataDCMd;
}

uint8_t RTE_u8Get_UserServo(void)
{
	return g_POST_DataStructure.u8UserdataServomotor;
}

uint8_t RTE_u8Get_UserBuzzer(void)
{
	return g_POST_DataStructure.u8UserdataBuzzer;
}

bool RTE_bGet_ButtonAmbientalLightsStatus(void)
{
	return g_POST_DataStructure.bButtonAmbientalLights;
}

bool RTE_bGet_ButtonFindMyCarStatus(void)
{
	return g_POST_DataStructure.bButtonFindMyCar;
}

bool RTE_bGet_ButtonShiftRegStatus(void)
{
	return g_POST_DataStructure.bButtonShiftReg;
}

bool RTE_bGet_ButtonRLedStatus(void)
{
	return g_POST_DataStructure.bButtonRLed;
}

bool RTE_bGet_ButtonGLedStatus(void)
{
	return g_POST_DataStructure.bButtonGLed;
}

bool RTE_bGet_ButtonBLedStatus(void)
{
	return g_POST_DataStructure.bButtonBLed;
}

uint8_t RTE_u16GetSavedDistance(void)
{
	return g_GET_DataStructure.u8Distance;
}


void RTE_vSetLockLightState(uint8_t u8Light)
{
	if (u8Light == LOCK_GREEN)
	{
		RTE_vSetShiftRegisterOutput(LOCK_RED, LOW);
		RTE_vSetShiftRegisterOutput(LOCK_GREEN, HIGH);
	}
	else if (u8Light == LOCK_RED)
	{
		RTE_vSetShiftRegisterOutput(LOCK_GREEN, LOW);
		RTE_vSetShiftRegisterOutput(LOCK_RED, HIGH);
	}
	else
	{
		ESP_LOGI(TAG, "Invalid relay level");
	}
}

void RTE_vSetServoPosition(uint32_t u32Position)
{
	SERVO_vChangeAngle(u32Position);
}

void RTE_vSetHeadlightsState(bool bState)
{
	RTE_vSetShiftRegisterOutput(HEAD_LIGHTS_POS, bState);
}

void RTE_vSetAmbientalLightsState(bool bState)
{
	/*The function will render the R-G-B color sequence.
	bState will be the button status from WebApp */

	static uint8_t s_u8ColorState = STATE_RED;

	if (bState == ON)
	{
		switch (s_u8ColorState)
		{
		case STATE_RED:
			RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
			RTE_vSetShiftRegisterOutput(RED, HIGH);
			s_u8ColorState = STATE_RED_GREEN;
			break;
		case STATE_GREEN:
			RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
			RTE_vSetShiftRegisterOutput(GREEN, HIGH);
			s_u8ColorState = STATE_GREEN_BLUE;
			break;
		case STATE_BLUE:
			RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
			RTE_vSetShiftRegisterOutput(BLUE, HIGH);
			s_u8ColorState = STATE_RED_BLUE;
			break;
		case STATE_RED_GREEN:
			RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
			RTE_vSetShiftRegisterOutput(RED_GREEN, HIGH);
			s_u8ColorState = STATE_GREEN;
			break;
		case STATE_RED_BLUE:
			RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
			RTE_vSetShiftRegisterOutput(RED_BLUE, HIGH);
			s_u8ColorState = STATE_ALL_COLORS;
			break;
		case STATE_GREEN_BLUE:
			RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
			RTE_vSetShiftRegisterOutput(GREEN_BLUE, HIGH);
			s_u8ColorState = STATE_BLUE;
			break;
		case STATE_ALL_COLORS:
			RTE_vSetShiftRegisterOutput(ALL_COLORS, HIGH);
			s_u8ColorState = STATE_RED;
			break;
		default:
			ESP_LOGI(TAG, "RGB ERROR");
			break;
		}
	}
	else if (bState == OFF)
	{
		RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
		s_u8ColorState = STATE_RED;
	}
	else
	{
		ESP_LOGI(TAG, "AMBIENTAL LIGHTS ERROR");
	}
}

void RTE_vSetRGBLedState() 
{
	/* this function will control the RGB led through the shift register depending on the combination of pressed buttons 
	   (R, G or B button or a combination of these)*/
	if (RTE_bGet_ButtonRLedStatus() && RTE_bGet_ButtonGLedStatus() && RTE_bGet_ButtonBLedStatus())
	{
		RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
		RTE_vSetShiftRegisterOutput(ALL_COLORS, HIGH);
	}
	else if (RTE_bGet_ButtonRLedStatus() && !RTE_bGet_ButtonGLedStatus() && RTE_bGet_ButtonBLedStatus())
	{
		RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
		RTE_vSetShiftRegisterOutput(RED_BLUE, HIGH);
	}
	else if (RTE_bGet_ButtonRLedStatus() && RTE_bGet_ButtonGLedStatus() && !RTE_bGet_ButtonBLedStatus())
	{
		RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
		RTE_vSetShiftRegisterOutput(RED_GREEN, HIGH);
	}
	else if (RTE_bGet_ButtonRLedStatus() && !RTE_bGet_ButtonGLedStatus() && !RTE_bGet_ButtonBLedStatus())
	{
		RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
		RTE_vSetShiftRegisterOutput(RED, HIGH);
	}
	else if (!RTE_bGet_ButtonRLedStatus() && RTE_bGet_ButtonGLedStatus() && RTE_bGet_ButtonBLedStatus())
	{
		RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
		RTE_vSetShiftRegisterOutput(GREEN_BLUE, HIGH);
	}
	else if (!RTE_bGet_ButtonRLedStatus() && !RTE_bGet_ButtonGLedStatus() && RTE_bGet_ButtonBLedStatus())
	{
		RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
		RTE_vSetShiftRegisterOutput(BLUE, HIGH);
	}
	else if (!RTE_bGet_ButtonRLedStatus() && RTE_bGet_ButtonGLedStatus() && !RTE_bGet_ButtonBLedStatus())
	{
		RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
		RTE_vSetShiftRegisterOutput(GREEN, HIGH);
	}
	else if (!RTE_bGet_ButtonRLedStatus() && !RTE_bGet_ButtonGLedStatus() && !RTE_bGet_ButtonBLedStatus())
	{
		RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
	}
	else
	{
		ESP_LOGI(TAG, "AMBIENTAL LIGHTS ERROR");
	}
}

void RTE_vSetShiftRegisterOutput(shift_register_positions_t u8ComponentMask, bool bLevel)
{
	/* this function will send to the shift register to reproduce the color sequence */
	static uint8_t s_u8CurrentData = 0;

	if (bLevel == HIGH)
	{
		s_u8CurrentData |= u8ComponentMask;
	}
	else if (bLevel == LOW)
	{
		s_u8CurrentData &= ~(u8ComponentMask);
	}
	else
	{
		ESP_LOGI(TAG, "Invalid level for shift register");
	}

	SHIFTREG_vOutput8Bits(s_u8CurrentData);
}

uint16_t RTE_u16GetDistance(void)
{
	return PROX_u16Read();
}

void RTE_vSetAlarmOn(void)
{
	sg_bIsAlarmOn = true;
}

void RTE_vSetAlarmOff(void)
{
	sg_bIsAlarmOn = false;
}

bool RTE_bGetAlarmStatus(void)
{
	return sg_bIsAlarmOn;
}

void RTE_vSetBuzzerOn(void)
{
	BuzzerStatus = true;
}

void RTE_vSetBuzzerOnSecurity(void)
{
	BuzzerStatusSecurity = true;
}

void RTE_vSetBuzzerOff(void)
{
	BuzzerStatus = false;
}

void RTE_vSetBuzzerOffSecurity(void)
{
	BuzzerStatusSecurity = false;
}

bool RTE_bGetBuzzerStatus(void)
{
	return BuzzerStatus;
}

bool RTE_bGetBuzzerStatusSecurity(void)
{
	return BuzzerStatusSecurity;
}