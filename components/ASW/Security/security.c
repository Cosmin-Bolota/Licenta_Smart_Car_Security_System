#include "ASW/Security/security.h"

#include "RTE/rte.h"
#include "BSW/HAL/Buzzer/buzzer.h"
#include "BSW/HAL/Com/com.h"

extern COM_POST_struct g_POST_DataStructure;

static const char *TAG = "ASW SECURITY";
int flagFindMyCar = 0;
void ASW_vTaskFindMyCar()
{
    flagFindMyCar = RTE_bGet_ButtonFindMyCarStatus();
    if(flagFindMyCar)
    {
        RTE_vSetBuzzerOn();
        BUZZER_vChangeDutyCycle(BUZZER_PWM_LVL5);
        
        RTE_vSetHeadlightsState(ON);
        RTE_vSetShiftRegisterOutput(ALL_COLORS, HIGH);
        ESP_LOGI(TAG, "Security: ON");
        ets_delay_us(8000);
    }
    else
    {
        if(!RTE_bGetBuzzerStatusSecurity())
        {
            BUZZER_vChangeDutyCycle(BUZZER_PWM_STOP);
            RTE_vSetBuzzerOff();
        }
        if(!RTE_bGet_ButtonHeadlightsStatus())
        {
            RTE_vSetHeadlightsState(OFF);
        }
        
        if(!RTE_bGet_ButtonAmbientalLightsStatus())
        {
            RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
        }
        ESP_LOGI(TAG, "Security: OFF");
    }
}

void ASW_vTaskCheckDriver()
{
    RTE_vSet_Occupied(RTE_u16GetSavedDistance() < DISTANCE_THRESHOLD);
    if(RTE_bGet_IsOccupied() && RTE_bGet_IsLocked())
    {
        for(uint8_t var = 0; var<10; var++)
        {
            if(var%2 == 0)
            {
                RTE_vSetBuzzerOnSecurity();
                BUZZER_vChangeDutyCycle(BUZZER_PWM_LVL5);
                RTE_vSetHeadlightsState(ON);
                RTE_vSetShiftRegisterOutput(ALL_COLORS, HIGH);
            }
            else
            {
                RTE_vSetBuzzerOffSecurity();
                BUZZER_vChangeDutyCycle(BUZZER_PWM_STOP);
                if(!RTE_bGet_ButtonHeadlightsStatus())
                {
                   RTE_vSetHeadlightsState(OFF); 
                }
                RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
            }
            vTaskDelay(200);
        }
    }
    else if(!RTE_bGet_IsLocked())
    {
        if(!RTE_bGetBuzzerStatus())
        {
            BUZZER_vChangeDutyCycle(BUZZER_PWM_STOP);
        }

        RTE_vSetBuzzerOffSecurity();
        
        if(!RTE_bGet_ButtonHeadlightsStatus())
        {
            RTE_vSetHeadlightsState(OFF); 
        }
        if(!RTE_bGet_ButtonAmbientalLightsStatus())
        {
            RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
        }
    }
}
