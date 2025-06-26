#include<stdio.h>
#define SIZE 20
#define INVALID '#'
int S[20],top=-1;
void push(char item)
{
  if(top==SIZE-1)
    printf("Stack Overflow!");
  else
  {
    top++;
    S[top]=item;
  }
}
char pop()
{
  if(top==-1)
    return INVALID;
  else
  {
    char item=S[top];
    top--;
    return item;
  }
}
void main()
{
  char str[20],ch;
  int i,palindrome=1;
  printf("Enter a string: ");
  scanf(" %[^\n]",str);

  for(i=0 ; str[i]!='\0' ; i++)
    push(str[i]);
  for(i=0 ; str[i]!='\0' ; i++)
  {
    ch=pop();
    if(ch!=str[i])
      palindrome=0;
  }
  if(palindrome)
    printf("PALINDROME\n");
  else
    printf("NOT PALINDROME\n");

}