#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "converters.h"

void get_b64_quads(char *hex, char *b64quads, int pad)
{
  char *dec_2_base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  char b1 = hex[0] >> 2;
  char b2 = ((hex[0] & 0x03) << 4) + (hex[1] >> 4);
  char b3 = ((hex[1] & 0x0f) << 2) + (hex[2] >> 6);
  char b4 = hex[2] & 0x3f;

  b64quads[0] = dec_2_base64[b1];
  b64quads[1] = dec_2_base64[b2];
  b64quads[2] = pad == 1 && !b3 ? '=' : dec_2_base64[b3];
  b64quads[3] = pad && !b4 ? '=' : dec_2_base64[b4];

  return;
}

char* hex2ByteArray( char *_hex ) {
    int hexSize = strlen(_hex);
    if (!hexSize) {
        printf("Could not compute the size of the input");
        return NULL;
    }
    if (hexSize % 2 != 0) {
        printf("The size of the input is not a multiple of 2");
        return NULL;
    }
    
    //remove whitespaces from hex string
    char *moveto = NULL;
    char *p = _hex;
    while (*p)
    {
        if (*p == ' ')
        {
            if (moveto == NULL)
                moveto = p;
            }
            else
            {
                if (moveto)
                {
                    memmove(moveto, p, strlen(p) + 1);
                    moveto = NULL;
                }
            }
        p++;
    }

    int bytearray_size = hexSize / 2; //each pair of hex chars is a byte
    char *bytearray = malloc(bytearray_size);
    p = _hex;
    char *bytearray_p = bytearray;
    char hexbytebuffer[3] = { 0 };
    int temp = hexSize;
    int ibytearray = 0;
    while (temp > 0)
    {
        memcpy(hexbytebuffer, p, 2);
        bytearray[ibytearray] = strtol(hexbytebuffer, NULL, 16);
        ibytearray++;
        p += 2;
        temp -= 2;
    }
    return bytearray;  
}

char* byteArray2B64(char *_byteArray){
      //allocate memory for base64 output (must be freed by whoever calls this function)
  int b64length = ((strlen(_byteArray))  / 3); //each 3 hex bytes will become 4 base64 chars
  char *base64 = malloc(b64length + 1);
  memset(base64, 0, b64length + 1);

  //walk through byte array, converting each 3 bytes to 4 base64 characters
  int temp = strlen(_byteArray);
  char *bytearrayp = _byteArray;
  char bytes[3] = { 0 };
  char b64chars[4] = { 0 };
  char *base64p = base64;
  while (temp > 0)
  {
    if (temp >= 3)
    {
      memcpy(bytes, bytearrayp, 3);
      get_b64_quads(bytes, b64chars, 0);
      temp -= 3;
      bytearrayp += 3;
    }
    else
    {
      //needs to pad with '='
      memset(bytes, 0, 3);
      memcpy(bytes, bytearrayp, temp);
      get_b64_quads(bytes, b64chars, temp);
      temp = 0;
    }
    memcpy(base64p, b64chars, 4);
    base64p += 4;
  }

  free(_byteArray);
  return base64;
}

char *byteArray2Hex(char *_byteArray) {
    int binLength = strlen(_byteArray);
    int count = 0; 
    char *hex = malloc(binLength);
    char *phex = hex;

    while (count < binLength) {
        sprintf(phex, "%02X", (unsigned char)_byteArray[count]);
        phex += 2;
        count++;
    }
    return hex;
}
