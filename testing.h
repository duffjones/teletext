#include "telet.h"

#define ON_ERROR(STR) perror("ERROR: " STR);exit(EXIT_FAILURE)
#define PRINT_RESULT(STR, FUNC) printf("%-30s%20s\n",STR, FUNC)
#define NEW_LINE printf("\n" );
#define DIVIDE  printf("---------------------------------------------------\n\n" );

typedef enum tester {
  fail   = 0,
  pass   = 1
}tester;



void testMain();
void testArgC(int argc);
void testCodeDisplay(cell hex[25][40]);

char* testResult(bool b);

boolean fcolor_test_i(void);
boolean bcolor_test_i(void);
boolean fsize_test_i(void);
boolean mode_test_i(void);
boolean hold_test_i(void);
boolean fp_test(void);
boolean argc_test(void);
boolean setCell_test(void);
boolean checkChar_test(void);

boolean testCodes(int test);
boolean testRandomCodes();
boolean codes_test_num(int codenumber);

boolean setFlags_yellowf_test();
boolean setFlags_bluef_test();
boolean setFlags_redf_test();
boolean setFlags_magentaf_test();
boolean setFlags_cyanf_test();
boolean setFlags_whitef_test();
boolean setFlags_greenf_test();

boolean setFlags_singleheight_test();
boolean setFlags_doubleheight_test();
boolean setFlags_holdg_test();
boolean setFlags_releaseg_test();
boolean setFlags_contg_test();
boolean setFlags_sepg_test();

boolean setFlags_colorg_test();
