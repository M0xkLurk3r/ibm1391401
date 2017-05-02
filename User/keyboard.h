#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "stm32f10x.h"
#include "usbhid.h"
#include "common.h"
#include "led.h"


// Define the GPIO Port for keyboard logic scanning procedure.
#define OCT_PORT_A GPIO_Pin_0
#define OCT_PORT_B GPIO_Pin_1
#define OCT_PORT_C GPIO_Pin_2
#define OCT_PORT_D GPIO_Pin_3
#define OCT_PORT_E GPIO_Pin_4
#define OCT_PORT_F GPIO_Pin_5
#define OCT_PORT_G GPIO_Pin_6
#define OCT_PORT_H GPIO_Pin_7

#define SER_PORT GPIO_Pin_8
#define CLK_PORT GPIO_Pin_9
#define SR_ENABLE_BIT GPIO_Pin_7

//#define NULL 0

// About the input form's FuncFlag.
#define IF_LCTRL_PRESSED	0x1
#define IF_LSHIFT_PRESSED	0x2
#define IF_LALT_PRESSED		0x4
#define IF_LGUI_PRESSED		0x8
#define IF_RCTRL_PRESSED	0x10
#define IF_RSHIFT_PRESSED	0x20
#define IF_RALT_PRESSED		0x40
#define IF_RGUI_PRESSED		0x80

void keyboard_scan(keyboard_input_form* form);
void keyboard_status_update(bool update, hid_data* data);

