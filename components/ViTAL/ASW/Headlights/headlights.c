#include "ASW/Headlights/headlights.h"

#include "RTE/rte.h"

static const char *TAG = "ASW HL";

void ASW_vTaskHeadLightControl()
{
    if(!RTE_bGet_ButtonFindMyCarStatus() && !RTE_bGet_IsLocked()) //set priority order(find my car is active)
    {
        if(RTE_bGet_ButtonHeadlightsStatus())
        {
            RTE_vSetHeadlightsState(ON);
            ESP_LOGI(TAG, "HeadLight: ON (bButton)");
        }
        else{
            uint16_t luminance = RTE_u16Get_PhotoRes();
            if(luminance < 25)
            {
                RTE_vSetHeadlightsState(OFF);
                ESP_LOGI(TAG, "HeadLight: ON ( < 25%% )");
            }
            else{
                RTE_vSetHeadlightsState(OFF);
                ESP_LOGI(TAG, "HeadLight: OFF ( > 25%% )");
            }
        }
        
    }
    
}