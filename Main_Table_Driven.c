#include <stdio.h>

int main() {
    int table[3][2] = {
        {0, 1},
        {2, 0},
        {1, 2}
    };

    int acceptingState = 0;
    int state = 0;
    char input[100];
    char ch;
    int symbol;

    printf("Enter input: ");
    scanf("%s", input);

    for (int i = 0; input[i] != '\0'; i++) {
        ch = input[i];

        if (ch == '0') {
            symbol = 0;
        } else if (ch == '1') {
            symbol = 1;
        } else {
            printf("String Rejected: Invalid Symbol '%c'", ch);
            return 0;
        }

        state = table[state][symbol];
    }

    if (state == acceptingState) {
        printf("String Accepted\n");
    } else {
        printf("String Rejected\n");
    }

    return 0;
}