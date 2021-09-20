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
#include "stm32f407xx.h"
#include "led.h"

volatile uint8_t Interrupt_flag = RESET;
volatile uint8_t Interrupt_count = 0;

int main(void)
{ 
	/*
	* Store the state of the system to take care of timing of states
	* Button handler
	*/
	
	uint8_t State = STATE_START;		
	uint8_t led_timer = 0;			
	GPIO_Handle_t GPIOBtn;				
    GPIO_Handle_t GpioLedRed;   
    GPIO_Handle_t GpioLedGreen;  
    GPIO_Handle_t GpioLedBlue;   
    GPIO_Handle_t GpioLedOrange;

	//*Initialize all leds*/
	GPIO_Led_Initialize(&GpioLedRed,LED_PIN_RED);
	GPIO_Led_Initialize(&GpioLedGreen,LED_PIN_GREEN);
	GPIO_Led_Initialize(&GpioLedBlue,LED_PIN_BLUE);
	GPIO_Led_Initialize(&GpioLedOrange,LED_PIN_ORANGE);
	GPIO_PeriClockControl(GPIOD,ENABLE);

	/*Initilize the GPIOs*/
	GPIO_Init(&GpioLedRed);
	GPIO_Init(&GpioLedGreen);
	GPIO_Init(&GpioLedBlue);
	GPIO_Init(&GpioLedOrange);

	/*Configure the Button*/
	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(GPIOA,ENABLE);

	GPIO_Init(&GPIOBtn);

	// GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_12,GPIO_PIN_RESET);
	//IRQ configurations
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI0,NVIC_IRQ_PRI0);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI0,ENABLE);


    while(1){
		Led_State_Machine(&State ,&led_timer);
		if (Interrupt_flag == SET && Interrupt_count == 0){
			led_timer = 0;
			State = STATE_NO_SEATBELT;
			Reset_All_LED();

			
		}
		if (Interrupt_flag == SET && Interrupt_count == 1)
		{
			led_timer = 0;
			State = STATE_CRASH_NO_SEATBELT;
			Reset_All_LED();

		}
		if (Interrupt_flag == SET && Interrupt_count == 2)
		{
			led_timer = 0;
			State = STATE_CRASH_SEATBELT;
			Reset_All_LED();
		}
		Interrupt_flag =RESET;
		Interrupt_count =RESET;
	}

}


void EXTI0_IRQHandler(void)
{
   delay(50); //200ms . wait till button de-bouncing gets over
	GPIO_IRQHandling(GPIO_PIN_NO_0); //clear the pending event from exti line
	if (Interrupt_flag == SET){
		Interrupt_count = Interrupt_count + 1;
	}
	Interrupt_flag = SET;
}