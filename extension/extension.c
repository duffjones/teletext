#include "extension.h"

int main(int argc, char * * argv) {
   flags current;
   cell hex[HT][WT];

   printf("PROGRAM STARTING!\n");
   importCodes(argv[1], hex); /* Imports 1000 codes from ARGV1 into array of cell structs */
   testFunction(argc, argv[2], hex); /* Initializes testing from ARGV */
   printHex(hex, & current);
   return 0;
}



/*Prints HTML to file based on different flags and graphics types. */
/*Due to the nature of html this is lengthier than we would otherwise like in a C program*/
/*All 'magic' numbers written in fprintf are adjustments of the label referring to them. These adjustments mirror the formatting of SDL*/
void printHex(cell hex[25][40], flags * current) {
   int w, h;
   sixels sixel;
   FILE * file = fopen("testhtml.txt", "w");

   /*Sets up our table in HTML*/
   fprintf(file, "<table style=\"color: white; font-size: 14pt; width: 5%%;cellspacing=\"0\" cellpadding=\"0\";\" bgcolor=\"#000000\">\n");
   fprintf(file, "<tbody>");

   for (h = 0; h < HT; h++) {
      changeFlags(current);
      fprintf(file, "<tr>\n");
      for (w = 0; w < WT; w++) {
         setFlags(hex[h][w].code, current);
         setCellFlags( & hex[h][w], current);
         setHold( & hex[h][w]);

         /*Checks for Graphics flag and prints a sixel with <rect> and <svg>*/
         if (hex[h][w].flag.mode == contiguous &&
            ((hex[h][w].code > a0 && hex[h][w].code <= bf) || hex[h][w].code >= e0)) {
            htmlSixel( & hex[h][w], sixel, file);
         } else if (hex[h][w].flag.mode == separate &&
            ((hex[h][w].code > a0 && hex[h][w].code <= bf) || hex[h][w].code >= e0)) {
            fprintf(file, "   <td><svg width=\"10\" height=\"12\"><rect width=\"10\" height=\"12\" style=\"fill:%s;\" /> </svg> </td>\n", colorEnum(hex[h][w].flag.frontcolor));
         }
         /*Writes double sized font by adjusting font size, and printing one line, while replacing the second with blank spaces */
         /* Linear gradient is used to split the background of our doublesize letters, mixing backcolor and backcolor of the above cell*/
         else if (h > 2 && hex[h - 1][w].flag.fontsize == topfont) {
            current -> fontsize = bottomfont;
            fprintf(file, "   <td style=\" background-image: linear-gradient(to top, %s, %s 50%%, %s 50%%, %s); height: 18; font-size: 28px; color: %s;\">%c</td>\n",
               colorEnum(hex[h][w].flag.backcolor), colorEnum(hex[h][w].flag.backcolor),
               colorEnum(hex[h - 1][w].flag.backcolor), colorEnum(hex[h - 1][w].flag.backcolor),
               colorEnum(hex[h][w].flag.frontcolor), hex[h][w].code - DIFF);
         } else if (hex[h][w].flag.fontsize == topfont || hex[h][w].code == 0x86) {
            fprintf(file, "<td></td>\n");
         } else if (hex[h][w].flag.fontsize == normalfont) {
            fprintf(file, "   <td style=\"color: %s; background-color: %s;\">%c</td>\n",
               colorEnum(hex[h][w].flag.frontcolor), colorEnum(hex[h][w].flag.backcolor), hex[h][w].code - DIFF);
         }
      }
      fprintf(file, "</tr>\n");
   }
   fprintf(file, "</tbody>");
   fprintf(file, "</table>");

   fclose(file);
}

void htmlSixel(cell * hex, sixels sixel, FILE * file) {
   setSixels(hex -> code, & sixel);
   fprintf(file, "  <td>\n <svg width=\"16\" height=\"18\">\n");

   if (sixel.uleft == true) {
      fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"0\" y=\"0\" style=\"fill:%s;\"/>\n", colorEnum(hex -> flag.frontcolor));
   } else {
      fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"0\" y=\"0\" style=\"fill:%s;\"/>\n", colorEnum(hex -> flag.backcolor));
   }
   if (sixel.uright == true) {
      fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"8\" y=\"0\" style=\"fill:%s;\"/>\n", colorEnum(hex -> flag.frontcolor));
   } else {
      fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"8\" y=\"0\" style=\"fill:%s;\"/>\n", colorEnum(hex -> flag.backcolor));
   }
   if (sixel.mleft == true) {
      fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"0\" y=\"6\" style=\"fill:%s;\"/>\n", colorEnum(hex -> flag.frontcolor));
   } else {
      fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"0\" y=\"6\" style=\"fill:%s;\"/>\n", colorEnum(hex -> flag.backcolor));
   }
   if (sixel.mright == true) {
      fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"8\" y=\"6\" style=\"fill:%s;\"/>\n", colorEnum(hex -> flag.frontcolor));
   } else {
      fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"8\" y=\"6\" style=\"fill:%s;\"/>\n", colorEnum(hex -> flag.backcolor));
   }
   if (sixel.bleft == true) {
      fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"0\" y=\"12\" style=\"fill:%s;\"/>\n", colorEnum(hex -> flag.frontcolor));
   } else {
      fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"0\" y=\"12\" style=\"fill:%s;\"/>\n", colorEnum(hex -> flag.backcolor));
   }
   if (sixel.bright == true) {
      fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"8\" y=\"12\" style=\"fill:%s;\"/>\n", colorEnum(hex -> flag.frontcolor));
   } else {
      fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"8\" y=\"12\" style=\"fill:%s;\"/>\n", colorEnum(hex -> flag.backcolor));
   }
   fprintf(file, "</svg>\n   </td>\n");
   resetSixels( & sixel);
}

/*changes our typedef color into a string to be printed into HTML*/
const char * colorEnum(enum color color) {
   switch (color) {
   case red:
      return "red";
   case blue:
      return "blue";
   case yellow:
      return "yellow";
   case green:
      return "green";
   case cyan:
      return "cyan";
   case magenta:
      return "magenta";
   case white:
      return "white";
   case black:
      return "black";
   default:
      return "black";
   }
}
