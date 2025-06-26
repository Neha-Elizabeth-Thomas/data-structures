#include<stdio.h>
#include<stdlib.h>
#define INVALID -999
struct node{
  int data;
  struct node* link;
};

struct node* newNode(int item){
  struct node* new=(malloc(sizeof(struct node)));
  new->data=item;
  new->link=NULL;
  return new;
}

void push(struct node* head,int item){
  struct node* new=newNode(item);
  new->link=head->link;
  head->link=new;
}

int pop(struct node* head)
{
  int item;
  if(head->link==NULL)
    return INVALID;
  item=head->link->data;
  head->link=head->link->link;
  return item;
}

void reverse(struct node* Shead)
{
  struct node* Phead,*Qhead;
  int num;
  Phead=newNode(0);
  Qhead=newNode(0);

  while((num=pop(Shead))!=INVALID)
    push(Phead,num);
  while((num=pop(Phead))!=INVALID)
    push(Qhead,num);
  while((num=pop(Qhead))!=INVALID)
    push(Shead,num);
}

void display(struct node* head)
{
  struct node* ptr=head->link;
  while(ptr!=NULL)
  {
    printf("%d-> ",ptr->data);
    ptr=ptr->link;
  }
  printf("\n\n");
}

void main()
{
  struct node *Shead;
  int i;

  Shead=newNode(0);

  for(i=0 ; i<10 ; i++)
    push(Shead,i);

  display(Shead);
  reverse(Shead);
  display(Shead);
}