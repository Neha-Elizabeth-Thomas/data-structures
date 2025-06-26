#include<stdio.h>
#include<stdlib.h>

#define INVALID -9999

struct node 
{
  int data;
  struct node *link;
};
struct node *qhead,*shead,*top=NULL,*front=NULL,*rear=NULL;

void Enqueue(int item)
{
   struct node* new=(struct node*)malloc(sizeof(struct node));
   new->data=item;
   new->link=NULL;
   if(front==NULL)
   {
      front=rear=new;
      qhead->link=new;
   }
   else
   {
    rear->link=new;
    rear=new;
   }
}

int Dequeue()
{
   int item;
   if(front==NULL)
   {
      return INVALID;
   }
   item=front->data;
   qhead->link=front->link;
   free(front);
   front=qhead->link;
   if(front==NULL)
    rear=NULL;
  return item;
}

void push(int item)
{
  struct node* new=(struct node*)malloc(sizeof(struct node));
  new->data=item;
  new->link=top;
  top=new;
  shead->link=top;
}

int pop()
{
  if(top==NULL)
  {
    return INVALID;
  }
  else
  {
    int item=top->data;
    shead->link=top->link;
    free(top);
    top=shead->link;
    return item;
  }
}

void reverseQ()
{
  int num;
  while((num=Dequeue())!=INVALID)
  {
    push(num);
  }
  while((num=pop())!=INVALID)
  {
    Enqueue(num);
  }
}

void returnNode(struct node* head)
{
  struct node* ptr=head;
  while(ptr!=NULL)
  {
    struct node* temp=ptr->link;
    free(ptr);
    ptr=temp;
  }
}
void displayQ()
{
  struct node* ptr=qhead->link;
  if(ptr==NULL)
  {
    printf("Queue empty\n");
    return ;
  }
  //printf("Contents of the QUEUE:\n");
  while(ptr!=NULL)
  {
    printf("%d\n",ptr->data);
    ptr=ptr->link;
  }
}
void main()
{
  int n,i,num;
  qhead=(struct node*)malloc(sizeof(struct node));
  shead=(struct node*)malloc(sizeof(struct node));
  qhead->link=NULL;
  shead->link=NULL;

  printf("How many numbers to be enqueued? ");
  scanf("%d",&n);
  printf("Enter %d numbers to be enqueued to dequeue:\n",n);
  for(i=0 ; i<n ; i++)
  {
    scanf("%d",&num);
    Enqueue(num);
  }

  printf("The contents of the queue before reversing: \n");
  displayQ();

  reverseQ();

  printf("The contents of the queue after reversing: \n");
  displayQ();

  returnNode(qhead);
  returnNode(shead);
}