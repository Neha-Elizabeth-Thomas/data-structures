#include<stdio.h>
#include<stdlib.h>
struct node
{
  int data;
  struct node* link;
};
void main()
{
    struct node *head,*temp,*ptr;
    int n,num,i;

    printf("How many numbers?");
    scanf("%d",&n);
//creation
    printf("Enter %d numbers: ",n);
    head=(struct node*)malloc(sizeof(struct node));
    ptr=head;
    for(i=0 ; i<n ; i++)
    {
      scanf("%d",&num);
      temp=(struct node*)malloc(sizeof(struct node));
      temp->data=num;
      ptr->link=temp;
      temp->link=NULL;
      ptr=ptr->link;
    }
//display
    ptr=head->link;
    while(ptr!=NULL)
    {
      printf("%d\n",ptr->data);
      ptr=ptr->link;
    }
//free the memory
    ptr=head;
    while(ptr!=NULL)
    {
      struct node*ptr1;
      ptr1=ptr->link;
      free(ptr);
      ptr=ptr1;
    }
}