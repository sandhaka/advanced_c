#include <stdio.h>
#include <string.h>

#define BOLD "\033[1m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

void reverse(char ar[], int n) {
    char temp[n];
    for (int i = 0; i < n; i++)
        temp[i] = ar[n - i - 1];
    for (int i = 0; i < n; i++)
        ar[i] = temp[i];
}

int decimalToBinary(void) {
    printf("Type a positive decimal number:\n");
    int input, integer, i = 0;
    int n = scanf("%d", &input);
    if (n != 1 || input <= 0) {
        printf("%s%sError reading input. Please try again.%s\n", BOLD, RED, RESET);
        return -1;
    }

    char binary[32];
    integer = input;

    while (integer > 0)
    {
        binary[i++] = '0' + (integer & 1);
        integer >>= 1;
    }
    binary[i] = '\0';
    
    reverse(binary, i);

    printf(BOLD GREEN "Typed: %d Binary: %s" RESET "\n", input, binary);
    
    return 0;
}

int binaryToDecimal(void) {
    printf("Type a binary number:\n");
    char binary[32];
    int n = scanf("%31s", binary);
    if (n != 1) {
        printf("%s%sError reading input. Please try again.%s\n", BOLD, RED, RESET);
        return -1;
    }
    
    int i, p = 0, d = 0;
    for (i = strlen(binary) - 1; i >= 0; i--,p++) {
        if (binary[i] == '1') {            
            d += 1 << p;
            continue;
        }
        if (binary[i] != '0') {
            printf("%s%sInvalid binary number:%s%s\n", BOLD, RED, binary, RESET);
            return -1;
        }
    }

    printf(BOLD GREEN "Typed: %s Decimal: %d" RESET "\n", binary, d);

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
