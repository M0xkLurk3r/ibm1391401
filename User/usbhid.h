#ifndef USBHID_H
#define USBHID_H

#include "stm32f10x.h"
#include "common.h"
#include "rl_usb.h"
#include "usb_hid.h"

typedef struct _keyboard_input_form {
	uint8_t funcflag;
	uint8_t reserved;	// Always been 0x00
	uint8_t keycode1;
	uint8_t keycode2;
	uint8_t keycode3;
	uint8_t keycode4;
	uint8_t keycode5;
	uint8_t keycode6;
}keyboard_input_form;

typedef struct _keyboard_output_form {
	uint8_t funcflag;
}keyboard_output_form;

typedef struct _hid_data {
	keyboard_input_form input_form;
	keyboard_output_form output_form;
}hid_data;

void USBHID_init();

#endif // USBHID_H