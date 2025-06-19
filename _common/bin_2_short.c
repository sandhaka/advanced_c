#include <string.h>
#include <mm_malloc.h>

short binStrToShort(const char binary[])
{
    if (strlen(binary) != 16) return -1;
    unsigned short d = 0;
    for (short i = 0; i < 16; i++) {
        if (binary[i] == '1')
            d = (d << 1) | 1;
        else if (binary[i] == '0')
            d = d << 1;
        else return -1;
    }

    return (short) d;
}

char* shortToBinStr(short d) {
    char* binary = (char *) malloc(sizeof(char) * 16 + 1);
    if (!binary) return NULL;
    unsigned short value = (unsigned short)d;
    for (short i = 15; i >= 0; i--)
        binary[15 - i] = ((value >> i) & 1) ? '1' : '0';
    binary[16] = '\0';
    return binary;
}
