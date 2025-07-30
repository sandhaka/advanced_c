#include <stdio.h>
#include <stdint.h>

typedef union {
    float f;
    uint32_t u;
} Data;

int main() {
    Data data;
    data.f = 3.14f;
    data.u = *(uint32_t*)&data.f;

    printf("Float: %f\n", data.f);
    printf("Bits pattern of float value: 0x%08X\n", data.u);

    return 0;
}