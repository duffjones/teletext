#include<stdio.h>
#include "telet.h"

void drawSmallSixel(SDL_Simplewin *sw, cell *hex, int i, int j,  int ox, int oy);
void setSixels(unsigned char code, sixels *sixel);
void DrawSixel(SDL_Simplewin *sw, cell *hex, int h, int w,  sixels sixel);
