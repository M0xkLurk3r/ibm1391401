#ifndef LED_H
#define LED_H

#include "stm32f10x.h"
#include "common.h"

#define NUM_LOCK_LED GPIO_Pin_10
#define CAPS_LOCK_LED GPIO_Pin_8
#define SCOL_LOCK_LED GPIO_Pin_10
#define LED_VCC	GPIO_Pin_9

void change_num_lock(bool status);
void change_caps_lock(bool status);
void change_scroll_lock(bool status);

void system_led(bool status);

void led_init();

#endif // LED_H