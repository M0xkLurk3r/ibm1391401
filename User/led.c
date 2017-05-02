#include "led.h"

void change_num_lock(bool status){
	static bool current_status;
	if (current_status == status)
		return;
	if (current_status = status)
		// Change the lights to ON.
		GPIO_ResetBits(GPIOA, NUM_LOCK_LED);
	else
		GPIO_SetBits(GPIOA, NUM_LOCK_LED);
}

void change_caps_lock(bool status){
	static bool current_status;
	if (current_status == status)
		return;
	if (current_status = status)
		// Change the lights to ON.
		GPIO_ResetBits(GPIOB, CAPS_LOCK_LED);
	else
		GPIO_SetBits(GPIOB, CAPS_LOCK_LED);
}

void change_scroll_lock(bool status){
	static bool current_status;
	if (current_status == status)
		return;
	if (current_status = status)
		// Change the lights to ON.
		GPIO_ResetBits(GPIOB, SCOL_LOCK_LED);
	else
		GPIO_SetBits(GPIOB, SCOL_LOCK_LED);
}

void led_init(){
	// Must be call after keyboard_init() called!!!
	GPIO_InitTypeDef GPIO_LED_Output, GPIO_LED_Output1;
	GPIO_LED_Output.GPIO_Pin = SCOL_LOCK_LED | CAPS_LOCK_LED | LED_VCC;
	GPIO_LED_Output.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_LED_Output);
	GPIO_LED_Output1.GPIO_Pin = NUM_LOCK_LED;
	GPIO_LED_Output1.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_LED_Output1);
	// Make the LED lights on when devices boot for 10 ms.
	GPIO_SetBits(GPIOA, LED_VCC);
	GPIO_SetBits(GPIOB, NUM_LOCK_LED);
	GPIO_SetBits(GPIOA, SCOL_LOCK_LED);
	GPIO_SetBits(GPIOA, CAPS_LOCK_LED);
}