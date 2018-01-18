#include "testing.h"
#include "stdio.h"



int main(int argc, char **argv)
{
  cell hex[HT][WT];
  SDL_Simplewin sw;
  fntrow font[FNTCHARS][FNTHEIGHT];
  flags current;

  printf("BEGINNING TESTS!\n" );
  /*crash happens here without print statement?*/
  testArgC(argc);
  importCodes(argv[1], hex);
  testCodeDisplay(hex);

  Neill_SDL_ReadFont(font, "m7fixed.fnt");
  Neill_SDL_Init(&sw);

  printCodes(&sw, hex, &current, font);

   do{
      SDL_Delay(MILLISECONDDELAY);
      Neill_SDL_UpdateScreen(&sw);
      Neill_SDL_Events(&sw);
     }

   while(!sw.finished);
      atexit(SDL_Quit);
      return 0;
}

void importCodes(char *filename, cell hex[HT][WT])
{
  FILE *fp = fopen(filename, "rb");
  unsigned char temphex[HT][WT];
  int i, w, h;
  w = 0, h = 0, i = 0;

  if (fp == NULL)
   {
      ON_ERROR("unable to open file:\nCheck filename and path.\n");
   }

  while (( i = fread ( &temphex, sizeof(unsigned char),CELLCOUNT, fp)) > 0) {
     for (h = 0; h < HT; h++) {
        for (w = 0; w < WT; w++) {
          hex[h][w].code = (temphex[h][w]);
        }
     }
  testCodes(i);
  fclose (fp);

}}


void changeFlags(flags *flag)
  {
    flag->frontcolor = white;
    flag->backcolor = black;
    flag->fontsize = normalfont;
    flag->mode = alphanumeric;
    flag->hold = release;
  }

void setCellFlags(cell *c, flags *flag)
  {
    c->flag.frontcolor = flag->frontcolor;
    c->flag.backcolor = flag->backcolor;
    c->flag.mode = flag->mode;
    c->flag.hold = flag->hold;
    c->flag.fontsize = flag->fontsize;
  }


void printCodes(SDL_Simplewin *sw, cell hex[HT][WT], flags *current,  fntrow (*fontdata)[18])
  {
    int  w, h;
    sixels sixel;
    w = 0; h = 0;

      for (h = 0; h < HT; h++) {
        changeFlags(current);
        for (w = 0; w < WT; w++) {

          setFlags(hex[h][w].code, current);
          setCellFlags(&hex[h][w], current);
          setHold(&hex[h][w]);

          if(hex[h][w].flag.mode == contiguous &&
            ((hex[h][w].code > a0 && hex[h][w].code<=bf)|| hex[h][w].code >= e0))
            {

               setDrawColor(sw, hex[h][w].flag.backcolor);

            DrawSixel(sw, &hex[h][w], h, w, sixel);
            }
          else if(hex[h][w].flag.mode == separate &&
            ((hex[h][w].code >= a0 && hex[h][w].code<=bf)|| hex[h][w].code >= e0))
            {
            DrawSixel(sw, &hex[h][w], h, w, sixel);
            }
          else if (hex[h-1][w].flag.fontsize == 2)
          {
            current->fontsize = bottomfont;
            SDL_DrawBottomChar(sw, &hex[h][w], fontdata, hex[h][w].code, w*CELLWT, h*CELLHT);
          }
          else if (current->fontsize == topfont)
          {
            hex[h][w].flag.fontsize = topfont;
            SDL_DrawTopChar(sw, &hex[h][w], fontdata, hex[h][w].code, w*CELLWT, h*CELLHT);
          }
          else {
            SDL_DrawChar(sw, &hex[h][w], fontdata, hex[h][w].code, w*CELLWT, h*CELLHT);
          }
        }
        resetSixels(&sixel);
  }
}

void  setHold( cell *c)
{
  static unsigned char mostrecent;
  static graphicsMode  lastgraphm = alphanumeric;
  static fontsz   lastfontsize  = normalfont;



  if ( lastgraphm != c->flag.mode ||  lastfontsize != c->flag.fontsize) {
    mostrecent = a0;
  }
  if (c->flag.hold == hold && c->code <= a0) {
    c->code = mostrecent;
     lastgraphm = hold;
  }
  if (c->code > a0 && c->flag.mode != alphanumeric) {
    mostrecent = c->code;
  }
   lastgraphm = c->flag.mode;
   lastfontsize  = c->flag.fontsize;
}


void SDL_DrawChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy)
{
   unsigned x, y;
   unsigned char letter;
   letter = checkChar(chr);

   for(y = 0; y < FNTHEIGHT; y++){
      for(x = 0; x < FNTWIDTH; x++){
         if(fontdata[letter-FNT1STCHAR][y] >> (FNTWIDTH - 1 - x) & 1){
          setDrawColor(sw, hex->flag.frontcolor);
         }
         else{
          setDrawColor(sw, hex->flag.backcolor);
             }
          SDL_RenderDrawPoint(sw->renderer, x + ox, (y)+oy);
      }
   }
}

