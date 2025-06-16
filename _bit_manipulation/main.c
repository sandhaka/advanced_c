#include <stdio.h>
#include <string.h>

#define BOLD "\033[1m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

int decimalToBinary(void) {
    printf("Type a decimal number:\n");
    return 0;
}

int binaryToDecimal(void) {
    printf("Type a binary number:\n");
    char binary[33];
    int n = scanf("%32s", binary);
    if (n != 1) {
        printf("%s%sError reading input. Please try again.%s\n", BOLD, RED, RESET);
        return -1;
    }
    
    int i, p = 0, d = 0;
    for (i = 0; binary[i] != '\0'; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            printf("%s%sInvalid binary number:%s%s\n", BOLD, RED, binary, RESET);
            return -1;
        }
    }

    printf(BOLD GREEN "Typed: %s" RESET "\n", binary);

    for (i = strlen(binary) - 1; i >= 0; i--,p++) {
        if (binary[i] == '1')
            d += 1 << p;
    }

    printf(BOLD GREEN "Decimal value: %d" RESET "\n", d);

    return 0;
}

int choice(void) {
    printf("Select an option:\n");
    printf("1) Convert a decimal number to binary\n");
    printf("2) Convert binary to decimal\n");
    printf("3) Exit\n");

    int option = 0;

    while (option < 1 || option > 3) {
        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");
        }    
        if (option < 1 || option > 3) {
            printf("Invalid option. Please select a number between 1 and 3.\n");
        }
    }

    return option;
}

int main(void) {
    int exitCode;
    switch (choice())
    {
        case 1:
            exitCode = decimalToBinary();
            break;
        case 2:
            exitCode = binaryToDecimal();
            break;
        default: 
            break;
    }

    return exitCode;
}
