#include<stdio.h>
#include<stdlib.h>

struct node{
  int data;
  struct node* link;
}*head;

struct node* newNode(int item)
{
  struct node* new=(struct node*)malloc(sizeof(struct node));
  new->data=item;
  new->link=NULL;
  return new;
}

void insert(int data)
{
  struct node* new,*ptr;
  new=newNode(data);
  ptr=head;
  while(ptr->link!=NULL)
    ptr=ptr->link;
  ptr->link=new;
}

void display()
{
  struct node* ptr=head->link;
  if(ptr==NULL)
    printf("list empty\n");
  else 
  {
    while(ptr!=NULL)
    {
      printf("%d\n",ptr->data);
      ptr=ptr->link;
    }
  }
}

void bubblesort()
{
  int i,n=1;
  struct node* j,*end,*prev;
  if(head->link==NULL) return;

  end=head->link;
  while(end->link!=NULL)
  {
    end=end->link;
    n++; 
  }
  for(i=1 ; i<n ; i++)
  {
    j=head->link;
    while(j!=end)
    {
      if(j->data>j->link->data)
      {
        int temp=j->data;
        j->data=j->link->data;
        j->link->data=temp;
      }
      prev=j;
      j=j->link;
    }
    end=prev;
  }
}

void main()
{
  int i,n,num;
  head=newNode(0) ;

  printf("How many elements?");
  scanf("%d",&n);

  printf("Enter %d numbers: ",n);
  for(i=0 ; i<n ; i++)
  {
    scanf("%d",&num);
    insert(num);
  }
  bubblesort();
  display();
}
