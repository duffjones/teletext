#include "telet.h"


/*
void makeSixels(SDL_Simplewin *sw, cell *hex, sixels sixel, int ox, int oy, int w, int h){

  SDL_DrawSixel(sw, &hex[h][w], 0, 0, w*CELLWT, h*CELLHT);
  SDL_DrawSixel(sw, &hex[h][w], 5, 0, w*CELLWT, h*CELLHT);
  SDL_DrawSixel(sw, &hex[h][w], 0, 5, w*CELLWT, h*CELLHT);
if(sixel.uleft == true){

}

if(sixel.uright == true){

}
if(sixel.mleft == true){

}
if(sixel.mright == true){
SDL_DrawSixel(sw, &hex[h][w], 5, 5, w*CELLWT, h*CELLHT);

}
if(sixel.bleft == true){
SDL_DrawSixel(sw, &hex[h][w], 10, 0, w*CELLWT, h*CELLHT);

}
if(sixel.bright == true){
SDL_DrawSixel(sw, &hex[h][w], 10, 5, w*CELLWT, h*CELLHT);

}


}
*/

void drawSmallSixel(SDL_Simplewin *sw, cell *hex, int i, int j,  int ox, int oy)
  {
    unsigned x, y;
    SDL_Rect rectangle;

    for(y = 0; y < 6; y++){
       for(x = 0; x < 8; x++){
           setDrawColor(sw, hex->flag.frontcolor);
              rectangle.w = 1;
              rectangle.h = 1;
              rectangle.x = (x+i)+ox;
              rectangle.y = (y+j)+oy;
             SDL_RenderFillRect(sw->renderer, &rectangle);
             SDL_RenderDrawRect(sw->renderer, &rectangle);
        }
     }
  }

  void setSixels(unsigned char code, sixels *sixel)
  {

    /*
    printf("Printing Codes %d ",code);
    */
    switch ((sixelCode) code) {

      case f0:

      sixel-> uleft = false;
      sixel->uright = false;
      sixel->mleft= false ;
      sixel->mright= false;
      sixel->bleft= true;
      sixel->bright= true;
      break;

      case a3:

      sixel-> uleft = true;
      sixel->uright = true;
      sixel->mleft= false ;
      sixel->mright= false;
      sixel->bleft= false;
      sixel->bright= false;
      break;

      case b5:

      sixel-> uleft = true;
      sixel->uright = false;
      sixel->mleft= true ;
      sixel->mright= false;
      sixel->bleft= true;
      sixel->bright= false;
      break;

      case ea:

      sixel-> uleft = false;
      sixel->uright = true;
      sixel->mleft= false ;
      sixel->mright= true;
      sixel->bleft= false;
      sixel->bright= true;
      break;




      default:
      sixel->uleft = true;
      sixel->uright = true;
      sixel->mleft= true;
      sixel->mright= true;
      sixel->bleft= true;
      sixel->bright= true;
      break;
      }}
