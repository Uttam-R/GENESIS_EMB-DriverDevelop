


/**
 * @author Uttam 
 * @brief Case study as a part of Embedded Driver Development
 * @version 0.1
 * @Created Sep 21, 2021
 */

#include "stm32f407xx.h"

/*
 * led pin defined
 *
 */ 

#define LED_PIN_GREEN       GPIO_PIN_NO_12
#define LED_PIN_ORANGE      GPIO_PIN_NO_13
#define LED_PIN_RED         GPIO_PIN_NO_14
#define LED_PIN_BLUE        GPIO_PIN_NO_15



/**
 * States of the system
 * 
 */
#define STATE_START 0
#define STATE_IDLE 1
#define STATE_IGNITION 2
#define STATE_NO_SEATBELT 3
#define STATE_CRASH_NO_SEATBELT 4
#define STATE_CRASH_SEATBELT 5

/**
 *Functions to handle leds
 *
 */
void GPIO_Led_Initialize(GPIO_Handle_t* GpioLed,uint8_t LedPin);
void Toggle_All_LED();
void Reset_All_LED();
void Led_State_Machine(uint8_t* State,uint8_t* led_timer);