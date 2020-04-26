/******
Demo for ssd1306 i2c driver for  Raspberry Pi 
******/

#include "ssd1306_i2c.h"
#include <stdio.h>

void main() {
	ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);

	ssd1306_display(); //Adafruit logo is visible
	ssd1306_clearDisplay();
	delay(1000);

	//ssd1306_drawFastHLine(0, 0, 128, WHITE);
	// char* text = "This is demo for SSD1306 i2c driver for Raspberry Pi";
	//ssd1306_drawString(text);
	//ssd1306_display();
	//delay(2000);
	//ssd1306_clearDisplay();

	char* s1 = "fellas";
	char* s2 = "we finally did it";
	char* s3a = "after wayyy too";
	char* s3b = "many hours";
	char* s4a = "this retarded thing";
	char* s4b = "actually works";
	char* s5 = "i'm so happy :cry:";
	char* s6 = "luv u all";

	int y = 32; // halfway between top and bottom (64 pixels high)
	int vertOffset = 8; // 8 pixels will give nice looking spacing for multi-line text
	int msDelay = 2000; // delay in between changing display text

	// x value is determined by: 64 - ((# of chars / 2) * 6)
	// since 64 is the halfway point (128 pixels wide)
	// each char is 6 pixels wide (including spacing)
	// so the above formula gives us centered text for this tiny screen

	drawText(46, y, s1, 1);
	ssd1306_display();
	delay(msDelay);
	ssd1306_clearDisplay();

	drawText(16, y, s2, 1);
	ssd1306_display();
	delay(msDelay);
	ssd1306_clearDisplay();

	drawText(22, y, s3a, 1);
	drawText(34, y + vertOffset, s3b, 1);
	ssd1306_display();
	delay(msDelay);
	ssd1306_clearDisplay();

	drawText(10, y, s4a, 1);
	drawText(22, y + vertOffset, s4b, 1);
	ssd1306_display();
	delay(msDelay);
	ssd1306_clearDisplay();

	drawText(10, y, s5, 1);
	ssd1306_display();
	delay(msDelay);
	ssd1306_clearDisplay();

	drawText(40, y + 16, s6, 1);
	ssd1306_display();
	delay(msDelay);
	// ssd1306_clearDisplay();

	int xCoords[37] = {
		2, 3, 4, 5, 9, 10, 11, 12,
		1, 6, 8, 13,
		0, 2, 3, 7, 14,
		0, 2, 14,
		0, 14,
		0, 14,
		1, 13,
		2, 12,
		3, 11,
		4, 10,
		5, 9,
		6, 8,
		7
	};

	int yCoords[37] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1,
		2, 2, 2, 2, 2,
		3, 3, 3,
		4, 4,
		5, 5,
		6, 6,
		7, 7,
		8, 8,
		9, 9,
		10, 10,
		11, 11,
		12
	};

	int xCoords2[57] = {
		3, 4, 5, 6, 7, 15, 16, 17, 18, 19,
		2, 8, 14, 20,
		1, 9, 13, 21,
		0, 3, 4, 10, 12, 22,
		0, 3, 11, 22,
		0, 22,
		0, 22,
		0, 22,
		1, 21,
		1, 21,
		2, 20,
		3, 19,
		4, 18,
		5, 17,
		6, 16,
		7, 15,
		8, 14,
		9, 13,
		10, 12,
		11
	};

	int yCoords2[57] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1,
		2, 2, 2, 2,
		3, 3, 3, 3, 3, 3,
		4, 4, 4, 4,
		5, 5,
		6, 6,
		7, 7,
		8, 8,
		9, 9,
		10, 10,
		11, 11,
		12, 12,
		13, 13,
		14, 14,
		15, 15,
		16, 16,
		17, 17,
		18, 18,
		19
	};

	drawArt(xCoords2, yCoords2);
	ssd1306_display();
	delay(msDelay);
	ssd1306_clearDisplay();

	//ssd1306_drawChar(0, 32, c, WHITE, 1);
	//ssd1306_dim(1);
	//ssd1306_startscrollright(00,0xFF);
	ssd1306_startscrollright(00, 0xFF);
	//ssd1306_fillRect(10,10, 50, 20, WHITE);
	//ssd1306_fillRect(80, 10, 130, 50, WHITE);
	//ssd1306_display();

	delay(10000);
	ssd1306_clearDisplay();
	ssd1306_display();

	return;
}

void drawText(int x, int y, char* s, int size) {
	char* c = s;

	for (c = s; *c != '\0'; c++) {
		ssd1306_drawChar(x, y, *c, WHITE, size);
		x += 6;
	}

	return;
}

void drawArt(int xCoords[], int yCoords[]) {
	int n = 57;
	int vertOffset = 20;
	int horizOffset = 53;
	int recentY = yCoords[0];

	for (int i = 0; i < n; i++) {
		ssd1306_drawPixel(xCoords[i] + horizOffset, yCoords[i] + vertOffset, WHITE);

		if (recentY != yCoords[i]) {
			ssd1306_display();
			delay(25);
			recentY = yCoords[i];
		}
	}

	return;
}
