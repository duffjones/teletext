/*neillsdl2 HAS BEEN INCLUDED WITHOUT CHANGES IN THIS PROGRAM.*/
/* I wasn't sure if it would be more appropriate to take the functions I needed, and rework them */
/*Since their structure would inevitable be the same as below, I figured it would be better to leave */
/*them in their original forms, and cite them here:   */

#include <SDL.h>
#include <math.h>

/*Added by me */
/*Nothing Changed in Functions Below */
#define WWIDTH (CELLWT * WT)
#define WHEIGHT (CELLHT * HT)
#define HT 25
#define WT 40
#define CELLHT 18
#define CELLWT 16

/* Font stuff */
typedef unsigned short fntrow;
#define FNTWIDTH (sizeof(fntrow)*8)
#define FNTHEIGHT 18
#define FNTCHARS 96
#define FNT1STCHAR 32

#define SDL_8BITCOLOUR 256

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

/* All info required for windows / renderer & event loop */
struct SDL_Simplewin {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
   SDL_Texture *display;
};
typedef struct SDL_Simplewin SDL_Simplewin;

void Neill_SDL_Init(SDL_Simplewin *sw);
void Neill_SDL_Events(SDL_Simplewin *sw);
void Neill_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b);
void Neill_SDL_DrawChar(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy);
void Neill_SDL_ReadFont(fntrow fontdata[FNTCHARS][FNTHEIGHT], char *fname);
void Neill_SDL_UpdateScreen(SDL_Simplewin *sw);
