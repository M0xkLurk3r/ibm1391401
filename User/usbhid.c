#include "usbhid.h"
#include "common.h"

void StUSBSetupIntterupts(){
	// Setup ST-USB Interrupts.
	NVIC_InitTypeDef USBNVIC;
	USBNVIC.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn; // give it low priority.
	USBNVIC.NVIC_IRQChannelPreemptionPriority = 0;
	USBNVIC.NVIC_IRQChannelSubPriority = 0;
	USBNVIC.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&USBNVIC);
}

void USBHID_init(){
/*
	GPIO_InitTypeDef GPIO_USBD;
	GPIO_USBD.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_USBD.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_USBD.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_USBD);
*/
	// Set up USB Clock to 48MHz(USB 2.0 High-speed defaults to 480Mbps)
	// 1Div5 means 72 / 1.5 == 48
	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
	StUSBSetupIntterupts();		// SET up USB Interrupts.
	// Initialize USB by calling RTE
//	USBD_Initialize(0);
//	USBD_Connect(0);ADC1
	USBD_HID0_Initialize();
}