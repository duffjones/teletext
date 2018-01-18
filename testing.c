#include "testing.h"
boolean test_frontcolor(void);

void testFunction(){
  printf("TESTING TEST FILE\n" );
}





void testMain(){

printf("TESTING FLAG INITIALIZATION (Base States):\n\n" );
printf("TESTING FRONT COLOR...%25s\n",testResult(fcolor_test_i()));
printf("TESTING BACK COLOR....%25s\n",testResult(bcolor_test_i()));
printf("TESTING FONTSIZE......%25s\n",testResult(fsize_test_i()));
printf("TESTING MODE..........%25s\n",testResult(mode_test_i()));
printf("TESTING HOLD..........%25s\n",testResult(hold_test_i()));

printf("\n\nTESTING FILE MANAGEMENT:\n\n" );
printf("TESTING ARGC..........%25s\n",testResult(argc_test()));
printf("TESTING FILE OPEN.....%25s\n",testResult(fp_test()));
printf("TESTING 1000 CODES....%25s\n",testResult(codes_test_num(1000)));
printf("TESTING 900 CODES(=FAIL)%25s\n",testResult(codes_test_num(900)));
printf("TESTING 1200 CODES....%25s\n",testResult(codes_test_num(1200)));

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


/*Changed Flags Testing*/

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

boolean codes_test_num(codenumber)
{
  return (testCodes(codenumber));
}







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
