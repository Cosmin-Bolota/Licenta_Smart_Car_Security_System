#include "ASW/Trunk/trunk.h"
#include "RTE/rte.h"

static const char *TAG = "ASW TRUNK";

static bool flagServoTest = 0; 

void ASW_vTaskServoTest(void)
{
    uint8_t p = RTE_u8Get_UserServo();
	if (!RTE_bGet_ButtonTrunkStatus() && !RTE_bGet_IsLocked())
	{
        if(p==90) //if p is equal to 90 (degrees)
        {
            flagServoTest=1; //servomotor is taken by ASW_vTaskServoTest
            RTE_vSetServoPosition(SERVO_MOTOR_90_DEG); //set the duty cycle corresponding to 90 deg
        }
        else if(p==180) //if p is equal to 180 (degrees)
        {
            flagServoTest=1; //servomotor is taken by ASW_vTaskServoTest
            RTE_vSetServoPosition(SERVO_MOTOR_180_DEG); //set the duty cycle corresponding to 180 deg
        }
        else if(p==0) //if p is equal to 0 (degrees)
        {
            flagServoTest=0; //servomotor is released by ASW_vTaskServoTest
            RTE_vSetServoPosition(TRUNK_CLOSE); //set the duty cycle corresponding to 90 deg
	    }
    }
}

void ASW_vTaskTrunkCheck(void)
{
    if(!RTE_bGet_IsLocked() && !flagServoTest)
    {
        if (RTE_bGet_ButtonTrunkStatus())
        {   
            RTE_vSetServoPosition(TRUNK_OPEN); //set the duty cycle corresponding to 180 deg
        }
        else
        {
            RTE_vSetServoPosition(TRUNK_CLOSE); //set the duty cycle corresponding to 90 deg
        } 
    }
    else if(RTE_bGet_IsLocked())
    {
        RTE_vSetServoPosition(TRUNK_LOCKED); //set the duty cycle corresponding to 0 deg
    }
}