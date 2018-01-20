#include "testing.h"
#include "stdio.h"


void importCodes(char *filename, cell hex[HT][WT])
{
  FILE *fp = fopen(filename, "rb");
  unsigned char temphex[HT][WT];
  int i, w, h;
  w = 0, h = 0, i = 0;

testFile(fp);

  while (( i = fread ( &temphex, sizeof(unsigned char),CELLCOUNT, fp)) > 0) {
     for (h = 0; h < HT; h++) {
        for (w = 0; w < WT; w++) {
          hex[h][w].code = (temphex[h][w]);
        }
     }
  fclose (fp);
}}


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
          else if (hex[h-1][w].flag.fontsize == topfont)
             {
            current->fontsize = bottomfont;
            hex[h][w].flag.fontsize = bottomfont;
            SDL_DrawDoubleChar(sw, &hex[h][w], fontdata, hex[h][w].code, w*CELLWT, h*CELLHT);
             }
          else if (current->fontsize == topfont)
             {
            hex[h][w].flag.fontsize = topfont;
            SDL_DrawDoubleChar(sw, &hex[h][w], fontdata, hex[h][w].code, w*CELLWT, h*CELLHT);
             }
          else {
            SDL_DrawChar(sw, &hex[h][w], fontdata, hex[h][w].code, w*CELLWT, h*CELLHT);
          }
        }
        resetSixels(&sixel);
  }
}

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

void  setHold( cell *c)
{
  static unsigned char mostrecent;
  static graphicsMode  lastgraphm = alphanumeric;
  static fontsz   lastfontsize  = normalfont;

  if (lastgraphm != c->flag.mode ||  lastfontsize != c->flag.fontsize) {
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
          SDL_RenderDrawPoint(sw->renderer, x + ox, y+oy);
      }
   }
}

void SDL_DrawDoubleChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy)
{
   unsigned x, y, fontheight, yheight;
   unsigned char letter;

/*Checks char is in range to print*/
letter = checkChar(chr);

/*If statements change print settings for top and bottom */
if(hex->flag.fontsize == bottomfont){
  fontheight = FNTHEIGHT;
  yheight = (FNTHEIGHT * 2);
}

if(hex->flag.fontsize == topfont){
   fontheight = 0;
   yheight = FNTHEIGHT;
}

/*Render the char using SDL/NeilSDL function structure */
   for(y = fontheight; y < yheight; y++){
      for(x = 0; x < FNTWIDTH; x++){
         if(letter > 0 && fontdata[letter-FNT1STCHAR][y/2] >> (FNTWIDTH - 1 - x) & 1){
          setDrawColor(sw, hex->flag.frontcolor);
         }
         else{
            setDrawColor(sw, hex->flag.backcolor);
            }
            if (hex->flag.fontsize == bottomfont){
            SDL_RenderDrawPoint(sw->renderer, x + ox, (y+oy)-FNTHEIGHT);
            }
        if(hex->flag.fontsize == topfont) {
          SDL_RenderDrawPoint(sw->renderer, x + ox, y+oy);
        }
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
