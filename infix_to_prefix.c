#include<stdio.h>
#include<string.h>
#define SIZE 20
#define INVALID '#'

char S[10];
int top=-1;
void push(char item)
{
  if(top==SIZE-1)
    printf("Stack Overflow\n");
  else{
    top++;
    S[top]=item;
  }
}
char pop()
{
  if(top==-1)
  {
    printf("Stack Underflow\n");
    return INVALID;
  }
  else
  {
    char item=S[top];
    top--;
    return item;
  }
}
int isoperand(char ch)
{
  return ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||ch>='0'&&ch<='9';
}
int isEmpty()
{
  return top==-1;
}
void reverseString(char s[])
{
  int l,r;
  l=0;
  for(r=0 ; s[r]!='\0' ; r++)
    ;
  r--;
  while(l<r)
  {
    char temp=s[l];
    s[l]=s[r];
    s[r]=temp;
    l++;
    r--;
  }
}
int precedence(char ch)
{
  switch(ch)
  {
    case '+':
    case '-':return 1;
    case '*':
    case '/':return 2;
    case '^':return 3;
    case '(':return 0;
  }
}

void InfixToPrefix(char infix[],char prefix[])
{
  int i,j;
  push('(');
  reverseString(infix);//imp
  
  /*for(i=0 ; infix[i]!='\0' ; i++)
    if(infix[i]=='(')
        infix[i]=')';
    else if(infix[i]==')')
            infix[i]='(';*/
  strcat(infix,"(");
  j=0;
  for(i=0 ; infix[i]!='\0' ; i++)
  { 
    if(infix[i]=='(')
        infix[i]=')';
    else if(infix[i]==')') //here the else is v.imp otherwise think about the catastrophic dump result that it will produce!!...
            infix[i]='(';//you are dump....
    if(isoperand(infix[i]))
    {
      prefix[j++]=infix[i];
    }
    else if(infix[i]=='(')
          push(infix[i]);
      else if(infix[i]==')')
            {
              while(S[top]!='('&&(!isEmpty()))
              {
                prefix[j++]=pop();
              }
              pop();
            }
            else
            {
              while(precedence(infix[i])<precedence(S[top]) && !isEmpty())
              { 
                //if precedence becomes equal then also push
                prefix[j++]=pop();
              }
              push(infix[i]);
            }
    }
  
  /*while(!isEmpty())
  {
    prefix[j++]=pop();
  }*/
  prefix[j]='\0';

  reverseString(prefix);
  
}
void main()
{
  char infix[20],prefix[20];
  printf("Enter the infix expression: ");
  scanf("%s",infix);
  InfixToPrefix(infix,prefix);
  printf("The prefix expression is:\n%s\n",prefix);
}