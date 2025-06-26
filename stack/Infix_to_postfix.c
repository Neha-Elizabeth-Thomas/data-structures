#include<stdio.h>
#include<string.h>
#include<math.h>

#define SIZE 30
char S[SIZE];
int top=-1;

void push(char item)
{
  if(top==SIZE-1)
    printf("Stack full\n");
  else{
    top++;
    S[top]=item;
  }
}
char pop()
{
  if(top==-1)
    printf("Stack empty\n");
  else
  {
    char item=S[top];
    top--;
    return item;
  }
}

int isp(char ch)
{
  switch(ch)
  {
    case '+':
    case '-':return 2;
    case '*':
    case '/':return 4;
    case '^':return 5;
    case '(':return 0;
  }
}

int icp(char ch)
{
  switch(ch)
  {
    case '+':
    case '-':return 1;
    case '*':
    case '/':return 3;
    case '^':return 6;
    case '(':return 7;
  }
}
int isOperand(char ch)
{
  return ch>='a'&&ch<='z' || ch>='A'&&ch<='Z' || ch>='0'&&ch<='9';
}
void InfixToPostfix(char infix[],char postfix[])
{
  int i,j;
  char symb;
  push('(');
  strcat(infix,")");
  j=0;
  for(i=0 ; infix[i]!='\0' ; i++)
  {
      symb=infix[i];
      if(isOperand(symb))
        postfix[j++]=symb;
      else if(symb==')')
            {
              while(S[top]!='(')
              {
                postfix[j++]=pop();
              }
              pop();
            }
            else
            {
              while(icp(symb)<=isp(S[top]))
              {
                postfix[j++]=pop();
              }
              push(symb);
            }
  }
  /*while(top!=-1)
  {
    postfix[j++]=pop();
  }*/ //not needed because we are concatenating ')'
  postfix[j]='\0';
}

int postfixEvaluate(char postfix[])
{
  char symb;
  int i,j,x,y;

  for(i=0 ; postfix[i]!='\0' ; i++)
  {
      symb=postfix[i];
      if(symb>='0'&&symb<='9')
        push(symb-'0');
      else
      {
        x=pop();
        y=pop();
        switch(symb)
        {
          case '+':push(y+x);
                    break;
          case '-':push(y-x);
                   break;
          case '*':push(y*x);
                   break;
          case '/':push(y/x);
                   break;
          case '^'://push(y^x);//include math.h how do you think C is going to take '^'
                   push(pow(y,x));
                   break;
          default:printf("Invalid operator\n");
        }
      }
  }
  return S[top];
}
void main()
{
  char infix[20],postfix[20];

  printf("Enter an infix expression: ");
  scanf("%s",infix);

  InfixToPostfix(infix,postfix);

  printf("postfix: %s\n",postfix);

  printf("value = %d\n",postfixEvaluate(postfix));
}