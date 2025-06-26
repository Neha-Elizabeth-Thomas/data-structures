#include<stdio.h>
#include<math.h>

#define SIZE 10
char s[SIZE],top=-1;

void push(char item)
{
  if(top==SIZE-1)
    return;
  s[++top]=item;
}

char pop()
{
  if(top==-1)
    return '*';
  return s[top--];
}

int isOperator(char ch)
{
  return ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^';
}

int evaluatePrefix(char prefix[])
{
  int i;
  for(i=0 ; prefix[i]!='\0' ; i++);
  i--;
  while(i!=-1)
  {
    char symb=prefix[i];
    if(symb>='0' && symb<='9')
      push(symb-'0');
    else if(isOperator(symb))
          {
            int a=pop();
            int b=pop();
            switch(symb)
            {
              case '+': push(a+b);
                        break;
              case '-': push(a-b);
                        break;
              case '*': push(a*b);
                        break;
              case '/': push(a/b);
                        break;
              case '^': push(pow(a,b));
                        break;
            }
          }
    i--;  
  }
  if(top==0)
    return s[top];
}

void main()
{
  char prefix[20];
  int result;
  printf("Enter a prefix expression: ");
  scanf(" %s",prefix);

  result=evaluatePrefix(prefix);
  printf("RESULT=%d\n",result);
}