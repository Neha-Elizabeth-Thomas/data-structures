#include<stdio.h>
#include<stdlib.h>

struct node
{
  char data;
  struct node* Llink;
  struct node* Rlink;
};
struct node* head;

void InsertBeg(char item)
{
  struct node* new=(struct node*)malloc(sizeof(struct node));
  if(new==NULL)
    printf("memory overflow\n");
  else
  {
    new->data=item;
    new->Llink=head;
    new->Rlink=head->Rlink;
    head->Rlink=new;
    if(new->Rlink!=NULL)
      new->Rlink->Llink=new;
  }
}

int isPalindrome()
{
  struct node* left=head->Rlink;
  struct node* right=left;
  while(right->Rlink!=NULL)
    right=right->Rlink;
  while(right!=left && left->Llink!=right)
  {
    if(left->data!=right->data)
      return 0;
    left=left->Rlink;
    right=right->Llink;
  }
  return 1;
}

void returnNode()
{
  struct node* ptr;
  ptr=head;
  while(ptr!=NULL)
  {
    struct node* temp=ptr->Rlink;
    free(ptr);
    ptr=temp;
  }
  printf("Successfully cleared memory\n");
}

void main()
{
  char str[30];
  int i;
  head=(struct node*)malloc(sizeof(struct node));
  head->Rlink=NULL;
  head->Llink=NULL;
  head->data=0;

  printf("Enter the string to be checked palindrome: ");
  scanf(" %[^\n]",str);

  for(i=0 ; str[i]!='\0' ; i++)
  {
    if(str[i]>='a' && str[i]<='z')
      str[i]-=32;
    InsertBeg(str[i]);
  }
   
  if(isPalindrome())
    printf("PALINDROME\n");
  else
    printf("NOT PALINDROME\n");

  returnNode();
}