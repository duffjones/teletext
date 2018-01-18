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
