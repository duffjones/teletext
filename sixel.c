#include "telet.h"


void drawSmallSixel(SDL_Simplewin *sw, cell *hex, int i, int j,  int ox, int oy)
  {
    unsigned x, y, sizey, sizex;
    SDL_Rect rectangle;
    sizey = 3;
    sizex = 4;
    if(hex->flag.mode == separate){
      sizey = 2;
      sizex = 3;
    }

    for(y = 0; y < sizey*2; y++){
       for(x = 0; x < sizex *2; x++){
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


/*

      case f0:
      BR; BL;
      sixel-> uleft = false;
      sixel->uright = false;
      sixel->mleft= false ;
      sixel->mright= false;
      sixel->bleft= true;
      sixel->bright= true;
      */
      /*
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
      */
      }}
