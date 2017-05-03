#ifndef USBHID_H
#define USBHID_H

#include "stm32f10x.h"
#include "common.h"
#include "rl_usb.h"
#include "usb_hid.h"

/*
 * According to USB HID v1.1 Documentation, the communication between
 * USB Host and the HID Device actualized via packet "Input-Output Form".
 *
 * The packet of that form defines below:
 *
 * Input form:						Mod-key func:
 * |----------------------------|	|----------------------------|
 * | Offset |  implication      |	| Offset |  implication      |
 * |----------------------------|	|----------------------------|
 * |   0    |  Mod-key func.    |	| >> 0   |  LEFT_CTRL		 |
 * |----------------------------|	|----------------------------|
 * |   1    |  reserved(0x00)   |	| >> 1	 |	LEFT_SHIFT		 |
 * |----------------------------|	|----------------------------|
 * |   2    |  keycode1         |	| >> 2   |  LEFT_ALT		 |
 * |----------------------------|	|----------------------------|
 * |   3    |  keycode2         |	| >> 3   |  LEFT_GUI         |
 * |----------------------------|	|----------------------------|
 * |   4    |  keycode3         |	| >> 4   |  RIGHT_CTRL       |
 * |----------------------------|	|----------------------------|
 * |   5    |  keycode4         |	| >> 5   |  RIGHT_SHIFT      |
 * |----------------------------|	|----------------------------|
 * |   6    |  keycode5         |	| >> 6   |  RIGHT_ALT        |
 * |----------------------------|	|----------------------------|
 * |   7    |  keycode6         |	| >> 7   |  RIGHT_GUI        |
 * |----------------------------|	|----------------------------|
 *
 * Input form:						HID_Answer:
 * |----------------------------|	|----------------------------|
 * | Offset |  implication      |	| Offset |  implication      |
 * |----------------------------|	|----------------------------|
 * |   0    |  HID_Answer       |	| >> 0   |  NUM_LOCK_LED	 |
 * |----------------------------|	|----------------------------|
 * |        |                   |	| >> 1	 |	CAPS_LOCK_LED	 |
 * |----------------------------|	|----------------------------|
 * |        |                   |	| >> 2   |  SCROLL_LOCK_LED	 |
 * |----------------------------|	|----------------------------|
 * |        |                   |	| >> 3   |  COMPOSE_LED      |
 * |----------------------------|	|----------------------------|
 * |        |                   |	| >> 4   |  KANA_LED         |
 * |----------------------------|	|----------------------------|
 * |        |                   |	| >> 5   |  reserved         |
 * |----------------------------|	|----------------------------|
 * |        |                   |	| >> 6   |  reserved         |
 * |----------------------------|	|----------------------------|
 * |        |                   |	| >> 7   |  reserved         |
 * |----------------------------|	|----------------------------|
 *
 */

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