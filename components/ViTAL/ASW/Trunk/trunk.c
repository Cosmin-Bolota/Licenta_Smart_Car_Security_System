#include "ASW/Trunk/trunk.h"

#include "RTE/rte.h"

static const char *TAG = "ASW TRUNK";

int flagTrunk=0; 
int flagServoTest=0; 
static bool p0=0, p90=0, p180=0;


void ASW_vTaskServoTest(void)
{
    uint8_t p = RTE_u8Get_UserServo();
	if (!RTE_bGet_ButtonTrunkStatus())
	{
        if(p==90 && p90==0) //if p is equal to 90 (degrees)
        {
            p0=0; p90=1; p180=0;
            flagServoTest=1; //servomotor is taken by ASW_vTaskServoTest
            RTE_vSetServoPosition(SERVO_MOTOR_90_DEG); //set the duty cycle corresponding to 90 deg
        }
        else if(p==180 && p180==0) //if p is equal to 180 (degrees)
        {
            p0=0; p90=0; p180=1;
            flagServoTest=1; //servomotor is taken by ASW_vTaskServoTest
            RTE_vSetServoPosition(SERVO_MOTOR_180_DEG); //set the duty cycle corresponding to 180 deg
        }
        else if(p==0 && p0==0) //if p is equal to 0 (degrees)
        {
            p0=1; p90=0; p180=0;
            flagServoTest=0; //servomotor is released by ASW_vTaskServoTest
            RTE_vSetServoPosition(SERVO_MOTOR_0_DEG); //set the duty cycle corresponding to 0 deg 
	    }
    }
}

bool lastStatus = 0;

void ASW_vTaskTrunkCheck(void)
{
    if(!RTE_bGet_IsLocked() && !flagServoTest)
    {
        if (!RTE_bGet_ButtonTrunkStatus() && lastStatus != RTE_bGet_ButtonTrunkStatus())
        {   
            if(!p90)
            {
                RTE_vSetServoPosition(TRUNK_CLOSE); //set the duty cycle corresponding to 0 deg
                p0=0; p90=1; p180=0;
            }
            lastStatus = RTE_bGet_ButtonTrunkStatus();
        }
        else if(lastStatus != RTE_bGet_ButtonTrunkStatus()){
            if(!p180)
            {
                RTE_vSetServoPosition(TRUNK_OPEN); //set the duty cycle corresponding to 90 deg
                p0=0; p90=0; p180=1;
            }
            lastStatus = RTE_bGet_ButtonTrunkStatus();
        }
        else{
            if(!p90)
            {
                RTE_vSetServoPosition(TRUNK_CLOSE); //set the duty cycle corresponding to 0 deg
                p0=0; p90=1; p180=0;
            }
        }
    }
    else if(RTE_bGet_IsLocked() && !flagServoTest && lastStatus)
    {
        if(!p90)
            {
                RTE_vSetServoPosition(TRUNK_CLOSE); //set the duty cycle corresponding to 0 deg
                p0=0; p90=1; p180=0;
            }
        vTaskDelay(100);
        lastStatus = 0;
    }
    else{
        if(!p90)
            {
                RTE_vSetServoPosition(TRUNK_CLOSE); //set the duty cycle corresponding to 0 deg
                p0=0; p90=1; p180=0;
            }
    }
}