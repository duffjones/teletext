#include "stdio.h"
#include "telet.h"

void importCodes(char * filename, cell hex[HT][WT]) {
   FILE * fp = fopen(filename, "rb");
   unsigned char temphex[HT][WT];
   int i, w, h;
   w = 0, h = 0, i = 0;

   testFile(fp);

   while ((i = fread( & temphex, sizeof(unsigned char), CELLCOUNT, fp)) > 0) {
      for (h = 0; h < HT; h++) {
         for (w = 0; w < WT; w++) {
            hex[h][w].code = (temphex[h][w]);
         }
      }
   }
   fclose(fp);
}

/*Most Important Function: Prints/renders codes to SDL depending on their flags/types */
void printCodes(SDL_Simplewin * sw, cell hex[HT][WT], flags * current, fntrow( * fontdata)[18]) {
   int w, h;
   sixels sixel;
   w = 0;
   h = 0;

   for (h = 0; h < HT; h++) {
      /*Resets flags to default at start of new row*/
      changeFlags(current);
      for (w = 0; w < WT; w++) {
         /*decodes hex, and sets cell and current flags appropriately*/
         setFlags(hex[h][w].code, current);
         setCellFlags( & hex[h][w], current);
         setHold( & hex[h][w]);
         /*is the cell a graphic?*/
         if (hex[h][w].flag.mode == contiguous &&
            ((hex[h][w].code > a0 && hex[h][w].code <= bf) || hex[h][w].code >= e0)) {
            setDrawColor(sw, hex[h][w].flag.backcolor);
            DrawSixel(sw, & hex[h][w], h, w, sixel);
         /*is the cell separated graphics?*/
         } else if (hex[h][w].flag.mode == separate &&
            ((hex[h][w].code >= a0 && hex[h][w].code <= bf) || hex[h][w].code >= e0)) {
            DrawSixel(sw, & hex[h][w], h, w, sixel);
         /*is the cell separated graphics?*/
         } else if (hex[h - 1][w].flag.fontsize == topfont) {
            current -> fontsize = bottomfont;
            hex[h][w].flag.fontsize = bottomfont;
            SDL_DrawDoubleChar(sw, & hex[h][w], fontdata, hex[h][w].code, w * CELLWT, h * CELLHT);
         } else if (current -> fontsize == topfont) {
            hex[h][w].flag.fontsize = topfont;
            SDL_DrawDoubleChar(sw, & hex[h][w], fontdata, hex[h][w].code, w * CELLWT, h * CELLHT);
         /*Default case: render cell as a Char*/
         } else {
            SDL_DrawChar(sw, & hex[h][w], fontdata, hex[h][w].code, w * CELLWT, h * CELLHT);
         }
      }
      resetSixels( & sixel);
   }
}


void changeFlags(flags * flag) {
   flag -> frontcolor = white;
   flag -> backcolor = black;
   flag -> fontsize = normalfont;
   flag -> mode = alphanumeric;
   flag -> hold = release;
}

void setCellFlags(cell * c, flags * flag) {
   c -> flag.frontcolor = flag -> frontcolor;
   c -> flag.backcolor = flag -> backcolor;
   c -> flag.fontsize = flag -> fontsize;
   c -> flag.mode = flag -> mode;
   c -> flag.hold = flag -> hold;
}

/*Checks for hold condition and tracks recent cell states*/
void setHold(cell * c) {
   static unsigned char mostrecent;
   static graphicsMode lastgraphm = alphanumeric;
   static fontsz lastfontsize = normalfont;

   /* Sets most recent cell info in new case */
   if (lastgraphm != c -> flag.mode || lastfontsize != c -> flag.fontsize) {
      mostrecent = a0;
   }
   /* Sets most recent cell info to code, remembers hold(for next call) */
   if (c -> flag.hold == hold && c -> code <= a0) {
      c -> code = mostrecent;
      lastgraphm = hold;
   }
   /*remembers code within writable range (for next call)*/
   if (c -> code > a0 && c -> flag.mode != alphanumeric) {
      mostrecent = c -> code;
   }
   lastgraphm = c -> flag.mode;
   lastfontsize = c -> flag.fontsize;
}

