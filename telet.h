#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef enum color {
  white, black, red, yellow, blue
} color;

struct flags {
  color      textcolor;
} state;

typedef struct flags flags;

typedef struct cell {
  struct flags flag;
  unsigned char data;
} cell;
