#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "neillsdl2.h"

#define RECTSIZE 20
#define MILLISECONDDELAY 20
#define HT 25
#define WT 40
#define ON_ERROR(STR) fprintf(stderr, STR ); exit(EXIT_FAILURE)

typedef enum color {
  w, z, r, y, b
} color;

struct flags {
  color     frontcolor;
  color     backcolor;
} state;

typedef struct flags flags;

typedef struct cell {
  flags flag;
  unsigned char code;
} cell;


typedef enum colorCode {
  redalpha        = 81,
  greenalpha      = 82,
  yellowalpha     = 83,
  bluealpha       = 84,
  whitealpha      = 87,

} colorCode;



void printCodes(SDL_Simplewin *sw, cell hex[HT][WT], flags *current,  fntrow (*fontdata)[18]);
void importCodes(char *filename, cell hex[25][40]);
void changeFlags(flags *flag);
FILE *openFile(char *filename, char *mode);
cell* cell_init(unsigned char data);
