#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global constant variable
static const char A = 'A';

struct pkt {
    size_t length;
    char data[];
};

int main(void) {

    printf("Flexible array members are supported from C99 standard. This program is compiled using: %ld\n", __STDC_VERSION__); 

    const char* msg = "Welcome message!";
    size_t msg_length = strlen(msg) + 1;
    struct pkt* packet_ptr = malloc(sizeof(struct pkt) + msg_length);

    packet_ptr->length = msg_length;
    memcpy(packet_ptr->data, msg, msg_length);

    printf("Payload: %s\n", packet_ptr->data);

    return 0;
}