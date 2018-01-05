#include "telet.h"
#include "stdio.h"
#include "neillsdl2.h"

#define RECTSIZE 20
#define MILLISECONDDELAY 20
#define HT 25
#define WT 40
#define ON_ERROR(STR) fprintf(stderr, STR ); exit(EXIT_FAILURE)

void printCodes(SDL_Simplewin *sw, unsigned char hex[25][40], fntrow (*fontdata)[18]);
void readCodesFromFile(char *filename, unsigned char hex[25][40]);
FILE *openFile(char *filename, char *mode);
cell* cell_init(unsigned char data);

int main(int argc, char **argv)
{
  unsigned char hex[HT][WT];
  SDL_Simplewin sw;
  fntrow font[FNTCHARS][FNTHEIGHT];
  /*
  char* hello;
  hello = "WHERE IS YOUR GOD NOW?";
*/
  printf("STARTING TEST: \n" );
      if ( (argc != 2) )  {
        printf("ERROR: Incorrect usage:\nOnly 1 argument is required.\n");
      }
  readCodesFromFile(argv[1], hex);

printf("XXXXXXXXXX BREAK XXXXXXXXXX\n");
Neill_SDL_ReadFont(font, "m7fixed.fnt");
printf("Font Loaded\n");
Neill_SDL_Init(&sw);
/*Neill_SDL_DrawString(&sw, font, hello, 10, 10);*/
printCodes(&sw, hex, font);
printf("print s\n" );

do{
      SDL_Delay(MILLISECONDDELAY);
      Neill_SDL_UpdateScreen(&sw);
      Neill_SDL_Events(&sw);
  }

  while(!sw.finished);

      atexit(SDL_Quit);
      return 0;
}


FILE *openFile(char *filename, char *mode)
{
  FILE *file = fopen(filename, mode);
    if (file == NULL) {
    printf("ERROR: unable to open file:\nCheck filename and path.\n");
  }
  return file;
}

void readCodesFromFile(char *filename, unsigned char hex[25][40])
{
  FILE *fp = openFile(filename, "rb");
  int  i, bytes, w, h;
  unsigned char temphex[HT][WT];
  i = 1; w = 0; h = 0; bytes = 0;

  printf("file open\n");
  while (( bytes = fread ( &temphex, sizeof(unsigned char) ,1000, fp)) > 0) {
    for (h = 0; h < HT; h++) {
      for (w = 0; w < WT; w++) {
        /*
        printf("%02x  ",  temphex[h][w]);
        printf("%d",  temphex[h][w]);
        */
        printf("%c",(temphex[h][w]) - 128);
        hex[h][w] = temphex[h][w];

        /*

        hex[h][w] =  cell_init(temphex[h][w]);
        */
        i++;
      }
      printf("\n");
  }
  fclose ( fp);
  }}


void printCodes(SDL_Simplewin *sw, unsigned char hex[HT][WT], fntrow (*fontdata)[18])
  {
    int  w, h;
    unsigned char code[10];
    w = 0; h = 0;
    printf("Command: Print Codes:\n" );
      for (h = 0; h < HT; h++) {
        for (w = 0; w < WT; w++) {
          /*
          sprintf(( char*)code, "%02x", hex[h][w]);
          */
          sprintf(( char*)code, "%c", (hex[h][w])-128);
          Neill_SDL_DrawString(sw, fontdata, (char*)code, w*WT/2, h*HT);
          printf("%s ",code );
        }
        printf("\n");
  }
}

cell* cell_init(unsigned char data)
{
    cell* c = calloc(1, sizeof(cell));
    if (c == NULL){
      return 0;
    }

    /*c->flag->textcolor = NULL;*/
    c->data = data;
    return c;
}

/*
void data_insert(cell* c, unsigned char ch)
{

    if(c->data == NULL) {
      c->data = ch;
      return;
      }
}


convertHex(unsigned char hex[HT][WT]){





}
*/
