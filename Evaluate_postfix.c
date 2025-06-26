#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 20
#define INVALID -9999

int S[20],top=-1;
void push(int item)
{
  if(top==SIZE-1)
    printf("Stack Overflow!");
  else
  {
    top++;
    S[top]=item;
  }
}
int pop()
{
  if(top==-1)
    return INVALID;
  else
  {
    int item=S[top];
    top--;
    return item;
  }
}
int postfixEvaluation(char Exp[])
{
  int i=0;
  strcat(Exp,"#");
  while(Exp[i]!='#')
  {
    if(Exp[i]>='0'&&Exp[i]<='9')
      push(Exp[i]-'0');
    else
    {
      int x=pop();
      int y=pop();
      switch(Exp[i])
      {
        case '+':push(y+x);
                break;
        case '-':push(y-x);
                break;
        case '*':push(y*x);
                 break;
        case '/':push(y/x);
                break;
        case '^':push(y^x);
                
      }
    }
    i++;
  }
  return S[top];
}
void main()
{
  char Exp[20];

  printf("Enter a postfix expression to be evaluated: ");
  scanf(" %[^\n]",Exp);
  printf("Result=%d\n",postfixEvaluation(Exp));
}