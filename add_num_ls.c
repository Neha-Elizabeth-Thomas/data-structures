#include<stdio.h>
#include<stdlib.h>

struct node{
  int data;
  struct node* link;
}*head1,*head2,*head3;

struct node* newNode(int data){
  struct node* new=(struct node*)malloc(sizeof(struct node));
  new->data=data;
  new->link=NULL;
  return new;
}

void insertBeg(struct node* head,int data)
{ 
  struct node* new=newNode(data);
  new->link=head->link;
  head->link=new;
}

void display(struct node* head)
{
  struct node* ptr=head->link;
  while(ptr->link!=NULL)
  {
    printf("%d->",ptr->data);
    ptr=ptr->link;
  }
  printf("%d\n\n",ptr->data);
}

void reverse(struct node* head)
{
  struct node* ptr,*prev,*temp;
  prev=NULL;
  ptr=head->link; 
  while(ptr)
  {
    struct node* temp=ptr->link;
    ptr->link=prev;
    prev=ptr;
    ptr=temp;
  }
  head->link=prev;
}

void add()
{
  int sum, carry=0;
  struct node* ptr1,*ptr2;
  reverse(head1);
  reverse(head2);

  ptr1=head1->link;
  ptr2=head2->link;
  while(ptr1 || ptr2)
  { 
    sum=0;
    //sum=ptr1->data+ptr2->data+carry;
    if(ptr1)
      sum+=ptr1->data;
    if(ptr2)
      sum+=ptr2->data;
    sum+=carry;

    carry=sum/10;
    sum=sum%10;
    insertBeg(head3,sum);
    if(ptr1)
      ptr1=ptr1->link; 
    if(ptr2)
      ptr2=ptr2->link;
  }
  if(carry)
    insertBeg(head3,carry);
}

void main()
{
  int num1,num2;
  head1=newNode(0);
  head2=newNode(0);
  head3=newNode(0);

  printf("Enter 2 numbers: ");
  scanf("%d %d",&num1,&num2);

  while(num1)
  {
    insertBeg(head1,num1%10);
    num1=num1/10;
  }
  
  while(num2)
  {
    insertBeg(head2,num2%10);
    num2=num2/10;
  }

  printf("1st num:\n");
  display(head1);
  printf("2nd num:\n");
  display(head2);

  add();
  printf("sum:\n"); 
  display(head3);
}