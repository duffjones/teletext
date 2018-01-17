#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "neillsdl2.h"

#define MILLISECONDDELAY 20
#define BLANK 0xA0
#define CELLCOUNT 1000

#define  TL sixel->uleft=true ;
#define  TR sixel->uright = true;
#define  ML sixel->mleft= true ;
#define  MR sixel->mright= true;
#define  BL sixel->bleft= true;
#define  BR sixel->bright= true;

typedef enum boolean {
  f   = 0,
  t   = 1
}boolean;

typedef struct sixels {
  boolean uleft;
  boolean uright;
  boolean mleft;
  boolean mright;
  boolean bleft;
  boolean bright;
} sixels;

typedef enum color {
  white = 6, black = 9, red = 3, yellow = 1, blue =2, cyan = 5, magenta = 4, green = 7
} color;

typedef enum fontsz {
  normalfont = 1, topfont = 2, bottomfont = 3
} fontsz;

typedef enum graphicsMode {
  alphanumeric, contiguous, separate
} graphicsMode;

typedef enum holdMode {
  release, hold
} holdMode;


typedef struct flags {
  color     frontcolor;
  color     backcolor;
  fontsz    fontsize;
  graphicsMode mode;
  holdMode hold;
} flags;


typedef struct cell {
  flags flag;
  unsigned char code;
} cell;


typedef enum colorCode {
  redf       = 0x81,
  greenf     = 0x82,
  yellowf    = 0x83,
  bluef      = 0x84,
  magentaf   = 0x85,
  cyanf      = 0x86,
  whitef     = 0x87,

  singleheight  = 0x8c,
  doubleheight  = 0x8d,

  redg     = 0x91,
  greeng   = 0x92,
  yellowg  = 0x93,
  blueg    = 0x94,
  magentag = 0x95,
  cyang    = 0x96,
  whiteg   = 0x97,

  contg    = 0x99,
  sepg     = 0x9a,


  bgblack       = 0x9c,
  bgnew         = 0x9d,

  holdg    = 0x9e,
  releaseg = 0x9f

} colorCode;

typedef enum sixelCode {
  a0       = 0xA0,
  a1       = 0xA1,
  a2       = 0xA2,
  a3       = 0xA3,
  a4       = 0xA4,
  a5       = 0xA5,
  a6       = 0xA6,
  a7       = 0xA7,
  a8       = 0xA8,
  a9       = 0xA9,
  aa       = 0xAA,
  ab       = 0xAB,
  ac       = 0xAC,
  ad       = 0xAD,
  ae       = 0xAE,
  af       = 0xAF,

  b0       = 0xB0,
  b1       = 0xB1,
  b2       = 0xB2,
  b3       = 0xB3,
  b4       = 0xB4,
  b5       = 0xB5,
  b6       = 0xB6,
  b7       = 0xB7,
  b8       = 0xB8,
  b9       = 0xB9,
  ba       = 0xBA,
  bb       = 0xBB,
  bc       = 0xBC,
  bd       = 0xBD,
  be       = 0xBE,
  bf       = 0xBF,

  e0       = 0xE0,
  e1       = 0xE1,
  e2       = 0xE2,
  e3       = 0xE3,
  e4       = 0xE4,
  e5       = 0xE5,
  e6       = 0xE6,
  e7       = 0xE7,
  e8       = 0xE8,
  e9       = 0xE9,
  ea       = 0xEA,
  eb       = 0xEB,
  ec       = 0xEC,
  ed       = 0xED,
  ee       = 0xEE,
  ef       = 0xEF,

  f0       = 0xF0,
  f1       = 0xF1,
  f2       = 0xF2,
  f3       = 0xF3,
  f4       = 0xF4,
  f5       = 0xF5,
  f6       = 0xF6,
  f7       = 0xF7,
  f8       = 0xF8,
  f9       = 0xF9,
  fa       = 0xFA,
  fb       = 0xFB,
  fc       = 0xFC,
  fd       = 0xFD,
  fe       = 0xFE,
  ff       = 0xFF

} sixelCode;


unsigned char checkChar(unsigned char chr);
void printCodes(SDL_Simplewin *sw, cell hex[HT][WT], flags *current,  fntrow (*fontdata)[18]);
void importCodes(char *filename, cell hex[25][40]);
void changeFlags(flags *flag);
void drawSmallSixel(SDL_Simplewin *sw, cell *hex, int i, int j,  int ox, int oy);
void makeSixels(SDL_Simplewin *sw, cell *hex, sixels sixel, int ox, int oy, int w, int h);
void setSixels(unsigned char code, sixels *sixel);
cell* cell_init(unsigned char data);
void setDrawColor(SDL_Simplewin *sw, color c);
void SDL_DrawChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy);
void SDL_DrawTopChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy);
void SDL_DrawBottomChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy);
void resetSixels(sixels *sixel);
void setFlags(unsigned char code, flags *current);
void  setHold( cell *c);
