#include<stdio.h>
#include<string.h>
#include<math.h>

#define SIZE 10

char s[SIZE];
int top=-1;

void push(char item){
    if(top==SIZE-1)
        printf("stack full\n");
    else
    {
        s[++top]=item;
    }
}

char pop(){
    if(top==-1)
        printf("stack empty\n");
    else
    {
        return s[top--];
    }
}

int precedence(char optr){
    switch(optr){
        case '+':
        case '-':return 1;
        case '*':
        case '/':return 2;
        case '^':return 3;
        case '(':return 0;
    }
}

void reverse(char str[]){
    int l=0,r;
    for(r=0 ; str[r]!='\0' ; r++);
    r--;
    while(l<r){
        char temp=str[l];
        str[l]=str[r];
        str[r]=temp;

        l++; r--;
    }
}

int isOperand(char ch){
    return ch>='a'&&ch<='z' || ch>='A'&&ch<='Z' || ch>='0'&&ch<='9';
}

void infixToPrefix(char infix[],char prefix[]){
    int i,j;
    reverse(infix);
    strcat(infix,"(");
    push('(');

    j=0;
    for(i=0 ; infix[i]!='\0' ; i++){
        char symb=infix[i];
        if(symb=='(')
            symb=')';
        else if(symb==')')
                symb='(';

        if(isOperand(infix[i]))
            prefix[j++]=symb;
        else if(symb=='(')
                push(symb);
              else if(symb==')')
                    {
                        while(s[top]!='(' && top!=-1)
                            prefix[j++]=pop();
                        pop();
                    }
                    else
                    {
                        while(precedence(symb)<precedence(s[top]))
                            prefix[j++]=pop();
                        push(symb);
                    }
    }
    prefix[j]='\0';
    reverse(prefix);
}

int isOperator(char ch){
    return ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^';    
}

int evaluatePrefix(char prefix[]){
    int i;
    for(i=0 ; prefix[i]!='\0' ; i++);
    i--;

    for( ; i>=0 ; i--){
        char symb=prefix[i];
        if(symb>='0' && symb<='9')
            push(symb-'0');
        else if(isOperator(symb)){
            int a=pop();
            int b=pop();
            switch(symb){
                case '+': push(a+b);
                          break;
                case '-': push(a-b);
                          break;
                case '*': push(a*b);
                          break;
                case '/': push(a/b);
                          break;
                case '^':push(pow(a,b));
                         break;
                default:printf("invalid operator found\n");
                        return -9999;
            }
        }
    }
    if(top==0)
        return s[top];
    else
        return -9999;
}

void main(){
    char infix[20],prefix[20];

    printf("Enter an infix expression: ");
    scanf(" %[^\n]",infix);

    infixToPrefix(infix,prefix);

    printf("The prefix equivalent is: %s\n",prefix);

    printf("The result of prefix evaluation is: %d\n",evaluatePrefix(prefix));

}
