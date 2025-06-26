#include<stdio.h>
#define SIZE 10
#define INVALID -9999

int A[SIZE],count=0;

void insert(int item,int pos)
{
  int i;
  pos--;
  if(count==SIZE)
  {
    printf("Array full..No more insertions..\n");
    return;
  }
  if(count==0)
  {
    A[0]=item;
    count++;
    return;
  }
  for(i=count-1; i>=pos ; i--)
  {
    A[i+1]=A[i];
  }
  A[pos]=item;
  count++;
}

int delete(int pos)
{
  int i,item;
  pos--;
  if(pos>count-1 || count==0)
  {
    printf("Arrayindex out of bound exception\n");
    return INVALID;
  }
  item=A[pos];
  for(i=pos+1 ; i<count ; i++)
  {
    A[i-1]=A[i];
  }
  count--;
  return item;
}

void display()
{
  for(int i=0 ; i<count ; i++)
    printf("%d\t",A[i]);
  printf("\n");
}
void main()
{
  int choice,num,pos;
  do
  {
    printf("Enter your choice:\n1)Insert\n2)Dlete\n3)Display\n4)Exit\n");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1:printf("enter the number to be inserted: ");
              scanf("%d",&num);
              printf("Enter the position btw 1 and %d: ",count+1);
              scanf("%d",&pos);
              insert(num,pos);
              display();
              break;
      case 2:printf("enter the position from num is to be deleted:(btw 1 and %d)",count+1);
              scanf("%d",&pos);
              printf("deleted: %d\n",delete(pos));
              display();
              break;
      case 3:display();
              break;
      case 4:return;
    }
  }
  while(1);
}