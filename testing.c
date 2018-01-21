#include "testing.h"
boolean test_frontcolor(void);

void testMain() {

    printf("\n\nTESTING FILE MANAGEMENT:\n" );
    DIVIDE;
    PRINT_RESULT("ARGC", testResult(argc_test()));
    PRINT_RESULT("FILE OPEN", testResult(fp_test()));
    PRINT_RESULT("Import 1000 Codes",  testResult(codes_test_num(1000)));
    PRINT_RESULT("Import 900 Codes",  testResult(codes_test_num(900)));
    PRINT_RESULT("Import 1200 Codes", testResult(codes_test_num(1200)));

    printf("\n\nFLAG INITIALIZATION (Base States):\n" );
    DIVIDE;
    PRINT_RESULT("FRONT COLOR", testResult(fcolor_test_i()));
    PRINT_RESULT("BACK COLOR", testResult(bcolor_test_i()));
    PRINT_RESULT("FONTSIZE", testResult(fsize_test_i()));
    PRINT_RESULT("MODE", testResult(mode_test_i()));
    PRINT_RESULT("HOLD", testResult(hold_test_i()));

    printf("\nTESTING FLAG CHANGES:\n" );
    DIVIDE;
    PRINT_RESULT("SET CELLS FROM FLAGS..", testResult(setCell_test()));

    printf("\nTESTING FLAG CODES:\n" );
    DIVIDE;
    printf("Alphanumeric color settings\n" );
    printf("This checks codes are functioning, and flags are saving,\n" );
    printf("states properly -- also tests modes and background setting:\n" );
    PRINT_RESULT("YELLOWF", testResult(setFlags_yellowf_test()));
    PRINT_RESULT("redF", testResult(setFlags_redf_test()));
    PRINT_RESULT("blueF", testResult(setFlags_bluef_test()));
    PRINT_RESULT("magentaF", testResult(setFlags_magentaf_test()));
    PRINT_RESULT("cyanF", testResult(setFlags_cyanf_test()));
    PRINT_RESULT("whiteF", testResult(setFlags_whitef_test()));
    PRINT_RESULT("greenF", testResult(setFlags_greenf_test()));

    printf("\nTesting Control Codes\n");
    DIVIDE;
    PRINT_RESULT("SINGLE HEIGHT", testResult(setFlags_singleheight_test()));
    PRINT_RESULT("DOUBLE HEIGHT", testResult(setFlags_doubleheight_test()));
    PRINT_RESULT("HOLD GRAPHICS", testResult(setFlags_holdg_test()));
    PRINT_RESULT("RELEASE GRAPHICS", testResult(setFlags_releaseg_test()));
    PRINT_RESULT("CONTIGUOUS GRAPHICS", testResult(setFlags_contg_test()));
    PRINT_RESULT("SEPARATE GRAPHICS", testResult(setFlags_sepg_test()));

    printf("\nGraphics color settings\n" );
    DIVIDE;
    printf("All 7 tested at once since other flags were tested above \n\n" );
    PRINT_RESULT("GRAPHICS COLOR", testResult(setFlags_colorg_test()));

    printf("\nTesting handling of incompatible codes\n");
    DIVIDE;
    PRINT_RESULT("CHECK CHAR FUNCTION", testResult(checkChar_test()));
    printf("\nSecond Test File for checking coords/import accuracy\n");
    PRINT_RESULT("CHECK RANDOM CODES", testResult(testRandomCodes()));


    printf("\nFURTHER TESTING\n");
    DIVIDE;
    printf("--Open file testfile/sixelchart.m7 to test sixels.\n");
    printf("--Open file test.m7 and test2.m7 to test see broad testing.\n");
    printf("--Run printhex as second argument to print hex and alpha code array to terminal.\n");
}

void testFunction(int argc, char *command, cell hex[HT][WT]) {

    testArgC(argc);
    if(argc == MAXARG) {
        if (strcmp(command, "test") == 0) {
            testMain();
        }

        else if (strcmp(command, "printhex") == 0) {
            testCodeDisplay(hex);
            printf("--Run test as second argument to view testing results.\n");
        }
        else {
            ON_ERROR("ARGV 2 is invalid. Did you mean to call: test or printhex?");
        }
    }
}
char* testResult(bool b) {
    char* string;
    if (b == 1) {
        string = "PASS";
    }
    else {
        string = "FAIL";
    }
    return string;
}


void testArgC(int argc) {
    if ( argc < 2 || argc>3 )  {
        ON_ERROR("Requires 2 or 3 Arguments: ");
    }
}


boolean codes_test_num(int codenumber)
{
    return (testCodes(codenumber));
}

/*Practical Testing for main() in TELET.C */
boolean testCodes(int test) {
    if ( test < 1000) {
        printf("You have entered %d codes, should be 1000\n",test );
        return false;
    }
    else
    {
        return true;
    }
}

