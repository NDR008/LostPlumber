
// main.c Lost Plumber v0.1 for Lost Cartridge Jam 2021
/*
MIT License
Copyright (c) 2021 NDR008
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <sys/types.h>
#include <libetc.h>
#include <stdlib.h>
#include <stdio.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libspu.h>
#include "engine/graphics.h"
#include "engine/input.h"
#include "engine/timerz.h"
#include "engine/audio.h"
#include "graphics/images.h"

#define factor 1024     
#define GRAVITY factor / 4
#define SPRITEHEIGHT 16
#define GROUND (SCREEN_HEIGHT- 5*16 - SPRITEHEIGHT) * factor

// each row represents the bottom 5 rows


// Global timer
PSXTimer mainTimer;

typedef struct AnimatedObject{
    int frame_n;            // this is the current frame
    int index;
    int total_frames;       // this is the total frame
    int y_pos;
    int x_pos;
    int x_vel;
    int y_vel;
    int anim_rate;
    Image *img_list;   // make this a list of Image (ok)
} AnimatedObject;

typedef struct World{
    int x_offset;
    int y_pos;
    int x_pos;
    int x_vel;
    int y_vel;
    Image *img_list;   // make this a list of Image (ok)
} World;

World ground;
Image groundL[1];

#define rows 5
#define cols 20
#define cols_max 20 //max number of visible cols
int groundWorld[rows][cols] ={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1}    
};

void initGame(void);
void initObjects(void);
void animate(AnimatedObject *animatedObj);
void drawWorld(void);

void initGame(void){
	initializeScreen();
    initializeDebugFont();
    setBackgroundColor(createColor(0, 0, 0));
    audioInit();
    inputInit();  // init inputs
	initializeDebugFont();
    initObjects();
}

void initObjects(void){
    ground.x_offset = 0;
    ground.y_pos = GROUND;
    ground.x_pos = 50 * factor;
    ground.y_vel = 0;
    ground.x_vel = 0;
    groundL[0] = createImage(img_ground);
    ground.img_list = groundL;
}

void animate(AnimatedObject *animatedObj){
    Image toDraw;
    if (animatedObj->anim_rate != 0) {
        if (mainTimer.vsync % animatedObj->anim_rate == 0) {
            animatedObj->frame_n++;
            animatedObj->index = animatedObj->frame_n % animatedObj->total_frames;
        }
    }
    toDraw = moveImage(animatedObj->img_list[animatedObj->index], animatedObj->x_pos / factor, animatedObj->y_pos / factor);
    drawImage(toDraw);
}

void drawWorld(void){
    Image tmpImage;
    for (int r=0; r < rows; r++){
        for (int c = 0; c < cols_max; c++){
            if (groundWorld[r][c]==1){
                tmpImage = moveImage(ground.img_list[0], 0+c*16, (16*8)+r*16);
                drawImage(tmpImage);
            }
        }
    }
}

int main() {
    initGame();
    printf("Lost Plumber v0.1\n");
    mainTimer = createTimer();
    while(1){
        clearDisplay();
        drawWorld();
        flushDisplay();
        mainTimer = incTimer(mainTimer);
    }
}