void setDrawColor(SDL_Simplewin * sw, color c) {
   /* Draw Color is Selected by the argument received from current color flag*/
   switch (c) {

   case yellow:
      Neill_SDL_SetDrawColour(sw, MAXC, MAXC, 0);
      break;

   case blue:
      Neill_SDL_SetDrawColour(sw, 0, 0, MAXC);
      break;

   case red:
      Neill_SDL_SetDrawColour(sw, MAXC, 0, 0);
      break;

   case magenta:
      Neill_SDL_SetDrawColour(sw, MAXC, 0, MAXC);
      break;

   case cyan:
      Neill_SDL_SetDrawColour(sw, 0, MAXC, MAXC);
      break;

   case green:
      Neill_SDL_SetDrawColour(sw, 0, MAXC, 0);
      break;

   case black:
      Neill_SDL_SetDrawColour(sw, 0, 0, 0);
      break;

   default:
      Neill_SDL_SetDrawColour(sw, MAXC, MAXC, MAXC);
   }
}

/*This function is based of Neill_SDL_DrawChar */
void SDL_DrawChar(SDL_Simplewin * sw, cell * hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy) {
   unsigned x, y;
   unsigned char letter;
   letter = checkChar(chr);

   for (y = 0; y < FNTHEIGHT; y++) {
      for (x = 0; x < FNTWIDTH; x++) {
         if (fontdata[letter - FNT1STCHAR][y] >> (FNTWIDTH - 1 - x) & 1) {
            setDrawColor(sw, hex -> flag.frontcolor);
         } else {
            setDrawColor(sw, hex -> flag.backcolor);
         }
         SDL_RenderDrawPoint(sw -> renderer, x + ox, y + oy);
      }
   }
}

void SDL_DrawDoubleChar(SDL_Simplewin * sw, cell * hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy) {
   unsigned x, y, fontheight, yheight;
   unsigned char letter;

   /*Checks char is in range to print*/
   letter = checkChar(chr);

   /*If statements change char draw settings for top and bottom */
   if (hex -> flag.fontsize == bottomfont) {
      fontheight = FNTHEIGHT;
      yheight = (FNTHEIGHT * 2);
   }

   if (hex -> flag.fontsize == topfont) {
      fontheight = 0;
      yheight = FNTHEIGHT;
   }

   /*Render the char using SDL/NeilSDL function structure */
   for (y = fontheight; y < yheight; y++) {
      for (x = 0; x < FNTWIDTH; x++) {
         if (letter > 0 && fontdata[letter - FNT1STCHAR][y / 2] >> (FNTWIDTH - 1 - x) & 1) {
            setDrawColor(sw, hex -> flag.frontcolor);
         } else {
            setDrawColor(sw, hex -> flag.backcolor);
         }
         if (hex -> flag.fontsize == bottomfont) {
            SDL_RenderDrawPoint(sw -> renderer, x + ox, (y + oy) - FNTHEIGHT);
         }
         if (hex -> flag.fontsize == topfont) {
            SDL_RenderDrawPoint(sw -> renderer, x + ox, y + oy);
         }
      }
   }
}

/*checks a Char code is in suitable range for SDL, and converts it if outside appropriate range */
unsigned char checkChar(unsigned char chr) {
   unsigned char letter;

   if (chr >= hexlow && chr <= hexhigh) {
      letter = chr;
   } else if (chr > BLANK && chr < ff) {
      letter = chr - DIFF;
   } else {
      letter = BLANK - DIFF;
   }
   return letter;
}

