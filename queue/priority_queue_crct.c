#include<stdio.h>
#define SIZE 10

struct item{
  int data;
  int priority;
}pq[SIZE];
int f=-1,r=-1;

void enqueue(int data,int priority)
{
  if(f==0 && r==SIZE-1)
  {
    printf("queue full\n");
    return;
  }
  if(f==-1){
    f=r=0;
    pq[0].data=data;
    pq[0].priority=priority;
  }
  else if(r==SIZE-1)//but queue is not full
      {
        int i,j;
        for(i=f ; i<=r ; i++)
          pq[i-1]=pq[i];//shift all the elements 1 position to left
        f--; r--;//v.imp

        j=r;
        while(j>=f && pq[j].priority>priority)
        {
          pq[j+1]=pq[j];
          j--;
        }
        pq[j+1].data=data;
        pq[j+1].priority=priority;
        r++;//v.v.imp
      }
      else
      {
        int j=r;
        while(j>=f && pq[j].priority>priority)
        {
          pq[j+1]=pq[j];
          j--;
        }
        pq[j+1].data=data;
        pq[j+1].priority=priority;
        r++;
      }
}

int dequeue()
{
  if(f==-1)
    printf("queue empty\n");
  else
  {
    int item=pq[f].data;
    f=f+1;
    if(f==r+1)
      f=r=-1;
    return item;
  }
}

void display()
{
  int i;
  if(f==-1){
    printf("deque empty\n");
    return;
  }
  printf("data    | Front:   ");
  for(i=f ; i<=r ; i++)
    printf("%-4d",pq[i].data);
  printf(":rear\n\n");

  printf("Priority| Front:   ");
  for(i=f ; i<=r ; i++)
    printf("%-4d",pq[i].priority);
  printf(":rear\n\n");
}

void main()
{
  int choice,item,priority;
  do{
    printf("Enter your choice: \n1)enqueue\n2)dequeue\n3)display\n4)exit\n");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1: printf("Enter the item: ");
              scanf("%d",&item);
              printf("Enter it spriority: ");
              scanf("%d",&priority);
              enqueue(item,priority);
              display();
              break;
      case 2: printf("The highest priority element dequeued is : %d\n",dequeue());
              display();
              break;
      case 3: display();
              break;
      case 4: return;
    }
  }while(1);
}