#define	NULL	0x00
#define	KEY_ERRORROLLOVER9	0x01
#define	KEY_POSTFAIL9	0x02
#define	KEY_ERRORUNDEFINED9	0x03
#define	KEY_A	0x04
#define	KEY_B	0x05
#define	KEY_C	0x06
#define	KEY_D	0x07
#define	KEY_E	0x08
#define	KEY_F	0x09
#define	KEY_G	0x0A
#define	KEY_H	0x0B
#define	KEY_I	0x0C
#define	KEY_J	0x0D
#define	KEY_K	0x0E
#define	KEY_L	0x0F
#define	KEY_M	0x10
#define	KEY_N	0x11
#define	KEY_O	0x12
#define	KEY_P	0x13
#define	KEY_Q	0x14
#define	KEY_R	0x15
#define	KEY_S	0x16
#define	KEY_T	0x17
#define	KEY_U	0x18
#define	KEY_V	0x19
#define	KEY_W	0x1A
#define	KEY_X	0x1B
#define	KEY_Y	0x1C
#define	KEY_Z	0x1D
#define	KEY_1	0x1E
#define	KEY_2	0x1F
#define	KEY_3	0x20
#define	KEY_4	0x21
#define	KEY_5	0x22
#define	KEY_6	0x23
#define	KEY_7	0x24
#define	KEY_8	0x25
#define	KEY_9	0x26
#define	KEY_0	0x27
#define	KEY_RETURN	0x28
#define	KEY_ESC	0x29
#define	KEY_BCKSPC	0x2A
#define	KEY_TAB	0x2B
#define	KEY_SPC	0x2C
#define	KEY_MINUS	0x2D
#define	KEY_EQUAL	0x2E
#define	KEY_LBR	0x2F // key '[' named 'left bracket'
#define	KEY_RBR	0x30 // key ']' named 'right bracket'
#define	KEY_BCKSLSH	0x31 // key '\' named "backslash"
#define	KEY_NON-US	0x32
#define	KEY_SMCOL	0x33
#define	KEY_	0x34
#define	KEY_GRAVE	0x35
#define	KEY_COMMA	0x36
#define	KEY_DOT	0x37
#define	KEY_SLASH	0x38 // key '/' named "slash"
#define	KEY_CPSLCK	0x39
#define	KEY_F1	0x3A
#define	KEY_F2	0x3B
#define	KEY_F3	0x3C
#define	KEY_F4	0x3D
#define	KEY_F5	0x3E
#define	KEY_F6	0x3F
#define	KEY_F7	0x40
#define	KEY_F8	0x41
#define	KEY_F9	0x42
#define	KEY_F10	0x43
#define	KEY_F11	0x44
#define	KEY_F12	0x45
#define	KEY_PRTSCR	0x46
#define	KEY_SCRLCK	0x47
#define	KEY_PAUSE	0x48
#define	KEY_INS		0x49
#define	KEY_HOME1	0x4A
#define	KEY_PGUP	0x4B
#define	KEY_DEL		0x4C
#define	KEY_END1	0x4D
#define	KEY_PGDN	0x4E
#define	KEY_RARR	0x4F
#define	KEY_LARR	0x50
#define	KEY_DARR	0x51
#define	KEY_UARR	0x52
#define	KEY_KPNUM	0x53
#define	KEY_KPSLASH	0x54
#define	KEY_KPAST	0x55 // Key '*' named 'asterisk'
#define	KEY_KPMINUS	0x56
#define	KEY_KPPLUS	0x57
#define	KEY_KPENTER5	0x58
#define	KEY_KP1	0x59
#define	KEY_KP2	0x5A
#define	KEY_KP3	0x5B
#define	KEY_KP4	0x5C
#define	KEY_KP5	0x5D
#define	KEY_KP6	0x5E
#define	KEY_KP7	0x5F
#define	KEY_KP8	0x60
#define	KEY_KP9	0x61
#define	KEY_KP0	0x62
#define	KEY_KPDOT	0x63
#define	KEY_EURO	0x64
#define	KEY_APPLICATION10	0x65
#define	KEY_POWER9	0x66
#define	KEY_KP=	0x67
#define	KEY_F13	0x68
#define	KEY_F14	0x69
#define	KEY_F15	0x6A
#define	KEY_F16	0x6B
#define	KEY_F17	0x6C
#define	KEY_F18	0x6D
#define	KEY_F19	0x6E
#define	KEY_F20	0x6F
#define	KEY_F21	0x70
#define	KEY_F22	0x71
#define	KEY_F23	0x72
#define	KEY_F24	0x73
#define	KEY_EXECUTE	0x74
#define	KEY_HELP	0x75
#define	KEY_MENU	0x76
#define	KEY_SELECT	0x77
#define	KEY_STOP	0x78
#define	KEY_AGAIN	0x79
#define	KEY_UNDO	0x7A
#define	KEY_CUT	0x7B
#define	KEY_COPY	0x7C
#define	KEY_PASTE	0x7D
#define	KEY_FIND	0x7E
#define	KEY_MUTE	0x7F
#define	KEY_VOLUP	0x80
#define	KEY_VOLDN	0x81
#define	KEY_LOCKING	0x82
//#define	KEY_LOCKING	0x83
//#define	KEY_LOCKING	0x84
#define	KEY_KPCOMMA27	0x85
#define	KEY_KPEQUAL	0x86
#define	KEY_INTERNATIONAL115	0x87
#define	KEY_INTERNATIONAL216	0x88
#define	KEY_INTERNATIONAL317	0x89
#define	KEY_INTERNATIONAL418	0x8A
#define	KEY_INTERNATIONAL519	0x8B
#define	KEY_INTERNATIONAL620	0x8C
#define	KEY_INTERNATIONAL721	0x8D
#define	KEY_INTERNATIONAL822	0x8E
#define	KEY_INTERNATIONAL922	0x8F
#define	KEY_LANG125	0x90
#define	KEY_LANG226	0x91
#define	KEY_LANG330	0x92
#define	KEY_LANG431	0x93
#define	KEY_LANG532	0x94
#define	KEY_LANG68	0x95
#define	KEY_LANG78	0x96
#define	KEY_LANG88	0x97
#define	KEY_LANG98	0x98
#define	KEY_ALTERNATE	0x99
#define	KEY_SYSREQ/ATTENTION1	0x9A
#define	KEY_CANCEL	0x9B
#define	KEY_CLEAR	0x9C
#define	KEY_PRIOR	0x9D
#define	KEY_RETURN	0x9E
#define	KEY_SEPARATOR	0x9F
#define	KEY_OUT	0xA0
#define	KEY_OPER	0xA1
#define	KEY_CLEAR/AGAIN	0xA2
#define	KEY_CRSEL/PROPS	0xA3
#define	KEY_EXSEL	0xA4
#define	KEY_KP00	0xB0
#define	KEY_KP000	0xB1
#define	KEY_SEPARATOR	0xB2
#define	KEY_SEPARATOR	0xB3
#define	KEY_UNIT	0xB4
#define	KEY_SUB-UNIT	0xB5
#define	KEY_KPLQ	0xB6  // keypad (
#define	KEY_KPRQ	0xB7  // keypad )
#define	KEY_KPLBR	0xB8
#define	KEY_KPRBR	0xB9
#define	KEY_KPTAB	0xBA
#define	KEY_KPBACKSPACE	0xBB
#define	KEY_KPA	0xBC
#define	KEY_KPB	0xBD
#define	KEY_KPC	0xBE
#define	KEY_KPD	0xBF
#define	KEY_KPE	0xC0
#define	KEY_KPF	0xC1
#define	KEY_KPXOR	0xC2
#define	KEY_KP^	0xC3
#define	KEY_KP%	0xC4
#define	KEY_KP<	0xC5
#define	KEY_KP>	0xC6
#define	KEY_KP&	0xC7
#define	KEY_KP&&	0xC8
#define	KEY_KP|	0xC9
#define	KEY_KP||	0xCA
#define	KEY_KP:	0xCB
#define	KEY_KP#	0xCC
#define	KEY_KPSPACE	0xCD
#define	KEY_KP@	0xCE
#define	KEY_KP!	0xCF
#define	KEY_KPMEMORY	0xD0
#define	KEY_KPMEMORY	0xD1
#define	KEY_KPMEMORY	0xD2
#define	KEY_KPMEMORY	0xD3
#define	KEY_KPMEMORY	0xD4
#define	KEY_KPMEMORY	0xD5
#define	KEY_KPMEMORY	0xD6
#define	KEY_KPVOL	0xD7 // KEY +/- 
#define	KEY_KPCLEAR	0xD8
#define	KEY_KPCLEAR	0xD9
#define	KEY_KPBINARY	0xDA
#define	KEY_KPOCTAL	0xDB
#define	KEY_KPDECIMAL	0xDC
#define	KEY_KPHEXADECIMAL	0xDD
#define	KEY_LCTRL	0xE0
#define	KEY_LSHIFT	0xE1
#define	KEY_LALT	0xE2
#define	KEY_LGUI	0xE3
#define	KEY_RCTRL	0xE4
#define	KEY_RSHIFT	0xE5
#define	KEY_RALT	0xE6
#define	KEY_RGUI	0xE7


void keyboard_init();

#endif // KEYBOARD_H