/*******************************************************************************
 * COPYRIGHT (C) VITESCO TECHNOLOGIES
 * ALL RIGHTS RESERVED.
 *
 * The reproduction, transmission or use of this document or its
 * contents is not permitted without express written authority.
 * Offenders will be liable for damages. All rights, including rights
 * created by patent grant or registration of a utility model or design,
 * are reserved.
 *******************************************************************************/

#ifndef COMPONENTS_VITAL_BSW_HAL_SERVO_MOTOR_H
#define COMPONENTS_VITAL_BSW_HAL_SERVO_MOTOR_H

#include "global.h"

/*******************************************************************************
 *  Function name    : SERVO_vChangeAngle
 *
 *  Description      : Change the Servo Motor angle
 *
 *  List of arguments: u32ServoAngle -> PWM duty cycle for this angle
 *
 *  Return value     : -
 *
 *******************************************************************************/
void SERVO_vChangeAngle(uint32_t u32ServoAngle);

/* Servo PWMs for different angles */
#define SERVO_MOTOR_0_DEG 550
#define SERVO_MOTOR_90_DEG 1500
#define SERVO_MOTOR_180_DEG 2500

#endif
