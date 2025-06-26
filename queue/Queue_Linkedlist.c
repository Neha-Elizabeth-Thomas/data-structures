#include<stdio.h>
#include<stdlib.h>
#define INVALID -9999

struct node{
  int data;
  struct node* link;
};
struct node *head,*f=NULL,*r=NULL;

void Enqueue(int item)//insertEnd
{
  struct node* new=(struct node*)malloc(sizeof(struct node));
  if(new==NULL)
    printf("Memory overflow\n");
  else
  {
    new->data=item;
    new->link=NULL;
    if(f==NULL)
    {
      head->link=new;
      f=new;
      r=new;
    }
    else
    {
      r->link=new;
      r =new;   
    }
  }
}

int dequeue()//deleteBeg
{
  if(f==NULL)
  {
    printf("No elements\n");
    return INVALID;
  }
  else
  {
    int item=f->data;
    head->link=f->link;
    free(f);
    f=head->link;
    if(f==NULL)
      r=NULL;
    return item;
  }
}

void display()
{
  struct node* ptr;
  ptr=f;
  printf("QUEUE:\n");
  if(f==NULL)
  {
    printf("No elements\n");
    return;
  }
  printf("FRONT:  ")
  while(ptr!=NULL)
  {
    printf("%d\t",ptr->data);
    ptr=ptr->link;
  }
  printf(":REAR");
}

void returnNode()
{
  struct node* ptr;
  ptr=head;
  while(ptr!=NULL)
  {
    struct node* temp=ptr->link;
    free(ptr);
    ptr=temp;
  }
}

void main()
{
  int choice,num;
  head=(struct node*)malloc(sizeof(struct node));
  head->link=NULL;

  do
  {
    printf("Enter your choice:\n1)Insert\n2)Delete\n3)Display\n4)Exit\n");
    scanf("%d",&choice);

    switch(choice)
    {
      case 1:printf("Enter the num to be inserted: ");
              scanf("%d",&num);
              Enqueue(num);
              break;
      case 2:num=dequeue();
              if(num!=INVALID)
                printf("popped num=%d\n",num);
              break;
      case 3:display();
              break;
      case 4:returnNode();
              return;
      default:returnNode();
              return;
    }
  }
  while(1);
}