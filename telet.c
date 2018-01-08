#include "telet.h"
#include "stdio.h"

void SDL_DrawChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy);
void SDL_DrawTopChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy);
void SDL_DrawBottomChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy);
void resetSixels(sixels *sixel);

void setFlags(unsigned char code, flags *current);
void  setHold( cell *c);


int main(int argc, char **argv)
{
  cell hex[HT][WT];
  SDL_Simplewin sw;
  fntrow font[FNTCHARS][FNTHEIGHT];
  flags current;

  printf("STARTING TEST: \n" );
      if ( (argc != 2) )  {
        printf("ERROR: Incorrect usage:\nOnly 1 argument is required.\n");
      }

importCodes(argv[1], hex);
Neill_SDL_ReadFont(font, "m7fixed.fnt");
Neill_SDL_Init(&sw);
printCodes(&sw, hex, &current, font);

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

void importCodes(char *filename, cell hex[25][40])
{
  FILE *fp = fopen(filename, "rb");
  int i, w, h;

  unsigned char temphex[HT][WT];
 w = 0; h = 0; i = 0;

 if (fp== NULL) {
 printf("ERROR: unable to open file:\nCheck filename and path.\n");
}
  printf("file open\n");
  while (( i = fread ( &temphex, sizeof(unsigned char) ,1000, fp)) > 0) {
        for (h = 0; h < HT; h++) {
          for (w = 0; w < WT; w++) {
              hex[h][w].code = (temphex[h][w]);
              printf("%x ", temphex[h][w]);
      }
      printf("\n" );
  }
  fclose ( fp);
  }}


void changeFlags(flags *flag)
  {
    flag->frontcolor = w;
    flag->backcolor = z;
    flag->fontsize = 1;
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

    printf("Command: Print Codes:\n" );
      for (h = 0; h < HT; h++) {
        changeFlags(current);
        for (w = 0; w < WT; w++) {
          setFlags(hex[h][w].code, current);
          setCellFlags(&hex[h][w], current);
          setHold( &hex[h][w]);

          if((hex[h][w].flag.mode == contiguous
            && hex[h][w].code >= a0 && hex[h][w].code<=bf)
            || (hex[h][w].flag.mode == contiguous
            && hex[h][w].code >= e0)
          ){

            setSixels(hex[h][w].code,  &sixel);
            if(sixel.uleft == true){
              drawSmallSixel(sw, &hex[h][w], 0, 0, w*CELLWT, h*CELLHT);
            }
            if(sixel.uright == true){
              drawSmallSixel(sw, &hex[h][w], 8, 0, w*CELLWT, h*CELLHT);
            }
            if(sixel.mleft == true){
              drawSmallSixel(sw, &hex[h][w], 0, 6, w*CELLWT, h*CELLHT);
            }
            if(sixel.mright == true){
              drawSmallSixel(sw, &hex[h][w], 8, 6, w*CELLWT, h*CELLHT);
            }
            if(sixel.bleft == true){
              drawSmallSixel(sw, &hex[h][w], 0, 12, w*CELLWT, h*CELLHT);
            }
            if(sixel.bright == true){
              drawSmallSixel(sw, &hex[h][w], 8, 12, w*CELLWT, h*CELLHT);
            }
            resetSixels(&sixel);
          }
          else          if((hex[h][w].flag.mode == separate
                        && hex[h][w].code >= a0 && hex[h][w].code<=bf)
                        || (hex[h][w].flag.mode == separate
                        && hex[h][w].code >= e0 )
                      ){

                      setSixels(hex[h][w].code,  &sixel);
                      if(sixel.uleft == true){
                        drawSmallSixel(sw, &hex[h][w], 0, 0, w*CELLWT, h*CELLHT);
                      }
                      if(sixel.uright == true){
                        drawSmallSixel(sw, &hex[h][w], 8, 0, w*CELLWT, h*CELLHT);
                      }
                      if(sixel.mleft == true){
                        drawSmallSixel(sw, &hex[h][w], 0, 6, w*CELLWT, h*CELLHT);
                      }
                      if(sixel.mright == true){
                        drawSmallSixel(sw, &hex[h][w], 8, 6, w*CELLWT, h*CELLHT);
                      }
                      if(sixel.bleft == true){
                        drawSmallSixel(sw, &hex[h][w], 0, 12, w*CELLWT, h*CELLHT);
                      }
                      if(sixel.bright == true){
                        drawSmallSixel(sw, &hex[h][w], 8, 12, w*CELLWT, h*CELLHT);
                      }
                      resetSixels(&sixel);

                    }

          else if (hex[h-1][w].flag.fontsize == 2){
            current->fontsize = bottomfont;
            SDL_DrawBottomChar(sw, &hex[h][w], fontdata, hex[h][w].code, w*CELLWT, h*CELLHT);
          }
          else if (current->fontsize == topfont) {
            hex[h][w].flag.fontsize = topfont;
            SDL_DrawTopChar(sw, &hex[h][w], fontdata, hex[h][w].code, w*CELLWT, h*CELLHT);
          }
          else {
            SDL_DrawChar(sw, &hex[h][w], fontdata, hex[h][w].code, w*CELLWT, h*CELLHT);
          }
        }
        printf("\n");
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

void resetSixels(sixels *sixel)
    {
      sixel->uleft=false ;
      sixel->uright = false;
      sixel->mleft= false;
      sixel->mright= false;
      sixel->bright= false;
      sixel->bleft= false;
    }
void SDL_DrawChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy)
{
   unsigned x, y;
   unsigned char letter;

   if(chr > BLANK){
     letter = chr - 128;
   }
   else {
     letter = BLANK - 128;
   }

   for(y = 0; y < FNTHEIGHT; y++){
      for(x = 0; x < FNTWIDTH; x++){
        /*cutting y in half makes just top bit*/
         if(fontdata[letter-FNT1STCHAR][y] >> (FNTWIDTH - 1 - x) & 1){
          setDrawColor(sw, hex->flag.frontcolor);

         }
         else{
          setDrawColor(sw, hex->flag.backcolor);
             }
             /*messing with this changes font height and stuff */
          SDL_RenderDrawPoint(sw->renderer, x + ox, (y)+oy);
      }
   }
}

void SDL_DrawTopChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy)
{
   unsigned x, y;
   unsigned char letter;

   if(chr > BLANK){
     letter = chr - 128;
   }
   else {
     letter = BLANK - 128;
   }

   for(y = 0; y < FNTHEIGHT; y++){
      for(x = 0; x < FNTWIDTH; x++){
        /*cutting y in half makes just top bit*/
         if(chr - 128 > 0 && fontdata[letter-FNT1STCHAR][y/2] >> (FNTWIDTH - 1 - x) & 1){
           /*
           printf("Draw color set\n" );
           */
          setDrawColor(sw, hex->flag.frontcolor);
          /*
          printf("DC %d\n",hex->flag.frontcolor );
          */
         }
         else{
          setDrawColor(sw, hex->flag.backcolor);
             }
             /*messing with this changes font height and stuff */
          SDL_RenderDrawPoint(sw->renderer, x + ox, (y-FNTHEIGHT/2)+oy);
      }
   }
}
void SDL_DrawBottomChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy)
{
   unsigned x, y;
   unsigned char letter;

   if(chr > BLANK){
     letter = chr - 128;
   }
   else {
     letter = BLANK - 128;
   }

   for(y = FNTHEIGHT/2; y < FNTHEIGHT; y++){
      for(x = 0; x < FNTWIDTH; x++){
        /*cutting y in half makes just top bit*/
         if(chr - 128 > 0 && fontdata[letter-FNT1STCHAR][y] >> (FNTWIDTH - 1 - x) & 1){
           /*
           printf("Draw color set\n" );
           */
          setDrawColor(sw, hex->flag.frontcolor);
          /*
          printf("DC %d\n",hex->flag.frontcolor );
          */
         }
         else{
          setDrawColor(sw, hex->flag.backcolor);
             }
             /*messing with this changes font height and stuff */
          SDL_RenderDrawPoint(sw->renderer, x + ox, ((y*2)-FNTHEIGHT)+oy - 9);
      }
   }
}
void setDrawColor(SDL_Simplewin *sw, color c){
/*
     printf("Grade is = %d\n", c );
*/
     switch(c) {
       /*yellow*/
        case 1 :
           Neill_SDL_SetDrawColour(sw, 255, 255, 0 );
           break;

        case 2 :
           Neill_SDL_SetDrawColour(sw, 0, 0, 255);
           break;

        case 3 :
           Neill_SDL_SetDrawColour(sw, 255, 0, 0);
           break;

        case 4 :
           Neill_SDL_SetDrawColour(sw, 255, 0, 125);
           break;

        case 5 :
          Neill_SDL_SetDrawColour(sw, 0, 255, 255);
          break;

        case 7 :
          Neill_SDL_SetDrawColour(sw, 0, 255, 0);
          break;

        case 9 :
          Neill_SDL_SetDrawColour(sw, 0, 0, 0);
          break;

        default :
           Neill_SDL_SetDrawColour(sw, 255, 255, 255);

     }
}

