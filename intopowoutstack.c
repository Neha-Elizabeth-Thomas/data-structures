#include <stdio.h>
#include <ctype.h>

#define MAX_SIZE 100

int precedence(char operator) {
    if (operator == '+' || operator == '-')
        return 1;
    if (operator == '*' || operator == '/')
        return 2;
    return 0;  // Lower precedence for other characters
}

void convertToPostfix(char *infix, int *index) {
    char c = infix[(*index)++];
    if (c == '(') {
        convertToPostfix(infix, index);
        putchar('(');
        convertToPostfix(infix, index);
        putchar(')');
    } else if (isalnum(c)) {
        putchar(c);
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
        int op1_precedence = precedence(c);
        int op2_precedence;
        if (infix[*index] == '+' || infix[*index] == '-' || infix[*index] == '*' || infix[*index] == '/') {
            op2_precedence = precedence(infix[*index]);
        } else {
            op2_precedence = 0;
        }

        if (op1_precedence > op2_precedence || op1_precedence == op2_precedence) {
            convertToPostfix(infix, index);
            putchar(c);
        } else {
            putchar('(');
            convertToPostfix(infix, index);
            putchar(c);
            convertToPostfix(infix, index);
            putchar(')');
        }
    }
}

int main() {
    char infix[MAX_SIZE];

    printf("Enter an infix expression: ");
    gets(infix);  // Note: gets() is not recommended for production code, but it simplifies input for this example.

    int index = 0;
    printf("Fully parenthesized postfix expression: ");
    convertToPostfix(infix, &index);
    putchar('\n');

    return 0;
}
