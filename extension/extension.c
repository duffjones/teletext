#include "extension.h"

void printHex(cell hex[25][40], flags* current);
const char* colorEnum(enum color color);

int main(int argc, char **argv)
{
  flags current;
  cell hex[HT][WT];


  printf("BEGINNING PROGRAM!\n" );

  importCodes(argv[1], hex); /* Imports 1000 codes from ARGV1 into array of cell structs */
  testFunction(argc, argv[2], hex); /* Initializes testing from ARGV */
  printHex(hex, &current);


printf("ENUM TRANSLATOR%s\n",colorEnum(red) );



}






void printHex(cell hex[25][40], flags* current){
  int  w, h;
  FILE *file  = fopen("testhtml.m7", "w");
  w = 0;h = 0;

  fprintf(file, "<table style=\"color: white; font-size: 14pt; width: 5%%;\" bgcolor=\"#000000\">\n");
  fprintf(file, "<tbody>");

          for (h = 0; h < HT; h++) {
            changeFlags(current);
             printf("<tr>\n" );
             fprintf(file, "<tr>\n");
             for (w = 0; w < WT; w++) {
               setFlags(hex[h][w].code, current);
               setCellFlags(&hex[h][w], current);
               setHold(&hex[h][w]);

                 if(hex[h][w].code <= a0 || hex[h][w].code >= 0xff){
                 printf("   <td>  </td>\n", hex[h][w].code);
                 fprintf(file, "   <td>  </td>\n",hex[h][w].code );
                  }

                 else {
                     printf("   <td bgcolor=\"%s\">%c</td>\n", colorEnum(hex[h][w].flag.backcolor), hex[h][w].code -DIFF );
                     fprintf(file, "   <td style=\"color: %s; background-color: %s;\">%c</td>\n", colorEnum(hex[h][w].flag.frontcolor) , colorEnum(hex[h][w].flag.backcolor)  , hex[h][w].code - DIFF );
                      }





            }
        printf("</tr>\n" );
        fprintf(file, "</tr>\n");
}
  fprintf(file, "</tbody>");
  fprintf(file, "</table>");

fclose(file);
}

const char* colorEnum(enum color color)
{
   switch (color)
   {
      case red: return "red";
      case blue: return "blue";
      case yellow: return "yellow";
      case green: return "green";
      case cyan: return "cyan";
      case magenta: return "magenta";
      case white: return "white";
      case black: return "black";

   }
}
