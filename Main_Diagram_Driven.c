#include <stdio.h>

int main() {
    enum State {S0, S1, S2} state = S0;
    char ch;
    char input[100];

    //printf("Diagram Driven Lex:\n");
    printf("Enter input: ");
    scanf("%s", input);
    for (int i = 0; input[i] != '\0'; i++) {
        ch = input[i];
        switch (state) {
            case S0:
                if (ch == '1') {
                    state = S1;
                } else if (ch == '0') {
                    state = S0;
                } else {
                    printf("String Rejected: Invalid Symbol '%c'", ch);
                    return 0;
                } break;
            case S1:
                if (ch == '1') {
                    state = S0;
                } else if (ch == '0') {
                    state = S2;
                } else {
                    printf("String Rejected: Invalid Symbol '%c'", ch);
                    return 0;
                } break;
            case S2:
                if (ch == '1'){
                    state = S2;
                } else if (ch == '0') {
                    state = S1;
                } else {
                    printf("String Rejected: Invalid Symbol '%c'", ch);
                    return 0;
                } break;
            }
    }
    if (state == S0) {
        printf("String Accepted\n");
    } else {
        printf("String Rejected\n");
    }
    return 0;
}