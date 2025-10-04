#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

short b = 0;

void local_handler(int sig) {
    printf("Signal received:  %d", sig);
    b = 1;
}

int main(void) {
    void (*sigHandlerRet)(int);
    sigHandlerRet = local_handler;
    signal(SIGINT, sigHandlerRet);
    // Continue until the SIGINT get cought
    while(b == 0) { sleep(1); }
    return 0;
}
