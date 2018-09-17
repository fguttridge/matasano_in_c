#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    const char input[] = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal";
    const char key[]= "ICE";

    int size = 0;
    int keyLocation = 0;
    char output[sizeof(input)];

    while(size < sizeof(input)) {
        if(keyLocation > sizeof(key)) {
            keyLocation = 0;
        }
        output[size] = key[keyLocation] ^ input[size];
        keyLocation++;
        size++;
    }
    printf("%s", output);                
}