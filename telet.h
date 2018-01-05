
typedef enum color {
  white, black, red, yellow, blue
} color;

typedef struct flags {
  color      textcolor;
} state;

typedef struct cell {
  flags flag;
  unsigned char data[];
} cell;


//struct for entire array?
