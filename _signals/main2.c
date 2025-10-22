#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { /* child */
        printf("Child: pid=%d, ppid=%d\n", getpid(), getppid());
        /* do child work */
        sleep(1);
        printf("Child: exiting with code 42\n");
        _exit(42);
    } else { /* parent */
        int status;
        printf("Parent: created child pid=%d\n", pid);
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return 1;
        }
        if (WIFEXITED(status))
            printf("Parent: child exited with status=%d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("Parent: child killed by signal %d\n", WTERMSIG(status));
    }

    return 0;
}