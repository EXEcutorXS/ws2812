#ifndef WS2812
#define WS2812

#include "main.h"

typedef struct
{
uint8_t green;
uint8_t red;
uint8_t blue;
}color_t;

#define DELAY_LEN 200
#define LED_COUNT (MAX_NODES + 1)
#define ARRAY_LEN DELAY_LEN + LED_COUNT*24
#define HIGH 65
#define LOW 26

#define RED 0x10,0,0
#define GREEN 0,0x10,0
#define BLUE 0,0,0x010
#define YELLOW 0x10,0x10,0
#define CYAN 0,0x10,0x10
#define MAGENTA 0x10,0,0x10
#define WHITE 0x3,0x3,0x3
#define BLACK 0,0,0
#define ORANGE 0x20,0x10,0x0
#define PINK 0x20,0x0,0x10
#define LGREEN 0x0,0x20,0x10


void wsSetColor(uint8_t num, uint8_t red, uint8_t green, uint8_t blue);
void swInit(void);
void wsPrepareArray(void);
void wsInit(TIM_HandleTypeDef * tim, uint32_t chan);
uint32_t * getBitBanded(uint32_t * adr,uint8_t bit);
void wsShiftLed(color_t newColor);
void wsDoubleBright(uint8_t num);
void wsMultiply(uint8_t num, float k);
#endif
