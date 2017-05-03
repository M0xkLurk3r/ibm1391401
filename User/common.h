#ifndef COMMON_H
#define COMMON_H

// #include <stdbool.h>
#include <string.h>
#include "stm32f10x.h"
// #include <stdio.h>

#define _In_
#define _Out_

#define bool uint8_t
#define true 1
#define false 0

// bool bitcmp(__var__ a, uint8_t b), get the bits b at variable a,
// and return the bit as BOOLEAN value.
#define bitcmp(a, b)  (((a) >> (b)) & 1)

// A Microsoft-style bzero()
#define ZeroMemory(a, b) memset((a), 0x00, (b))

void Delay(uint32_t dlyTicks);

// System initialize function
void delay_us(unsigned int us);
void delay_ms(unsigned int ms);
//void RCC_DeInit(void);
void StSystemClockInit(void);

// For the fucking ARMCC compiler.


#endif // COMMON_H