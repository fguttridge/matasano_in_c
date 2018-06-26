#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "converters.h"

/* Returns true iff each character of "s" is alphabetic or numeric. */
int str_isalnum(char * s) {
  int i=0, len=strlen(s);
  // Added a slight handicap here to account for noise appended to end of string
  // Should fix this at a later point
  for (i=0; i<len - 2; i++) {
    if (!(isalnum(s[i]) || (s[i] == ' ') || (s[i] == '\''))) return 0; /* false */
  }
  return 1; /* true */
}


int main(int argc, char* argv[])
{
    char const* const fileName = argv[1]; /* should check that argc > 1 */
    FILE* file = fopen(fileName, "r"); /* should check the result */
    char line[60];
    char *lineBytes;
    char lineResult[60];

    int ascii = 256;

    while (fgets(line, sizeof(line), file)) {
        printf("----------------------------- New Line -----------------------------\n");
        line[strlen(line)] = "\0";
        lineBytes = hex2ByteArray(line);
        for (int j = 0; j < ascii; j++) {
            for (int i = 0; i < strlen(lineBytes); i++) {
                lineResult[i] = lineBytes[i] ^ j;
            }
            if(isalnum(lineResult[0]) && str_isalnum(lineResult) && strlen(lineResult) > 4) {
                printf("decoded for %d: %s\n", j, lineResult);
            }
        }
        
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        printf("original: %s\n", line);
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);
    printf("\n");
    return 0;
}

// The result appears to be:
// Now that the party is jumping
// Ecoded using ascii 55 or { 7 }
// original string: 7b5a4215415d544115415d5015455447414c155c46155f4058455c5b523

