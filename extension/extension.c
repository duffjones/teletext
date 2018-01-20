#include "extension.h"

void printHex(cell hex[25][40]);


int main(int argc, char **argv)
{
  flags current;
  cell hex[HT][WT];


  printf("BEGINNING PROGRAM!\n" );

  importCodes(argv[1], hex); /* Imports 1000 codes from ARGV1 into array of cell structs */
  testFunction(argc, argv[2], hex); /* Initializes testing from ARGV */
  printHex(hex);

}



void printHex(cell hex[25][40]){
  int  w, h;
  FILE *file  = fopen("testhtml.m7", "w");
  w = 0;h = 0;

  fprintf(file, "<table style=\"color: white; font-size: 10pt; width: 5%%;\" bgcolor=\"#000000\">\n");
  fprintf(file, "<tbody>");

          for (h = 0; h < HT; h++) {
             printf("<tr>\n" );
             fprintf(file, "<tr>\n");
             for (w = 0; w < WT; w++) {
                 if(hex[h][w].code <= a0 || hex[h][w].code >= 0xff){
                 printf("   <td>  </td>\n", hex[h][w].code);
                 fprintf(file, "   <td>  </td>\n",hex[h][w].code );
                  }
                 else {
                     printf("   <td>%c</td>\n", hex[h][w].code -DIFF );
                     fprintf(file, "   <td>%c</td>\n",hex[h][w].code - DIFF );
                      }
            }
        printf("</tr>\n" );
        fprintf(file, "</tr>\n");
}
  fprintf(file, "</tbody>");
  fprintf(file, "</table>");

fclose(file);
}