/*Draws one of six sixels that makes up a cell.*/
void drawSmallSixel(SDL_Simplewin *sw, cell *hex, int i, int j,  int ox, int oy, boolean blank)
{
    unsigned x, y, sizey, sizex;
    SDL_Rect rectangle;
    sizey = CONY;
    sizex = CONX;
    /*Checks for separate graphics mode and changes rect size */
    if(hex->flag.mode == separate) {
        sizey = SEPY;
        sizex = SEPX;
    }

    for(y = 0; y < sizey*SZ; y++) {
       for(x = 0; x < sizex*SZ; x++) {
         if (blank == true){
            setDrawColor(sw, hex->flag.frontcolor);
          }
          else {
            setDrawColor(sw, hex->flag.backcolor);
          }
            rectangle.w = 1;
            rectangle.h = 1;
            rectangle.x = (x+i)+ox;
            rectangle.y = (y+j)+oy;
            SDL_RenderFillRect(sw->renderer, &rectangle);
            SDL_RenderDrawRect(sw->renderer, &rectangle);
        }
    }
}

void resetSixels(sixels *sixel)
{
    sixel->uleft = false;
    sixel->uright = false;
    sixel->mleft = false;
    sixel->mright = false;
    sixel->bright = false;
    sixel->bleft = false;
}

/* Draws a complete sixel from 6 small sixels, activated by a boolean determined by sixel case/switch*/
void DrawSixel(SDL_Simplewin *sw, cell *hex, int h, int w, sixels sixel) {
    setSixels(hex->code,  &sixel);

        drawSmallSixel(sw, hex, 0, 0, w*CELLWT, h*CELLHT, (sixel.uleft));
        drawSmallSixel(sw, hex, COORD8, 0, w*CELLWT, h*CELLHT, (sixel.uright));
        drawSmallSixel(sw, hex, 0, COORD6, w*CELLWT, h*CELLHT, (sixel.mleft));
        drawSmallSixel(sw, hex, COORD8, COORD6, w*CELLWT, h*CELLHT, (sixel.mright));
        drawSmallSixel(sw, hex, 0, COORD12, w*CELLWT, h*CELLHT, (sixel.bleft));
        drawSmallSixel(sw, hex, COORD8, COORD12, w*CELLWT, h*CELLHT, (sixel.bright));

    resetSixels(&sixel);
}

/* Handles all incoming hex codes, and changes appropriate current or cell flags*/
void setFlags(unsigned char code, flags * current) {
   switch ((controlCode) code) {

   /* SELECT FONT COLOR*/
   case yellowf:
      current -> frontcolor = yellow;
      current -> mode = alphanumeric;
      break;

   case bluef:
      current -> frontcolor = blue;
      current -> mode = alphanumeric;
      break;

   case redf:
      current -> frontcolor = red;
      current -> mode = alphanumeric;
      break;

   case magentaf:
      current -> frontcolor = magenta;
      current -> mode = alphanumeric;
      break;

   case cyanf:
      current -> frontcolor = cyan;
      current -> mode = alphanumeric;
      break;

   case whitef:
      current -> frontcolor = white;
      current -> mode = alphanumeric;
      break;

   case greenf:
      current -> frontcolor = green;
      current -> mode = alphanumeric;
      break;

   /* SELECT FONT HEIGHT*/
   case singleheight:
      current -> fontsize = normalfont;
      current -> mode = alphanumeric;
      break;

   case doubleheight:
      current -> fontsize = topfont;
      current -> mode = alphanumeric;
      break;

   /* SELECT BACKGROUND COLOR*/
   case bgblack:
      current -> backcolor = black;
      break;

   case bgnew:

      current -> backcolor = current -> frontcolor;
      break;

    /*SELECT GRAPHICS MODE AND COLOR FOR GRAPHICS*/
   case redg:
      current -> mode = contiguous;
      current -> frontcolor = red;
      break;

   case greeng:
      current -> mode = contiguous;
      current -> frontcolor = green;
      break;

   case yellowg:
      current -> mode = contiguous;
      current -> frontcolor = yellow;
      break;

   case blueg:
      current -> mode = contiguous;
      current -> frontcolor = blue;
      break;

   case magentag:
      current -> mode = contiguous;
      current -> frontcolor = magenta;
      break;

   case cyang:
      current -> mode = contiguous;
      current -> frontcolor = cyan;
      break;

   case whiteg:
      current -> mode = contiguous;
      current -> frontcolor = white;
      break;

   case contg:
      current -> mode = contiguous;
      break;

   case sepg:
      current -> mode = separate;
      break;

   /* HOLD AND RELEASE*/
   case holdg:
      current -> hold = hold;
      break;

   case releaseg:
      current -> hold = release;
      break;

   default:
      break;
   }
}

