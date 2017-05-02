#include "usbhid.h"
#include "common.h"

void USBHID_init(){
	USBD_Initialize(0);
	USBD_Connect(0);
}