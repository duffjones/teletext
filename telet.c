#include "telet.h"
#include "stdio.h"

int main(int argc, char **argv)
{
  cell hex[HT][WT];
  SDL_Simplewin sw;
  fntrow font[FNTCHARS][FNTHEIGHT];

  printf("STARTING TEST: \n" );
      if ( (argc != 2) )  {
        printf("ERROR: Incorrect usage:\nOnly 1 argument is required.\n");
      }

importCodes(argv[1], hex);
Neill_SDL_ReadFont(font, "m7fixed.fnt");
Neill_SDL_Init(&sw);
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

void importCodes(char *filename, cell hex[25][40])
{
  FILE *fp = openFile(filename, "rb");
  int bytes, w, h;
  unsigned char temphex[HT][WT];
 w = 0; h = 0; bytes = 0;

  printf("file open\n");
  while (( bytes = fread ( &temphex, sizeof(unsigned char) ,1000, fp)) > 0) {

        for (h = 0; h < HT; h++) {
          for (w = 0; w < WT; w++) {
            hex[h][w].code = (temphex[h][w]-128);

      }
  }
  fclose ( fp);
  }}


void changeFlags(flags *flag)
  {
    flag->frontcolor = white;
    flag->backcolor = black;
  }

  void setCellFlags(cell *c, flags *flag)
  {
    c->flag.frontcolor = flag->frontcolor;
    c->flag.backcolor = flag->backcolor;
  }


void printCodes(SDL_Simplewin *sw, cell hex[HT][WT], fntrow (*fontdata)[18])
  {
    int  w, h;
    w = 0; h = 0;

    printf("Command: Print Codes:\n" );
      for (h = 0; h < HT; h++) {

        for (w = 0; w < WT; w++) {
          Neill_SDL_DrawChar(sw, fontdata, hex[h][w].code, w*WT/2, h*HT);
        }
        printf("\n");
  }
}
