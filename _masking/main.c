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

static struct cmd commands[4] = {
    {0, 3, {0}, "set"},
    {1, 5, {0}, "unset"},
    {2, 4, {0}, "read"},
    {3, 4, {0}, "exit"}
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
    printf("[exit]\n");
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
    char flags_bin_string[BITS + 1];
    
    if (argc > 1) {
        flags = (ushort) atoi(argv[1]);
    }

    print_menu();

    for(;;) {
        
        printf("> ");

        fgets(usr_input, USER_INPUT_LEN, stdin);
        usr_input[USER_INPUT_LEN] = '\0';

        struct cmd* cmd = parse_usr_input(usr_input);

        if (cmd == NULL) {
            printf("Wrong commands arguments\n");
            continue;
        }

        printf("'%s' command selected!\n", cmd->cmd_str);

        switch (cmd->code)
        {
        case 0:
            printf("Setting bits:\n");
            for (int i = 0; i < BITS; i++)
                printf("%d ", cmd->args[i]);
            printf("\n");
            break;
        case 1:
            printf("Unsetting bits:\n");
            for (int i = 0; i < BITS; i++)
                printf("%d ", cmd->args[i]);
            printf("\n");
            break;
        case 2: 
            if (short_to_bin_str(flags, flags_bin_string, BITS + 1) != 0)
                return -1;
            printf("Value flags: %s\n", flags_bin_string);
            break;
        case 3:
            return 0;
        default:
            {
                printf("Unrecognized command\n");
                return -1;
            }
        }
    }
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
        if (c == ' ' || c == '\0' || c == '\n') { 
            break;
        }

        l++;
    }

    for (int j = 0; j < 4; j++) {
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
                        arg[l] = '\0';
                        l = 0;
                        int bit = (short) atoi(arg);
                        if (bit >= 16 || bit < 0) return NULL;
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
