#include <string.h>
#include <mm_malloc.h>

short bin_str_to_short(const char binary[])
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

int short_to_bin_str(short d, char* buffer, size_t lenght) {
    if (!buffer) return -1;
    if (lenght != 16 + 1) return -1;
    unsigned short value = (unsigned short)d;
    for (short i = 15; i >= 0; i--)
        buffer[15 - i] = ((value >> i) & 1) ? '1' : '0';
    buffer[16] = '\0';
    return 0;
}