boolean testFile(FILE *fp) {
    if (fp == NULL)
    {
        ON_ERROR("unable to open file:\nCheck filename and path.\n");
    }
    return (fp != NULL);
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

boolean checkChar_test(void) {

    unsigned char testchar;
    unsigned char checkedchar;
    testchar = 0x05;
    checkedchar = checkChar(testchar);

    if(checkedchar != BLANK - DIFF ) {
        return 0;
    }

    printf("...0x05 Passed\n" );
    testchar = 0x35;
    checkedchar = checkChar(testchar);

    if(checkedchar != testchar ) {
        return 0;
    }

    printf("...0x35 Passed\n" );
    testchar = a5;
    checkedchar = checkChar(testchar);

    if(checkedchar != testchar - DIFF ) {
        return 0;
    }
    printf("...0xA5 Passed\n" );
    return(1);
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
boolean setFlags_yellowf_test() {
    flags c;
    setFlags(yellowf, &c);
    setFlags(bgnew, &c);
    return (c.backcolor == yellow
            && c.frontcolor == yellow
            && c.mode == alphanumeric);
}

boolean setFlags_bluef_test() {
    flags c;
    setFlags(bluef, &c);
    setFlags(bgnew, &c);
    return (c.backcolor == blue
            && c.frontcolor == blue
            && c.mode == alphanumeric);
}
boolean setFlags_redf_test() {
    flags c;
    setFlags(redf, &c);
    setFlags(bgnew, &c);
    return (c.backcolor == red
            && c.frontcolor == red
            && c.mode == alphanumeric);
}
boolean setFlags_magentaf_test() {
    flags c;
    setFlags(magentaf, &c);
    setFlags(bgnew, &c);
    return (c.backcolor == magenta
            && c.frontcolor == magenta
            && c.mode == alphanumeric);
}
boolean setFlags_cyanf_test() {
    flags c;
    setFlags(cyanf, &c);
    setFlags(bgnew, &c);
    return (c.backcolor == cyan
            && c.frontcolor == cyan
            && c.mode == alphanumeric);
}
boolean setFlags_whitef_test() {
    flags c;
    setFlags(whitef, &c);
    setFlags(bgnew, &c);
    return (c.backcolor == white
            && c.frontcolor == white
            && c.mode == alphanumeric);
}
boolean setFlags_greenf_test() {
    flags c;
    setFlags(greenf, &c);
    setFlags(bgnew, &c);
    return (c.backcolor == green
            && c.frontcolor == green
            && c.mode == alphanumeric);
}

/*GRAPHICS COLOR TESTS*/
/*Quick test that all graphics are loading into flags*/
boolean setFlags_colorg_test() {
    flags c;

    setFlags(yellowg, &c);
    if(c.frontcolor != yellow) {
        return 0;
    }
    printf("...Yellow Passed\n" );
    setFlags(redg, &c);
    if(c.frontcolor != red) {
        return 0;
    }
    printf("...Red Passed\n" );
    setFlags(greeng, &c);
    if(c.frontcolor != green) {
        return 0;
    }
    printf("...green Passed\n" );
    setFlags(blueg, &c);
    if(c.frontcolor != blue) {
        return 0;
    }
    printf("...Blue Passed\n" );
    setFlags(magentag, &c);
    if(c.frontcolor != magenta) {
        return 0;
    }
    printf("...Magenta Passed\n" );
    setFlags(cyang, &c);
    if(c.frontcolor != cyan) {
        return 0;
    }
    printf("...Cyan Passed\n" );
    setFlags(whiteg, &c);
    if(c.frontcolor != white) {
        return 0;
    }
    printf("...White Passed\n\n" );

    return 1;
}


/*SET FLAGS TESTS*/
/*Height and Hold settings*/
boolean setFlags_singleheight_test() {
    flags c;
    setFlags(singleheight, &c);
    return (c.fontsize == normalfont);
}

boolean setFlags_doubleheight_test() {
    flags c;
    setFlags(doubleheight, &c);
    return (c.fontsize == topfont);
}

boolean setFlags_holdg_test() {
    flags c;
    setFlags(holdg, &c);
    return (c.hold == hold);
}

boolean setFlags_releaseg_test() {
    flags c;
    setFlags(releaseg, &c);
    return (c.hold == release);
}

boolean setFlags_contg_test() {
    flags c;
    setFlags(contg, &c);
    return (c.mode == contiguous);
}

boolean setFlags_sepg_test() {
    flags c;
    setFlags(sepg, &c);
    return (c.mode == separate);
}

/*
NEED TO MAKE FOR:
FRIDAY
creating hexfile from array
redundant sixel function removal with ints
*/

boolean testRandomCodes() {


    cell hex[HT][WT];
    importCodes("testfiles/test2.m7", hex);

    return ( hex[0][0].code == b1 &&
             hex[9][0].code == b1 &&
             hex[24][0].code == b1 &&
             hex[0][24].code == b2);
}

void testCodeDisplay(cell hex[25][40]) {
    int  w, h;
    w = 0;
    h = 0;
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
            if(hex[h][w].code <= a0 || hex[h][w].code >= 0xff) {
                printf("%x", hex[h][w].code);
            }
            else {
                printf("%c ", hex[h][w].code -DIFF );
            }
        }
        printf("\n" );
    }
}
