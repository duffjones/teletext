#include "sixel.h"

#define ON_ERROR(STR) perror("ERROR: " STR);exit(EXIT_FAILURE)

typedef enum tester {
  fail   = 0,
  pass   = 1
}tester;


void testCodeDisplay(cell hex[25][40]);
boolean testCodes(int test);
char* testResult(bool b);
boolean fcolor_test_i(void);
boolean bcolor_test_i(void);
boolean fsize_test_i(void);
boolean mode_test_i(void);
boolean hold_test_i(void);

boolean testFile(FILE *fp);
boolean fp_test(void);
boolean argc_test(void);
boolean codes_test_num(codenumber);
boolean setCell_test(void);

void testMain();
void testArgC(int argc);

boolean setFlags_yellowf_test();
boolean setFlags_bluef_test();
boolean setFlags_redf_test();
boolean setFlags_magentaf_test();
boolean setFlags_cyanf_test();
boolean setFlags_whitef_test();
boolean setFlags_greenf_test();

boolean setFlags_colorg_test();
boolean checkChar_test(void);

boolean setFlags_singleheight_test();
boolean setFlags_doubleheight_test();
boolean setFlags_holdg_test();
boolean setFlags_releaseg_test();
boolean setFlags_contg_test();
boolean setFlags_sepg_test();
