#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "neillsdl2.h"


#define MILLISECONDDELAY 20
#define BLANK 0xA0

#define ON_ERROR(STR) fprintf(stderr, STR ); exit(EXIT_FAILURE)

typedef enum color {
  w = 6, z = 9, r = 3, y = 1, b =2, c = 5, m = 4, g = 7
} color;

typedef enum fontsz {
  normalfont = 1, topfont = 2, bottomfont = 3
} fontsz;

typedef enum graphicsMode {
  alphanumeric, contiguous, separate
} graphicsMode;


typedef struct flags {
  color     frontcolor;
  color     backcolor;
  fontsz    fontsize;
  graphicsMode mode;


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
  bgnew         = 0x9d

} colorCode;








void printCodes(SDL_Simplewin *sw, cell hex[HT][WT], flags *current,  fntrow (*fontdata)[18]);
void importCodes(char *filename, cell hex[25][40]);
void changeFlags(flags *flag);
cell* cell_init(unsigned char data);
