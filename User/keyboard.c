#include "keyboard.h"

/*
 * Standard IBM-5170 1391401 keyboard layout:
 *
 * Esc F1 F2 F3 F4 F5 F6 F7 F8 F9 F10 F11 F12      SysRq ScLk Pause
 * ~  1  2  3  4  5  6  7  8  9  0  -  +  Bkspc     Ins  Home PgUp    NmLk /  *  -
 * Tab Q  W  E  R  T  Y  U  I  O  P  [  ]  \        Del  End  PgDn     7  8  9   
 * CpLk A  S  D  F  G  H  J  K  L  ;  "  Return  					   4  5  6   +
 * LShft Z  X  C  V  B  N  M  <  >  ?     RShft           Up		   1  2  3  
 * LCtrl   LAlt      Space    RAlt        RCtrl     Left Down Right    0     .   Return
 *
 */

const uint8_t ibm1391401_keycode[16][8] = 
{{ NULL        , NULL        , KEY_LCTRL   , NULL        , NULL        , NULL        , KEY_RCTRL   , NULL        }
,{ NULL        , KEY_LSHIFT  , NULL        , NULL        , NULL        , NULL        , KEY_RSHIFT  , NULL        }
,{ KEY_ESC     , KEY_TAB     , KEY_GRAVE   , KEY_1       , KEY_Q       , KEY_A       , KEY_Z       , NULL        }
,{ KEY_EURO    , KEY_CPSLCK  , KEY_F1      , KEY_2       , KEY_W       , KEY_S       , KEY_X       , NULL        }
,{ KEY_F4      , KEY_F3      , KEY_F2      , KEY_3       , KEY_E       , KEY_D       , KEY_C       , NULL        }
,{ KEY_G       , KEY_T       , KEY_5       , KEY_4       , KEY_R       , KEY_F       , KEY_V       , KEY_B       }
,{ KEY_F5      , KEY_BCKSPC  , KEY_F9      , KEY_F10     , NULL        , KEY_BCKSLSH , KEY_RETURN  , KEY_SPC     }
,{ KEY_H       , KEY_Y       , KEY_6       , KEY_7       , KEY_U       , KEY_J       , KEY_M       , KEY_N       }
,{ KEY_LALT    , NULL        , NULL        , KEY_PRTSCR  , KEY_SCRLCK  , NULL        , NULL        , KEY_RALT    }
,{ KEY_UARR    , NULL        , KEY_HOME1   , KEY_END1    , KEY_KPPLUS  , KEY_KPENTER5, KEY_PAUSE   , KEY_LARR    }
,{ KEY_KPDOT   , KEY_KP6     , KEY_PGUP    , KEY_PGDN    , KEY_KP9     , KEY_KP3     , KEY_KPAST   , KEY_KPMINUS }
,{ KEY_KP0     , KEY_KP5     , KEY_INS     , KEY_F12     , KEY_KP8     , KEY_KP2     , KEY_KPSLASH , KEY_RARR    }
,{ NULL        , KEY_KP4     , KEY_DEL     , KEY_F11     , KEY_KP7     , KEY_KP1     , KEY_KPNUM   , KEY_DARR    }
,{ /*KEY_PING,*/NULL, KEY_LBR     , KEY_MINUS   , KEY_0       , KEY_P       , KEY_SMCOL   , /*KEY_HASH,*/NULL, KEY_SLASH   }
,{ NULL        , KEY_F7      , KEY_F8      , KEY_9       , KEY_O       , KEY_L       , KEY_DOT     , NULL        }
,{ KEY_F6      , KEY_RBR     , KEY_EQUAL   , KEY_8       , KEY_I       , KEY_K       , KEY_COMMA   , NULL        }};


void keyboard_init(){
	GPIO_InitTypeDef GPIO_Serial_Output, GPIO_Parallel_Input;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	
	// Enable the clock signal in the port B and A.
	// Set up the serial output port and clock port and the MR port.
	// And 8 parallel pin for parallel input.
	
	GPIO_Parallel_Input.GPIO_Pin = OCT_PORT_A | OCT_PORT_B | OCT_PORT_C | OCT_PORT_D
								 | OCT_PORT_E | OCT_PORT_F | OCT_PORT_G | OCT_PORT_H;
	GPIO_Serial_Output.GPIO_Pin = SER_PORT | CLK_PORT | SR_ENABLE_BIT; 
	
	// Set these port enter their mode.
	
	GPIO_Parallel_Input.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Serial_Output.GPIO_Mode = GPIO_Mode_Out_PP;
	
	// Set the clock speed.
	
	GPIO_Parallel_Input.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Serial_Output.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Serial_Output);
	GPIO_Init(GPIOA, &GPIO_Parallel_Input);
	GPIO_ResetBits(GPIOB, SER_PORT | CLK_PORT | SR_ENABLE_BIT);
	GPIO_ResetBits(GPIOA, OCT_PORT_A | OCT_PORT_B | OCT_PORT_C | OCT_PORT_D
						| OCT_PORT_E | OCT_PORT_F | OCT_PORT_G | OCT_PORT_H);
}

