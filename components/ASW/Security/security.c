#include "ASW/Security/security.h"

#include "RTE/rte.h"
#include "BSW/HAL/Buzzer/buzzer.h"
#include "BSW/HAL/Com/com.h"

extern COM_POST_struct g_POST_DataStructure;

static const char *TAG = "ASW SECURITY";
static bool phase = 1;
void ASW_vTaskFindMyCar()
{
    if(RTE_bGet_ButtonFindMyCarStatus())
    {
        if(phase){
            BUZZER_vChangeDutyCycle(BUZZER_PWM_LVL5);
        }
        else{
            BUZZER_vChangeDutyCycle(BUZZER_PWM_STOP);
        }
        RTE_vSetHeadlightsState(phase);
        RTE_vSetShiftRegisterOutput(ALL_COLORS, phase);
        ESP_LOGI(TAG, "Find my car: ON");
        phase = !phase;
    }
    else
    {
        if(!RTE_bGetBuzzerStatusSecurity() && !RTE_bGet_ButtonHonkStatus())
        {
            BUZZER_vChangeDutyCycle(BUZZER_PWM_STOP);
        }
        if(!RTE_bGet_ButtonHeadlightsStatus() && RTE_u16Get_PhotoRes()>25)
        {
            RTE_vSetHeadlightsState(OFF);
        }
        
        if(!RTE_bGet_ButtonAmbientalLightsStatus())
        {
            RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
        }
        phase = 1;
        ESP_LOGI(TAG, "Find my car: OFF");
    }
}
static uint16_t alarmTime = 0;
void ASW_vTaskCheckDriver()
{
    RTE_vSet_Occupied(RTE_u16GetSavedDistance() < DISTANCE_THRESHOLD);
    if(RTE_bGet_IsOccupied() && RTE_bGet_ButtonSecurityStatus() && RTE_bGet_IsLocked())
    {
        RTE_vSetBuzzerOnSecurity();
        if(phase){
            BUZZER_vChangeDutyCycle(BUZZER_PWM_LVL5);
        }
        else{
            BUZZER_vChangeDutyCycle(BUZZER_PWM_STOP);
        }
        RTE_vSetHeadlightsState(phase);
        RTE_vSetShiftRegisterOutput(ALL_COLORS, phase);
        alarmTime++;
        phase = !phase;
    }
    else if(alarmTime && RTE_bGet_ButtonSecurityStatus() && RTE_bGet_IsLocked())
    {
        if(phase){
            BUZZER_vChangeDutyCycle(BUZZER_PWM_LVL5);
        }
        else{
            BUZZER_vChangeDutyCycle(BUZZER_PWM_STOP);
        }
        RTE_vSetHeadlightsState(phase);
        RTE_vSetShiftRegisterOutput(ALL_COLORS, phase);
        alarmTime++;
        phase = !phase;
    }
    else if(!RTE_bGet_ButtonSecurityStatus())
    {
        RTE_vSetBuzzerOffSecurity();
        alarmTime = 0;
        if(!RTE_bGet_ButtonFindMyCarStatus() && !RTE_bGet_ButtonHonkStatus())
        {
            BUZZER_vChangeDutyCycle(BUZZER_PWM_STOP);
        }

        if(!RTE_bGet_ButtonFindMyCarStatus() && !RTE_bGet_ButtonHeadlightsStatus() && RTE_u16Get_PhotoRes()>25)
        {
            RTE_vSetHeadlightsState(OFF); 
        }

        if(!RTE_bGet_ButtonFindMyCarStatus() && !RTE_bGet_ButtonAmbientalLightsStatus())
        {
            RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
        }
    }
}
