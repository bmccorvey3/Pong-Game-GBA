//Brent McCorvey

#include "mylib.h"

u16 *videoBuffer = (u16*)0x6000000;

void setPixel(int r, int c, u16 color) {
	videoBuffer[WIDTH * r + c] = color;

}

void drawImage3 (int r, int c, int width, int height, const u16* image) {
	for (int i = 0; i < height; i++) {
		DMA[3].src = (image + (width * i));
		DMA[3].dst = videoBuffer + OFFSET(r+i,c,WIDTH);
		DMA[3].cnt = width | DMA_ON;
	}
}

void delay(int n) {
	volatile int x = 0; 
	for(int i = 0; i < n*10000; i++) {
		x++;
	}
}

void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void blackScreen(int r, int c) {
	DMA[3].src = RGB(0,0,0);
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = (r*c) | DMA_ON | DMA_DESTINATION_INCREMENT;
}


void drawRect(int r, int c, int width, int height, u16 color) {
	for(int i = 0; i< height; i++) {
		for(int j = 0; j<width; j++) {
			setPixel(r+i, c+j, color);
		}
	}
}

//FIX THIS STUFF