void setFlags(unsigned char code, flags *current){

  /*
  printf("Printing Codes %d ",code);
  */
  switch ((colorCode) code) {

    case yellowf:
    current->frontcolor = 1;
    current->mode = alphanumeric;
    break;
case bluef:
    current->frontcolor = 2;
    current->mode = alphanumeric;
    break;

    case redf:
    current->frontcolor = 3;
    current->mode = alphanumeric;
    break;

case magentaf:
    current->frontcolor = 4;
    current->mode = alphanumeric;
    break;

case cyanf:
    current->frontcolor = 5;
    current->mode = alphanumeric;
    break;

case whitef:
    current->frontcolor = 6;
    current->mode = alphanumeric;
    break;

case greenf:
    current->frontcolor = 7;
    current->mode = alphanumeric;
    break;

case singleheight:
    current->fontsize = 1;
    break;

case doubleheight:
    current->fontsize = 2;
    break;

case bgblack:
    current->backcolor = 9;
    break;

case bgnew:
    current->backcolor = current->frontcolor;
    break;

case redg:
    current->mode = contiguous;
    current->frontcolor = r;
    break;

case greeng:
    current->mode = contiguous;
    current->frontcolor = g;
    break;

case yellowg:
      current->mode = contiguous;
      current->frontcolor = y;
      break;

case blueg:
      current->mode = contiguous;
      current->frontcolor = b;
      break;

case magentag:
      current->mode = contiguous;
      current->frontcolor = m;
      break;

case cyang:
      current->mode = contiguous;
      current->frontcolor = c;
      break;

case whiteg:
      current->mode = contiguous;
      current->frontcolor = w;
      break;

case contg:
      current->mode = contiguous;
      break;

case sepg:
      current->mode  = separate;
      break;

      case holdg:
        current->hold = hold;
        break;
      case releaseg:
        current->hold = release;
        break;
      default:
        break;
    }}
