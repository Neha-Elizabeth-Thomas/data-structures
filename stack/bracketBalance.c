#include<stdio.h>
#define SIZE 5
#define INVALID '#'

char S[SIZE];
int top=-1;

void push(char item){
    if(top==SIZE-1)
        printf("%d\n",S[top]);
    else
        S[++top]=item;
}

char pop(){
    if(top==-1)
        return INVALID;
    else
        return S[top--];
}

int checkBracket(char infix[]){
    int i;
    for(i=0 ; infix[i]!='\0' ; i++){
        char symb=infix[i];
        if(symb=='(' || symb=='{' || symb=='[' || symb=='<')
            push(symb);
        if(symb==')' || symb=='}' || symb==']' || symb=='>'){
            char item=pop();
            switch(symb){
                case ')': if(item!='(')
                            return 0;
                case '}': if(item!='{')
                            return 0;
                case ']': if(item!='[')
                            return 0;
                case '>': if(item!='<')
                            return 0;
            }
        }            
    }
    if(top!=-1)
        return 0;
    return 1;
}

void main(){
    char infix[30];
    printf("Enter an infix exp: ");
    scanf(" %s",infix);

    if(checkBracket(infix))
        printf("brackets balanced\n");
    else
        printf("unbalanced\n");
}
