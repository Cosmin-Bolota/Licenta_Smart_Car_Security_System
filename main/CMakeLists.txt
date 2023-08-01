idf_component_register(SRCS "main.c"
                        "../components/BSW/MCAL/ADC/adc.c"
                        "../components/BSW/MCAL/GPIO/gpio.c"
                        "../components/BSW/MCAL/PWM/pwm.c"
                        "../components/BSW/MCAL/WIFI/wifi.c"


                        "../components/BSW/HAL/Buzzer/buzzer.c"
                        "../components/BSW/HAL/Com/com.c"
                        "../components/BSW/HAL/DC_Motor/dc_motor.c"
                        "../components/BSW/HAL/Photo_Resistor/photo_resistor.c"
                        "../components/BSW/HAL/Proximity_Sensor/proximity_sensor.c"
                        "../components/BSW/HAL/Servo_Motor/servo_motor.c"
                        "../components/BSW/HAL/Shift_Register/shift_register.c"
                        "../components/BSW/HAL/Temp_Sensor/temp_sensor.c"

                        "../components/RTE/rte.c"

                        "../components/ASW/Ambient_Light/ambient_light.c"
                        "../components/ASW/Climate_Control_System/climate_control_system.c"
                        "../components/ASW/Headlights/headlights.c"
                        "../components/ASW/Horn/horn.c"
                        "../components/ASW/Locking_System/locking_system.c"
                        "../components/ASW/Security/security.c"
                        "../components/ASW/Trunk/trunk.c"

                        "../components/SRVL/SCHEDULER/scheduler.c"

                    EMBED_FILES "../components/index.html"

                    INCLUDE_DIRS "include" "../components/include")
