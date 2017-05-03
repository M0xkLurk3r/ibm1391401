#include "common.h"

#define SYS_CLK 72/8 //System clock == 72M

void delay_us(
	// Delay for a bit time(us).
	unsigned int us // delay time(us)
){
	uint8_t n;		    
	while (us--) 
		for (n = 0; n < SYS_CLK; n++); 	 
}

void delay_ms(
	// Delay for a bit time(ms)
	uint32_t ms // delay time(ms)
){
	while (ms--)
		delay_us(1000);	 
}


void RCC_DeInit2(void){									   
	RCC->APB2RSTR = 0x00000000;// Reset the peripheral device			 
	RCC->APB1RSTR = 0x00000000;   	  
  	RCC->AHBENR = 0x00000014;  // enable the flash clock, and shut down the DMA clock	  
  	RCC->APB2ENR = 0x00000000; // disable the peripheral device clock.			   
  	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     // enable the internal HSION	high-speed clock
	RCC->CFGR &= 0xF8FF0000;   // RESET SW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     // RESET HSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     // RESET HSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //RESET PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
	RCC->CIR = 0x00000000;     //Close all interrupts!
}


void StSystemClockInit(void){
	// Initialize SYSTEM CLOCK
	// Got 72M system internal clock.
	uint8_t temp=0;
	uint8_t timeout=0;
	RCC_DeInit2();
	RCC_DeInit();
	RCC->CR |= 0x00010000;  // enable HSEON

	timeout = 0;
	while(! (RCC->CR >> 17) && timeout < 200)
		timeout++;// await PERIPHERAL clock READY!	 

	//0-24M 等待0;24-48M 等待1;48-72M等待2;(非常重要!)	   
	FLASH->ACR |= 0x32; //FLASH 2个延时周期

	RCC->CFGR |= 0X001D2400;//APB1/2=DIV2;AHB=DIV1;PLL=9*CLK;HSE作为PLL时钟源
	RCC->CR |= 0x01000000;  //PLLON

	timeout = 0;
	while(!(RCC->CR >> 25) && timeout < 200)
		timeout++;// Await PLL got lock

	RCC->CFGR |= 0x00000002;// Use PLL for system lock
	while(temp!=0x02&&timeout<200){     //Await it sets ready.   
		temp = RCC->CFGR >> 2;
		timeout++;
		temp &= 0x03;
	}  
}

