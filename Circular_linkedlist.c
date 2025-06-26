#include<stdio.h>
#include<stdlib.h>
struct node
{
  int data;
  struct node* link;
};
void display(struct node* head)
{
  struct node* ptr;
  ptr=head->link;
  while(ptr!=head)
  {
    printf("%d\n",ptr->data);
    ptr=ptr->link;
  }
}
struct node* search(struct node* head,int item)
{
  struct node* ptr;
  ptr=head->link;
  if(ptr==NULL)
    printf("No elements");
  else
  {
    while(ptr!=head)
    {
      if(ptr->data==item)
        return ptr;
      ptr=ptr->link;
    }
    printf("%d not found\n",item);
    return NULL;
  }
}

void returnNode(struct node*  head)
{
  struct node* ptr;
  ptr=head->link;
  while(ptr!=head)
  {
    struct node* temp=ptr->link;
    free(ptr);
    ptr=temp;
  }
  free(head);

  printf("Successfully freed memory\n");
}
void main()
{
  int n,num,i;
  struct node* ptr;
  struct node* head=(struct node*)malloc(sizeof(struct node));
  head->data=0;
  head->link=NULL;
  printf("How many numbers: ");
  scanf("%d",&n);
  printf("Enter %d numbers: ",n);
  ptr=head;
  for(i=0 ; i<n ; i++)
  {
    struct node* new=(struct node*)malloc(sizeof(struct node));
    scanf("%d",&num);
    new->data=num;
    new->link=head;
    ptr->link=new;
    ptr=new;
  }

  display(head);

  printf("enter the number to be searched: ");
  scanf("%d",&num);
  if(search(head,num)!=NULL)
    printf("%d is present in the list\n",num);

  returnNode(head);
}