void SDL_DrawTopChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy)
{
   unsigned x, y;
   unsigned char letter;

   letter = checkChar(chr);

   for(y = 0; y < FNTHEIGHT; y++){
      for(x = 0; x < FNTWIDTH; x++){
         if((letter > 0) && fontdata[letter-FNT1STCHAR][y/2] >> (FNTWIDTH - 1 - x) & 1){
          setDrawColor(sw, hex->flag.frontcolor);
         }

         else{
          setDrawColor(sw, hex->flag.backcolor);
             }
             /*messing with this changes font height and stuff */
          SDL_RenderDrawPoint(sw->renderer, x + ox, y+oy);
      }
   }
}

unsigned char checkChar(unsigned char chr){
  unsigned char letter;

  if(chr  >= hexlow && chr <= hexhigh){
    letter = chr;
  }

  else if(chr > BLANK && chr < ff){
    letter = chr - DIFF;
  }

  else {
    letter = BLANK - DIFF;
  }
  return letter;
}

void SDL_DrawBottomChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy)
{
   unsigned x, y;
   unsigned char letter;

   letter = checkChar(chr);

   for(y = FNTHEIGHT ; y < FNTHEIGHT *2; y++){
      for(x = 0; x < FNTWIDTH; x++){
         if(letter > 0 && fontdata[letter-FNT1STCHAR][y/2] >> (FNTWIDTH - 1 - x) & 1){
          setDrawColor(sw, hex->flag.frontcolor);
         }
         else{
            setDrawColor(sw, hex->flag.backcolor);
            }
          SDL_RenderDrawPoint(sw->renderer, x + ox, y+oy - (FNTHEIGHT ));
      }
   }
}



void setDrawColor(SDL_Simplewin *sw, color c){
/* Draw Color is Selected by the argument received from current color flag*/
     switch(c) {

        case yellow :
           Neill_SDL_SetDrawColour(sw, MAXC, MAXC, 0 );
           break;

        case blue :
           Neill_SDL_SetDrawColour(sw, 0, 0, MAXC);
           break;

        case red :
           Neill_SDL_SetDrawColour(sw, MAXC, 0, 0);
           break;

        case magenta :
           Neill_SDL_SetDrawColour(sw, MAXC, 0, MAXC);
           break;

        case cyan :
          Neill_SDL_SetDrawColour(sw, 0, MAXC, MAXC);
          break;

        case green :
          Neill_SDL_SetDrawColour(sw, 0, MAXC, 0);
          break;

        case black :
          Neill_SDL_SetDrawColour(sw, 0, 0, 0);
          break;

        default :
           Neill_SDL_SetDrawColour(sw, MAXC, MAXC, MAXC);

     }
}

void setFlags(unsigned char code, flags *current){
switch ((colorCode) code) {
/* SELECT FONT COLOR*/
case yellowf:
    current->frontcolor = yellow;
    current->mode = alphanumeric;
    break;

case bluef:
    current->frontcolor = blue;
    current->mode = alphanumeric;
    break;

case redf:
    current->frontcolor = red;
    current->mode = alphanumeric;
    break;

case magentaf:
    current->frontcolor = magenta;
    current->mode = alphanumeric;
    break;

case cyanf:
    current->frontcolor = cyan;
    current->mode = alphanumeric;
    break;

case whitef:
    current->frontcolor = white;
    current->mode = alphanumeric;
    break;

case greenf:
    current->frontcolor = green;
    current->mode = alphanumeric;
    break;

/* SELECT FONT HEIGHT*/
case singleheight:
    current->fontsize = normalfont;
    current->mode = alphanumeric;
    break;

case doubleheight:
    current->fontsize = topfont;
    current->mode = alphanumeric;
    break;

/* SELECT BACKGROUND COLOR*/
case bgblack:
    current->backcolor = black;
    break;

case bgnew:

    current->backcolor = current->frontcolor;
    break;

/*SELECT GRAPHICS MODE AND COLOR FOR GRAPHICS*/
case redg:
    current->mode = contiguous;
    current->frontcolor = red;
    break;

case greeng:
    current->mode = contiguous;
    current->frontcolor = green;
    break;

case yellowg:
      current->mode = contiguous;
      current->frontcolor = yellow;
      break;

case blueg:
      current->mode = contiguous;
      current->frontcolor = blue;
      break;

case magentag:
      current->mode = contiguous;
      current->frontcolor = magenta;
      break;

case cyang:
      current->mode = contiguous;
      current->frontcolor = cyan;
      break;

case whiteg:
      current->mode = contiguous;
      current->frontcolor = white;
      break;

case contg:
      current->mode = contiguous;
      break;

case sepg:
      current->mode  = separate;
      break;

/* HOLD AND RELEASE*/
case holdg:
        current->hold = hold;
        break;

case releaseg:
      current->hold = release;
      break;

default:
      break;
    }}
