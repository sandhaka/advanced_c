#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
    Include common.c:
    gcc -pedantic main.c ../_common/bin_2_short.c 
 */

#define CMD_STR_LEN 5
#define USER_INPUT_LEN 44
#define BITS 16

struct cmd {
    int code;
    size_t cmd_str_len;
    short args[16];
    char cmd_str[CMD_STR_LEN + 1];
};

typedef unsigned short ushort;

extern int short_to_bin_str(short d, char* buffer, size_t lenght);

static struct cmd commands[3] = {
    {0, 3, {0}, "set"},
    {1, 5, {0}, "unset"},
    {2, 4, {0}, "read"}
};

void set(void);
void unset(void);
void read(void);
struct cmd* parse_usr_input(const char *restrict buffer);

void print_menu(void) {
    printf("Type a masking option:\n");
    printf("[set] <bits 1-16>\n");
    printf("[unset] <bits 1-16>\n");
    printf("[read]\n");
    printf("Examples:\n");
    printf("> read\n");
    printf(". 0000000000000000\n");
    printf("> set 1 3 10\n");
    printf(". 0000001000000101\n");
    printf("> uset 3\n");
    printf(". 0000001000000001\n");    
}

int main(int argc, char** argv) {

    ushort flags = 0, mask;
    char usr_input[USER_INPUT_LEN + 1];
    
    if (argc > 1) {
        flags = (ushort) atoi(argv[1]);
    }

    print_menu();

    if (scanf("%44[^\n]", usr_input) == -1) {
        printf("Unrecognized command: %s\n", usr_input);
        return -1;
    }

    struct cmd* cmd = parse_usr_input(usr_input);

    if (cmd == NULL) {
        printf("Wrong commands arguments\n");
        return -1;
    }

    printf("'%s' command selected!\n", cmd->cmd_str);

    switch (cmd->code)
    {
    case 0:
        printf("Setting bits:\n");
        for (int i = 0; i < BITS - 1; i++)
            printf("%d ", cmd->args[i]);
        break;
    case 1:
        break;
    case 2: 
        break;
    default:
        {
            printf("Unrecognized command\n");
            return -1;
        }
    }

    return 0;
}

void set(void) {

}

void unset(void) {

}

void read(void) {

}

struct cmd* parse_usr_input(const char *restrict buffer) {
    int i, a = 0, l = 0;

    // Parse command
    for (i = 0; i < USER_INPUT_LEN; i++) {
        char c = buffer[i];
        if (c == ' ' || c == '\0') { 
            break;
        }

        l++;
    }

    for (int j = 0; j < 3; j++) {
        if (l != commands[j].cmd_str_len) continue;
        if (strncmp(buffer, commands[j].cmd_str, commands[j].cmd_str_len) == 0) {
            // Eventually parse arguments
            if (commands[j].code != 2) {
                l = 0;
                char arg[3];
                for (;i < USER_INPUT_LEN; i++) {
                    char c = buffer[i];
                    if (c != ' ' && c != '\0') { 
                        l++;
                    }
                    else if(l != 0) {
                        if (l > 2) return NULL;
                        strncpy(arg, buffer + (i - l), l);
                        arg[l + 1] = '\0';
                        l = 0;
                        int bit = (short) atoi(arg);
                        if (bit >= 16) return NULL;
                        commands[j].args[a++] = bit;
                    }

                    if (c == '\0') {
                        break;
                    }
                }
            }

            return &commands[j];
        }
    }

    return NULL;
}
