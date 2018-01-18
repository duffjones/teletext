#include "testing.h"
boolean test_frontcolor(void);

void testFunction(){
  printf("TESTING TEST FILE\n" );
}





void testMain(){

  printf("\n\nTESTING FILE MANAGEMENT:\n\n" );
  printf("ARGC..................%25s\n",testResult(argc_test()));
  printf("FILE OPEN.............%25s\n",testResult(fp_test()));
  printf("1000 CODES............%25s\n",testResult(codes_test_num(1000)));
  printf("900 CODES(should fail)%25s\n",testResult(codes_test_num(900)));
  printf("1200 CODES............%25s\n",testResult(codes_test_num(1200)));

   printf("\n\nFLAG INITIALIZATION (Base States):\n\n" );
   printf("FRONT COLOR...%25s\n",testResult(fcolor_test_i()));
   printf("BACK COLOR....%25s\n",testResult(bcolor_test_i()));
   printf("FONTSIZE......%25s\n",testResult(fsize_test_i()));
   printf("MODE..........%25s\n",testResult(mode_test_i()));
   printf("HOLD..........%25s\n",testResult(hold_test_i()));

   printf("\n\nTESTING FLAG CHANGES:\n\n" );
   printf("SET CELLS FROM FLAGS..%25s\n",testResult(setCell_test()));


   printf("\n\nTESTING FLAG CODES:\n\n" );
   printf("Alphanumeric color settings\n" );
   printf("This checks codes are functioning, and flags are saving,\n" );
   printf("states properly -- also tests modes and background setting:\n\n" );
   printf("YELLOWF...%25s\n",testResult(setFlags_yellowf_test()));
   printf("REDF......%25s\n",testResult(setFlags_redf_test()));
   printf("BLUEF.....%25s\n",testResult(setFlags_bluef_test()));
   printf("MAGENTAF..%25s\n",testResult(setFlags_magentaf_test()));
   printf("CYANF.....%25s\n",testResult(setFlags_cyanf_test()));
   printf("WHITEF....%25s\n",testResult(setFlags_whitef_test()));
   printf("GREENF....%25s\n",testResult(setFlags_greenf_test()));

   printf("\nGraphics color settings\n" );
   printf("All 7 tested at once since other flags were tested above \n\n" );
   printf("GRAPHICS COLOR%25s\n",testResult(setFlags_colorg_test()));

   printf("\nTesting handling of incompatible codes\n");
    printf("\nCHECK CHAR FUNCTION%25s\n",testResult(checkChar_test()));


}




char* testResult(bool b){
   char* string;
   if (b == 1){
      string = "PASS";
   }
   else{
      string = "FAIL";
   }
return string;
}


/* TESTING FOR BASE STATE FLAGS*/
/* changeFlags() function*/
boolean fcolor_test_i(void)
{
  flags flag;
  changeFlags(&flag);
  return (flag.frontcolor == white);
}

boolean bcolor_test_i(void)
{
  flags flag;
  changeFlags(&flag);
  return (flag.backcolor == black);
}

boolean fsize_test_i(void)
{
  flags flag;
  changeFlags(&flag);
  return (flag.fontsize == normalfont);
}

boolean mode_test_i(void)
{
  flags flag;
  changeFlags(&flag);
  return (flag.mode == alphanumeric);
}

boolean hold_test_i(void)
{
  flags flag;
  changeFlags(&flag);
  return (flag.hold == release);
}


/*TEST FILE HANDLING AND IMPORT CODES*/
boolean argc_test(void)
{
  testArgC(2);
  return (1);
}

boolean fp_test(void)
{
  bool tf;
  FILE *fp = fopen("test.m7", "rb");
  tf = testFile(fp);
  fclose(fp);
  return (tf);
}

boolean checkChar_test(void){

unsigned char testchar;
unsigned char checkedchar;
   testchar = 0x05;
   checkedchar = checkChar(testchar);

   if(checkedchar != BLANK - DIFF ){
     return 0;
   }
  printf("0x05 Passed\n" );
  testchar = 0x35;
  checkedchar = checkChar(testchar);

  if(checkedchar != testchar ){
    return 0;
  }
   printf("0x35 Passed\n" );
   testchar = a5;
   checkedchar = checkChar(testchar);

   if(checkedchar != testchar - DIFF ){
        return 0;
   }
   printf("0xA5 Passed\n" );
  return(1);
}







