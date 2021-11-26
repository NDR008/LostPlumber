/*
 * basics.h
 *
 *  Created on: Dec 19, 2020
 *      Author: NDR008
 *		Strong based on work of: 
 *      Author: Wituz
 * 		fixed the include crap
 */

#pragma once

#include <sys/types.h>
#include <libgpu.h>
#include <libgs.h>

#define TYPE_LINE 0
#define TYPE_BOX 1

#define SCREEN_MODE_PAL 0
#define SCREEN_MODE_NTSC 1

extern int SCREEN_WIDTH, SCREEN_HEIGHT;

typedef struct Color {
	int r;
	int g;
	int b;
} Color;

typedef struct Line {
	LINE_F2 line;
	int type;
} Line;

typedef struct Box {
	Line line[4];
	int type;
} Box;

typedef struct {
	RECT rect;
	RECT crect;
	GsIMAGE tim_data;
	GsSPRITE sprite;
} Image;

Image createImage(unsigned char imageData[]);
Image moveImage(Image image, int x, int y);
void drawImage(Image image);
Image scaleImage(Image img, int xScale, int yScale);
Image rotImage(Image img, int rotation);

Color createColor(int r, int g, int b);
Line createLine(Color color, int x1, int y1, int x2, int y2);
Box createBox(Color color, int x1, int y1, int x2, int y2);
Line moveLine(Line line, int x1, int y1, int x2, int y2);
Box moveBox(Box box, int x1, int y1);
Box transposeBox(Box box, int x1, int y1);
void drawLine(Line line);
void drawBox(Box box);
void drawImage(Image image);
void setScreenMode(int mode);
void setBackgroundColor(Color color);
void initializeScreen();
void initializeDebugFont();
void initializeOrderingTable();
void flushDisplay();
void clearDisplay();
void clearVRAM();