void invoke_clock_tick(bool status){
	// Tick the clock to shift register.
	if (status)
		GPIO_SetBits(GPIOA, CLK_PORT);
	else
		GPIO_ResetBits(GPIOA, CLK_PORT);
}

void switch_sr_status(
	// Switch the SR status (by change the MR Pin status)
	_In_ bool status	// New status
){
	switch (status){
	case true:
		GPIO_SetBits(GPIOA, SR_ENABLE_BIT);
		break;
	case false:
		GPIO_ResetBits(GPIOA, SR_ENABLE_BIT);
	}
}	

void keyboard_scan(
	// Keyboard scanning procedure.
	_Out_ keyboard_input_form* form
	// keyboard_input_form: The input form of USB HID.
){
	uint16_t keydata;
	uint8_t counter = 0, counter1 = 0, counter2 = 0;
	switch_sr_status(true);	// Switch the SR ON!
	GPIO_SetBits(GPIOA, SER_PORT);	// Send a signal to 16-bit SR.
//	((uint8_t *)form)[0] = '\x00';
//	((uint8_t *)form)[1] = '\x00';
	ZeroMemory(form, 8);
	for (counter = 0; counter < 16; counter++){
		invoke_clock_tick(true);
		if (! counter) // counter == 0
			GPIO_ResetBits(GPIOA, SER_PORT);	// Close the signal kick in round zero.
		keydata = GPIO_ReadInputData(GPIOA);
		invoke_clock_tick(false);
		for (counter2 = 0; counter2 < 8; counter++){
			if (bitcmp(keydata, counter2)){
				switch (ibm1391401_keycode[counter][counter2]){
					case KEY_LCTRL:
						form->funcflag |= IF_LCTRL_PRESSED;
						break;
					case KEY_LSHIFT:
						form->funcflag |= IF_LSHIFT_PRESSED;
						break;
					case KEY_LALT:
						form->funcflag |= IF_LALT_PRESSED;
						break;
					case KEY_LGUI:
						form->funcflag |= IF_LGUI_PRESSED;
						// Will never come here, because IBM 1391401 did not have Winkey!
						break;
					case KEY_RCTRL:
						form->funcflag |= IF_RCTRL_PRESSED;
						break;
					case KEY_RSHIFT:
						form->funcflag |= IF_RSHIFT_PRESSED;
						break;
					case KEY_RALT:
						form->funcflag |= IF_RALT_PRESSED;
						break;
					case KEY_RGUI:
						form->funcflag |= IF_RGUI_PRESSED;
						break;
					default:
						(&((uint8_t *)form)[2])[counter1++] = ibm1391401_keycode[counter][counter2];
						break;
				}
			}
		}
		if (counter1 >= 6){
			break;
			// if pressed key was more than 6, I will not proceed more keypress events.
			// I did not like to do evil, but the fucking USB HID v1.11 protocol does.
		}
	}
//	for (; counter1 < 6; counter1++){
//		(&((uint8_t *)form)[2])[counter1] = '\x00';
//	}
	switch_sr_status(false);
	return;
}

void keyboard_sync_status(
	// Synchronize the keyboard status, and host's command.
	_In_ keyboard_output_form* form
	// keyboard_input_form: The output form of USB HID.
){
	if (bitcmp(form->funcflag, 0))
		// Num lock LED should be switch on.
		change_num_lock(true);
	else
		// Or switch off.
		change_num_lock(false);
	
	if (bitcmp(form->funcflag, 1))
		// Caps lock LED should be switch on.
		change_caps_lock(true);
	else
		// Or switch off.
		change_caps_lock(false);
		
	if (bitcmp(form->funcflag, 2))
		// Scroll lock LED should be switch on.
		change_scroll_lock(true);
	else
		// Or switch off.
		change_scroll_lock(false);
		
}
