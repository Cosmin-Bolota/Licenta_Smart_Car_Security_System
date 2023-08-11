#ifndef COMPONENTS_VITAL_RTE_H
#define COMPONENTS_VITAL_RTE_H

#include "global.h"

typedef enum
{
	LOCK_GREEN = (uint8_t)(1 << 1),
	LOCK_RED = (uint8_t)(1 << 2),
	RGB_RED_POS = (uint8_t)(1 << 4),
	RGB_GREEN_POS = (uint8_t)(1 << 5),
	RGB_BLUE_POS = (uint8_t)(1 << 3),
	HEAD_LIGHTS_POS = (uint8_t)((1 << 6) | (1 << 7))
} shift_register_positions_t;

typedef enum
{
	RED = RGB_RED_POS,
	GREEN = RGB_GREEN_POS,
	BLUE = RGB_BLUE_POS,
	RED_GREEN = RGB_RED_POS | RGB_GREEN_POS,
	RED_BLUE = RGB_RED_POS | RGB_BLUE_POS,
	GREEN_BLUE = RGB_GREEN_POS | RGB_BLUE_POS,
	ALL_COLORS = RGB_RED_POS | RGB_GREEN_POS | RGB_BLUE_POS
} rgb_states_masks_t;

typedef enum
{
	STATE_RED = 0,
	STATE_GREEN,
	STATE_BLUE,
	STATE_RED_GREEN,
	STATE_RED_BLUE,
	STATE_GREEN_BLUE,
	STATE_ALL_COLORS
} rgb_states_t;

static bool BuzzerStatusSecurity; //To know when the alarm activated during the enabled security

bool RTE_bGet_ButtonFanStatus(void);
bool RTE_bGet_ButtonHonkStatus(void);
bool RTE_bGet_ButtonSecurityStatus(void);
bool RTE_bGet_ButtonDoorLockStatus(void);
uint8_t RTE_u8Get_UserTemperature(void);

bool RTE_bGet_ButtonTrunkStatus(void);
bool RTE_bGet_ButtonHeadlightsStatus(void);

uint8_t RTE_u8Get_Temperature(void);
uint8_t RTE_u8Get_Humidity(void);
uint8_t RTE_u8Get_Comfort(void);
uint16_t RTE_u16Get_PhotoRes(void);

bool RTE_bGet_IsLocked(void);
bool RTE_bGet_IsOccupied(void);

void RTE_vSet_Temperature(uint8_t u8Data);
void RTE_vSet_Humidity(uint8_t u8Data);
void RTE_vSet_Comfort(uint8_t u8Data);
void RTE_vSet_PhotoRes(uint16_t u16Data);
void RTE_vSet_Locked(bool bStatus);
void RTE_vSet_Occupied(bool bStatus);

void RTE_vSetBuzzerDutyCycle(uint32_t u32DutyCycle);
void RTE_vSet_ButtonHonkDone(void);
void RTE_vSet_ButtonFindMyCarDone(void);
void RTE_vSetDCMotorSpeed(uint32_t u32Speed);
void RTE_vSetDCMotorSpeedReverse(uint32_t u32Speed);

uint8_t RTE_u8Get_UserDCMs(void);
uint8_t RTE_u8Get_UserDCMd(void);
uint8_t RTE_u8Get_UserServo(void);
uint8_t RTE_u8Get_UserBuzzer(void);

bool RTE_bGet_ButtonAmbientalLightsStatus(void);
bool RTE_bGet_ButtonFindMyCarStatus(void);
bool RTE_bGet_ButtonShiftRegStatus(void);

bool RTE_bGet_ButtonRLedStatus(void);
bool RTE_bGet_ButtonGLedStatus(void);
bool RTE_bGet_ButtonBLedStatus(void);

void RTE_vSetLockLightState(uint8_t u8Light);
void RTE_vSetServoPosition(uint32_t u32Position);
void RTE_vSetHeadlightsState(bool bState);

void RTE_vSetRGBLedState();

void RTE_vSetAmbientalLightsState(bool bState);
void RTE_vSetShiftRegisterOutput(shift_register_positions_t u8ComponentMask, bool bLevel);
uint16_t RTE_u16GetDistance(void);
uint8_t RTE_u16GetSavedDistance(void);
void RTE_vSetAlarmOn(void);
void RTE_vSetAlarmOff(void);
bool RTE_bGetAlarmStatus(void);

void RTE_vSetBuzzerOnSecurity(void);
void RTE_vSetBuzzerOffSecurity(void);
bool RTE_bGetBuzzerStatusSecurity(void);

#define OFF false
#define ON true

#define LOW false
#define HIGH true

#define DC_MOTOR_OFF 0
#define DC_MOTOR_LOW 15000
#define DC_MOTOR_HIGH 20000

#define DC_MOTOR_20 4000
#define DC_MOTOR_40 8000
#define DC_MOTOR_60 12000
#define DC_MOTOR_80 16000

#define BUZZER_OFF 0
#define BUZZER_ON 1000
#define BUZZER_LVL2 2000
#define BUZZER_LVL3 3000
#define BUZZER_LVL4 4000
#define BUZZER_LVL5 5000

#define TRUNK_CLOSE 1500
#define TRUNK_OPEN 2500
#define TRUNK_LOCKED 550
#define SERVO_MOTOR_0_DEG 550
#define SERVO_MOTOR_90_DEG 1500
#define SERVO_MOTOR_180_DEG 2500

#endif
