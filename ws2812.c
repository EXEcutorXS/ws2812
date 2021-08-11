#include "ws2812.h"
extern TIM_HandleTypeDef htim2;

uint16_t wsBuffer[ARRAY_LEN];
color_t cBuffer[LED_COUNT];

void wsSetColor(uint8_t num, uint8_t red, uint8_t green, uint8_t blue)
{
cBuffer[num].red=red;
cBuffer[num].green=green;
cBuffer[num].blue=blue;
}

void wsDoubleBright(uint8_t num)
{
	cBuffer[num].red*=2;
	cBuffer[num].green*=2;
	cBuffer[num].blue*=2;
}

void wsMultiply(uint8_t num, float k)
{
	cBuffer[num].red*=k;
	cBuffer[num].green*=k;
	cBuffer[num].blue*=k;
}

void swInit(void)
{
int i;
for(i=0;i<ARRAY_LEN;i++)
	wsBuffer[i]=0;
}

void wsPrepareArray()
{
	uint16_t i=0;
	int16_t j=0;
	uint32_t * adr=getBitBanded((uint32_t*)cBuffer, 0);

	for(i=0;i<LED_COUNT*3;i++)
	for(j=7;j>=0;j--)
		if (*adr++)
      wsBuffer[i*8+j]=65;
		else
	  wsBuffer[i*8+j]=26;
}

void wsInit(TIM_HandleTypeDef * tim, uint32_t chan)
{
	HAL_TIM_PWM_Start_DMA(tim, chan, (uint32_t*)wsBuffer, ARRAY_LEN);
}

uint32_t * getBitBanded(uint32_t * adr,uint8_t bit)
{
return (uint32_t*)(((((uint32_t)adr)&0xFFFF))*32+bit*4+0x22000000);
}

void wsShiftLed(color_t newColor)
{
	uint8_t i;

	for(i=LED_COUNT;i>0;i--)
		cBuffer[i]=cBuffer[i-1];
	cBuffer[0]=newColor;
	wsPrepareArray();
}