boolean codes_test_num(int codenumber)
{
  return (testCodes(codenumber));
}

boolean setCell_test(void)
{
  flags current;
  cell test;
  flags testflags;

     current.frontcolor = blue;
     current.backcolor = red;
     current.fontsize = doubleheight;
     current.mode = contiguous;
     current.hold = hold;
     setCellFlags(&test, &current);
     testflags.frontcolor = test.flag.frontcolor;

  return (testflags.frontcolor == blue);
}

/*SET FLAGS TESTS*/
/*Testing function that sets draw color, and respective flags*/

boolean setFlags_yellowf_test(){
flags c;
setFlags(yellowf, &c);
setFlags(bgnew, &c);
return (c.backcolor == yellow
  && c.frontcolor == yellow
  && c.mode == alphanumeric);
}

boolean setFlags_bluef_test(){
  flags c;
  setFlags(bluef, &c);
  setFlags(bgnew, &c);
  return (c.backcolor == blue
    && c.frontcolor == blue
    && c.mode == alphanumeric);
}
boolean setFlags_redf_test(){
  flags c;
  setFlags(redf, &c);
  setFlags(bgnew, &c);
  return (c.backcolor == red
    && c.frontcolor == red
    && c.mode == alphanumeric);
}
boolean setFlags_magentaf_test(){
  flags c;
  setFlags(magentaf, &c);
  setFlags(bgnew, &c);
  return (c.backcolor == magenta
    && c.frontcolor == magenta
    && c.mode == alphanumeric);
}
boolean setFlags_cyanf_test(){
  flags c;
  setFlags(cyanf, &c);
  setFlags(bgnew, &c);
  return (c.backcolor == cyan
    && c.frontcolor == cyan
    && c.mode == alphanumeric);
}
boolean setFlags_whitef_test(){
  flags c;
  setFlags(whitef, &c);
  setFlags(bgnew, &c);
  return (c.backcolor == white
    && c.frontcolor == white
    && c.mode == alphanumeric);
}
boolean setFlags_greenf_test(){
  flags c;
  setFlags(greenf, &c);
  setFlags(bgnew, &c);
  return (c.backcolor == green
    && c.frontcolor == green
    && c.mode == alphanumeric);
}

boolean setFlags_colorg_test(){
  flags c;

  setFlags(yellowg, &c);
  if(c.frontcolor != yellow){
    return 0;
  }
  printf("Yellow Passed\n" );
  setFlags(redg, &c);
  if(c.frontcolor != red){
    return 0;
  }
  printf("Red Passed\n" );
  setFlags(greeng, &c);
  if(c.frontcolor != green){
    return 0;
  }
  printf("green Passed\n" );
  setFlags(blueg, &c);
  if(c.frontcolor != blue){
    return 0;
  }
  printf("Blue Passed\n" );
  setFlags(magentag, &c);
  if(c.frontcolor != magenta){
    return 0;
  }
  printf("Magenta Passed\n" );
  setFlags(cyang, &c);
  if(c.frontcolor != cyan){
    return 0;
  }
  printf("Cyan Passed\n" );
  setFlags(whiteg, &c);
  if(c.frontcolor != white){
    return 0;
  }
  printf("White Passed\n" );

    return 1;



}










/*
NEED TO MAKE FOR:

setDrawColor(sw, hex[h][w].flag.backcolor);

DrawSixel

SDL_DrawTopChar

SDL_DrawBottomChar

SDL_DrawChar

checkChar

setHold() + flags
hex[h][w].code > a0 && hex[h][w].code<=bf)|| hex[h][w].code >= e0
*/





/*Practical Testing for main() in TELET.C */

boolean testCodes(int test){
  if ( test < 1000){
    printf("You have entered %d codes, should be 1000\n",test );
    return false;
  }
  else
  {
    return true;
  }
}

boolean testFile(FILE *fp){
if (fp == NULL)
 {
    ON_ERROR("unable to open file:\nCheck filename and path.\n");
 }
 return (fp != NULL);
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
}}

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
