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
  for (i=0; i<len - 10; i++) {
    if (!(isalnum(s[i]) || (s[i] == ' ') || (s[i] == '\''))) return 0; /* false */
  }
  return 1; /* true */
}

int main(void) {
    const char digest[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    char binaryResult[sizeof(digest) / 2];
    char hexResult[sizeof(digest)];
    int count = 0;
    int character = 128; // All ascii characters here
    char *digestBytes = hex2ByteArray(digest);
    while(character > 0) {
        for (count = 0; count < strlen(digestBytes); count++) {
            binaryResult[count] = digestBytes[count] ^ character;
        }
        if(str_isalnum(binaryResult)){
            printf("The result for character %d is: %s\n", character, binaryResult);
        }
        character--;
    }
}

// Note: Seems to be ascii 88 yields result: 
// Cooking MC's like a pound of bacon?+?
// This indicates that X is the xor value