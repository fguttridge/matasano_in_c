#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "converters.h"

int main(void) {
    char x1[] = "1c0111001f010100061a024b53535009181c";
    char x2[] = "686974207468652062756c6c277320657965";
    int count;

    char *binx1 = hex2ByteArray(x1);
    char *binx2 = hex2ByteArray(x2);

    char xorResult[(sizeof(x1) / 2) + 1];
    
    for(count = 0; count < (sizeof(x1) / 2); count++) {
        xorResult[count] = binx1[count] ^ binx2[count];
    }
    // Append null terminator for strlen accuracy
    xorResult[18] = '\0';

    char *finalResult = byteArray2Hex(xorResult);
    printf("%s\n", finalResult);

    free(finalResult);


    // 746865206B696420646F6E277420706C6179
    // 746865206b696420646f6e277420706c6179

}