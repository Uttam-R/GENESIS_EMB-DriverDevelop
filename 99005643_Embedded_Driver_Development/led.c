/**
 * @file main.c
 * @author Uttam 
 * @brief Case study as a part of Embedded Driver Development
 * @version 0.1
 * @Created Sep 21, 2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include"led.h"

/**
 * @brief Initialize an led, 
 * 
 * @param GpioLed 
 * @param LedPin 
 */
void GPIO_Led_Initialize(GPIO_Handle_t* GpioLed,uint8_t LedPin){

	GpioLed->pGPIOx = GPIOD;
	GpioLed->GPIO_PinConfig.GPIO_PinNumber = LedPin;
	GpioLed->GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed->GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed->GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed->GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
}


/**
 * @brief Reset the output on all leds
 * 
 */
void Reset_All_LED(){

    GPIO_WriteToOutputPin(GPIOD,LED_PIN_ORANGE,RESET);
    GPIO_WriteToOutputPin(GPIOD,LED_PIN_RED,RESET);
    GPIO_WriteToOutputPin(GPIOD,LED_PIN_GREEN,RESET);
    GPIO_WriteToOutputPin(GPIOD,LED_PIN_BLUE,RESET);
    
}

/**
 * @brief Toggle output state of all leds
 * 
 */
void Toggle_All_LED(){
    GPIO_ToggleOutputPin(GPIOD,LED_PIN_ORANGE);
    GPIO_ToggleOutputPin(GPIOD,LED_PIN_BLUE);
    GPIO_ToggleOutputPin(GPIOD,LED_PIN_GREEN);
    GPIO_ToggleOutputPin(GPIOD,LED_PIN_RED);
}



/**
 * @brief State Machine for the led system
 * 
 * @param State 
 * @param led_timer 
 */
void Led_State_Machine(uint8_t* State,uint8_t* led_timer){
    
    switch (*State)
    {
    // just change the state to ignintion
    case STATE_START:
        *State = STATE_IGNITION;
        break;
    
    case STATE_IGNITION:
        GPIO_ToggleOutputPin(GPIOD,LED_PIN_GREEN);
        delay(1000);
        *(led_timer)= *(led_timer) +1;
        if (*(led_timer) > 5){
            *State = STATE_IDLE;
            Reset_All_LED(); 
        }
        break;
    case STATE_NO_SEATBELT:
        delay(1000);
        Toggle_All_LED();
        break;

    case STATE_CRASH_SEATBELT:
        GPIO_ToggleOutputPin(GPIOD,LED_PIN_BLUE);
        delay(1000);
        break;

    case STATE_CRASH_NO_SEATBELT:
        
        GPIO_ToggleOutputPin(GPIOD,LED_PIN_RED);
        delay(1000);
        *(led_timer)= *(led_timer) +1;
        if (*(led_timer) > 15){
            *State = STATE_IDLE;
            Reset_All_LED(); 
        }
        break;
        
    case STATE_IDLE:
        // Empty state does nothing
        break;

    
    default:
        break;
    }
}
