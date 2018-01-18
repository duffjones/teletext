#include "testing.h"

void testFunction(){
  printf("TESTING TEST FILE\n" );
}

void testCodeDisplay(cell hex[25][40]){
  int  w, h;
  w = 0;h = 0;
  printf("HEX CODES: \n" );
     for (h = 0; h < HT; h++) {
     for (w = 0; w < WT; w++) {
        printf("%x ", hex[h][w].code);
     }
  printf("\n" );
  }
  printf("\n\n" );
  printf("ALPHANUMERIC CODES: \n" );
          for (h = 0; h < HT; h++) {
            for (w = 0; w < WT; w++) {
              if(hex[h][w].code <= a0 || hex[h][w].code >= 0xff){
                printf("%x", hex[h][w].code);
              }
                else {
                  printf("%c ", hex[h][w].code -128 );
                    }
      }
        printf("\n" );
}
}

void testCodes(int test){
  if ( test < 1000){
    printf("You have entered %d codes, should be 1000\n",test );
    ON_ERROR("Wrong number of HEX codes");
  }
   else
   {
     printf("You have %d codes\n", test );
   }
}
void testArgC(int argc){
  if ( (argc != 2) )  {
    ON_ERROR("Requires 2 Arguments: ");
  }
}
void testValue(int value, int compare){

  if (value == compare)
   {
      ON_ERROR("unable to open file:\nCheck filename and path.\n");
   }

}
