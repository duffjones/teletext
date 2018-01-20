#include "telet.h"

#if EXTON
#define main notMain
#endif



int main(int argc, char **argv)
{
  cell hex[HT][WT];
  SDL_Simplewin sw;
  fntrow font[FNTCHARS][FNTHEIGHT];
  flags current;

  printf("BEGINNING PROGRAM!\n" );
  /*crash happens here without print statement?\
  testCodeDisplay(hex);
  */


  importCodes(argv[1], hex); /* Imports 1000 codes from ARGV1 into array of cell structs */
  testFunction(argc, argv[2], hex); /* Initializes testing from ARGV */
  Neill_SDL_ReadFont(font, "m7fixed.fnt");
  Neill_SDL_Init(&sw);
  printCodes(&sw, hex, &current, font); /* Prints 1000 codes to SDL*/

   do{
      SDL_Delay(MILLISECONDDELAY);
      Neill_SDL_UpdateScreen(&sw);
      Neill_SDL_Events(&sw);
     }

   while(!sw.finished);
      atexit(SDL_Quit);
      return 0;
}
