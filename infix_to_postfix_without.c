#include <stdio.h>
#include <ctype.h>

int precedence(char operator) {
    if (operator == '+' || operator == '-')
        return 1;
    if (operator == '*' || operator == '/')
        return 2;
    return 0;
}

void infixToPostfix(char* infix, int i) {
    if (infix[i] == '\0') {
        return;
    }

    if (isdigit(infix[i]) || isalpha(infix[i])) {
        printf("%c", infix[i]);
    } else if (infix[i] == '(') {
        infixToPostfix(infix, i + 1);
    } else if (infix[i] == ')') {
        // Do nothing here
    } else {
        while (precedence(infix[i]) <= precedence(infix[i + 1])) {
            infixToPostfix(infix, i + 1);
        }
        printf("%c", infix[i]);
    }
    infixToPostfix(infix, i + 1);
}

int main() {
    char infix[100];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    printf("Postfix expression: ");
    infixToPostfix(infix, 0);

    return 0;
}
