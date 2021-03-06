#include "led.h"
#include "usbhid.h"
#include "keyboard.h"
#include "common.h"

/*
 *  Copyright (C) NSS TEAM, All rights reserved.
 *           ..
 *         .#.
 *       .##.
 *      ###.    ###                                   ..              ..
 *    .###.    #####.         .#####     ####     .#########.    ..#########
 *   ####.     #######        .######    ####   .#####...####   #####...####
 *  #####    ####  ####.      .#######   ####   ####       ..  .####       .
 * ######.   ###.   .####.    .###.####  ####   ######..       .#####..
 *   .####.   .###     ####.  .### .#### ####    ##########.    .#########.
 *     .####   ###.   .####.  .###  .########      .#########     .#########.
 *       ########     ####.   .###   .#######           .####.         .#####
 *        .#####     ####     .###    .######   ##.      ####  .#.      .###.
 *          ###     ###.      .###     .#####   ############.  .############
 *                 ##.        .###      .###.   ..########.     ..#######.
 *               .#.
 *             .           
 *	NSS(Neusoft Network Security Studio) was a student team 
 *	of Dalian Neusoft University of Information, 
 *	aimed to network security research, and GEEK(gay) discover.
 *
 *  Author: Anthony Lee (lkphantom1995@gmail.com)
 *
 *	About ibm1391401:
 *  A Compatible controller for IBM 5170 keyboard Model M 1391401,
 *	based on STM32F103C8T6 Microcontroller.
 *
 */
 
 void led_blink(void){
	// Blink the LED (give status for showing the system was not piao)
	while (1){
		system_led(true);
		delay_ms(200);
		system_led(false);
		delay_ms(200);
		system_led(true);
		delay_ms(80);
		system_led(false);
		delay_ms(80);
		system_led(true);
		delay_ms(80);
		system_led(false);
		delay_ms(200);
	}
}

 int main(){
	// TODO: Code here.
	keyboard_input_form input_form;
	keyboard_output_form output_form;
	osThreadId thread_ledblink;
	StSystemClockInit();	// Start up the OS, and system clock.
	//SystemCoreClockUpdate();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	// Enable the clock signal in the port B and A.
	keyboard_init();
	led_init();
	osThreadDef_t detectpiao = {
		.pthread = led_blink,
		.tpriority = osPriorityNormal,
		.instances = 1,
		.stacksize = 0
	};
	thread_ledblink = osThreadCreate((const osThreadDef_t*)&detectpiao, NULL);
	USBHID_init();
	delay_ms(1000);
	osThreadTerminate(thread_ledblink);
	while (1){
		output_form.funcflag = 0;
		if (USBD_HID0_GetReport(HID_REPORT_OUTPUT, USBD_HID_REQ_EP_CTRL, 0, (uint8_t *)&output_form) == -1)
			continue;
		// Keyboard scan code here.
		keyboard_scan(&(input_form));
		keyboard_sync_status(&output_form);
		
		if (! USBD_HID0_SetReport(HID_REPORT_INPUT, USBD_HID_REQ_EP_CTRL, 0, (uint8_t *)(&input_form), 8))
			continue;
	}
	return 1;
}