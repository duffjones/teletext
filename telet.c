#include "telet.h"
#include "stdio.h"
#include "neillsdl2.h"

#define RECTSIZE 20
#define MILLISECONDDELAY 20

void readCodesFromFile(char *filename, unsigned char hex[25][40]);
FILE *openFile(char *filename, char *mode);


int main(int argc, char **argv)
{
  unsigned char hex[25][40];
  SDL_Simplewin sw;

  printf("STARTING TEST: \n" );
      if ( (argc != 2) )  {
        printf("ERROR: Incorrect usage:\nOnly 1 argument is required.\n");
      }
  readCodesFromFile(argv[1], hex);
printf("XXXXXXXXXX BREAK XXXXXXXXXX\n");



Neill_SDL_Init(&sw);


do{

      SDL_Delay(MILLISECONDDELAY);

      Neill_SDL_UpdateScreen(&sw);

      /* Has anyone pressed ESC or killed the SDL window ?
         Must be called frequently - it's the only way of escaping  */
      Neill_SDL_Events(&sw);

   }while(!sw.finished);


   /* Clear up graphics subsystems */
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
  unsigned char temphex[25][40];
  i = 1; w = 0; h = 0; bytes = 0;


  printf("file open\n");

  while (( bytes = fread ( &temphex, sizeof(unsigned char) ,1000, fp)) > 0) {
    for (h = 0; h < 25; h++) {
      for (w = 0; w < 40; w++) {
        printf("%02x  ",  temphex[h][w]);
        hex[h][h] = temphex[h][w];
        i++;
      }
      printf("\n");
  }
  fclose ( fp);

  }}
