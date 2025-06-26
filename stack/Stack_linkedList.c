#include<stdio.h>
#include<stdlib.h>
#define INVALID -9999

struct node
{
  int data;
  struct node* link;
};
struct node *head,*top=NULL;

void push(int item)
{
  struct node* new=(struct node*)malloc(sizeof(struct node));
  if(new==NULL)
    printf("No memory in heap!memory overflow\n");
  else
  {
    new->data=item;
    new->link=top;
    head->link=new;
    top=new;
  }
}

int pop()
{
  if(top==NULL)
  {
    printf("no items in stack\n");
    return INVALID;
  }
  else
  {
    int item=top->data;
    head->link=top->link;
    free(top);
    top=head->link;
    return item;
  }
}

void display()
{
  struct node* ptr;
  ptr=top;
  if(top==NULL)
  {
    printf("No elements\n");
    return;
  }
  while(ptr!=NULL)
  {
    printf("%d\n",ptr->data);
    ptr=ptr->link;
  }
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
  printf("Successfully freed memory\n");
}
void main()
{
  int num,choice,i;

  head=(struct node*)malloc(sizeof(struct node));
  head->link=NULL;
  head->data=0;
  
  do
  {
    printf("Enter yourchoice:\n1)push\n2)pop\n3)display\n4)exit\n");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1:printf("Enter num to be pushed: ");
              scanf("%d",&num);
              push(num);
              break;
      case 2:num=pop();
              if(num!=INVALID)
                  printf("popped num=%d\n",num);
              break;
      case 3:display();
              break;
      case 4:returnNode();
              exit(0);
              break;
      default:returnNode();
              return;
    }
  }
  while(1);

  returnNode();
}