/*this is where sixels are coded, small sixels turning on and off.*/
void setSixels(unsigned char code, sixels *sixel)
{
  switch ((sixelCode) code) {

    case a0:
    break;
    case a1:TL;
    break;
    case a2:TR;
    break;
    case a3:TL; TR;
    break;
    case a4:ML;
    break;
    case a5:TL; ML;
    break;
    case a6:TR; ML;
    break;
    case a7:TL; TR; ML;
    break;
    case a8:MR;
    break;
    case a9:TL; MR;
    break;
    case aa:TR; MR;
    break;
    case ab:TL; TR; MR;
    break;
    case ac:ML; MR;
    break;
    case ad:TL; MR; ML;
    break;
    case ae:TR; ML; MR;
    break;
    case af:TR; TL; MR; ML;
    break;

    case b0:BL;
    break;
    case b1:TL; BL;
    break;
    case b2:TR; BL;
    break;
    case b3:TR; TL; BL;
    break;
    case b4:BL; ML;
    break;
    case b5:TL; ML; BL;
    break;
    case b6:TR; ML; BL;
    break;
    case b7:TL; ML; BL; TR;
    break;
    case b8:BL; MR;
    break;
    case b9:TL; MR; BL;
    break;
    case ba:TR; MR; BL;
    break;
    case bb:TL; TR; MR; BL;
    break;
    case bc:ML; MR; BL;
    break;
    case bd:TL; ML; BL; MR;
    break;
    case be:TR; MR; ML; BL;
    break;
    case bf:TL; TR; ML; MR; BL;
    break;

    case e0:BR;
    break;

    case e1:BR; TL;
    break;
    case e2:TR; BR;
    break;
    case e3:TR; TL; BR;
    break;
    case e4:ML; BR;
    break;
    case e5:TL; ML; BR;
    break;
    case e6:TR; ML; BR;
    break;
    case e7:TL; TR; ML; BR;
    break;
    case e8:ML; BL;
    break;
    case e9:TL; ML; BL;
    break;
    case ea:TR; MR; BR;
    break;
    case eb:TL; TR; MR; ML;
    break;
    case ec:ML; MR; BR;
    break;
    case ed:TL; ML; MR; BR;
    break;
    case ee:TR; MR; BR; ML;
    break;
    case ef:TR; TL; MR; ML; BR;
    break;

    case f0:BR; BL;
    break;
    case f1:TL; BL; BR;
    break;
    case f2:TR; BR; BL;
    break;
    case f3:TL; TR; BL; BR;
    break;
    case f4:ML; BR; BL;
    break;
    case f5:TL; ML; BL; BR;
    break;
    case f6:TR; ML; BL; BR;
    break;
    case f7:TR; TL; ML; BR; BL;
    break;
    case f8:BL; MR; ML;
    break;
    case f9:TL; MR; BL; BR;
    break;
    case fa:TR; MR; BL; BR;
    break;
    case fb:TL; TR; MR; BL; BR;
    break;
    case fc:MR; ML; BR; BL;
    break;
    case fd:TL; ML; MR; BL; BR;
    break;
    case fe:TR; MR; ML; BR; BL;
    break;
    case ff:TR; TL; MR; ML; BR; BL;
    break;
    default: return;

    }}
