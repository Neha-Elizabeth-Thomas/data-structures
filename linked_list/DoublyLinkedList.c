#include<stdio.h>
#include<stdlib.h>
#define INVALID -9999
struct node
{
  int data;
  struct node* Llink;
  struct node* Rlink;
};
struct node *head;

void InsertBeg(int item)
{
  struct node* ptr;
  struct node* new=(struct node*)malloc(sizeof(struct node));
  if(new==NULL)
    printf("Memory overflow\n");
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
void InsertEnd(int item)
{
  struct node* ptr=head;
  while(ptr->Rlink!=NULL)
    ptr=ptr->Rlink;
  struct node* new=(struct node*)malloc(sizeof(struct node));
  if(new==NULL)
    printf("memory overflow\n");
  else
  {
    new->data=item;
    new->Rlink=NULL;
    new->Llink=ptr;
    ptr->Rlink=new;
  }
}
void Insertafter(int item,int key)
{
  struct node* ptr=head->Rlink;
  while(ptr->data!=key && ptr!=NULL)
    ptr=ptr->Rlink;
  if(ptr==NULL)
    printf("Key not found]n");
  else
  {
    struct node* new=(struct node*)malloc(sizeof(struct node));
    if(new==NULL)
      printf("Memory Overflow\n");
    else
    {
      new->data=item;
      new->Llink=ptr;
      new->Rlink=ptr->Rlink;
      ptr->Rlink=new;
      if(new->Rlink!=NULL)
        new->Rlink->Llink=new;
    }
  }
}

void Insertbefore(int item,int key)
{
  struct node* ptr=head->Rlink;
  while(ptr->data!=key && ptr!=NULL)
    ptr=ptr->Rlink;
  if(ptr==NULL)
    printf("key not found\n");
  else
  {
    struct node* new=(struct node*)malloc(sizeof(struct node));
    if(new==NULL)
      printf("Memory overflow\n");
    {
      new->data=item;
      new->Rlink=ptr;
      new->Llink=ptr->Llink;
      ptr->Llink=new;
      new->Llink->Rlink=new;
    }
  }
}
int deleteBeg()
{
  struct node* ptr=head->Rlink;
  if(ptr==NULL)
  {
    printf("no elements found\n");
    return INVALID;
  }
  else
  {
    int item=ptr->data;
    head->Rlink=ptr->Rlink;
    if(ptr->Rlink!=NULL)
      ptr->Rlink->Llink=head;
    free(ptr);
    return item;
  }
}

int deleteEnd()
{
  struct node* ptr=head->Rlink;
  if(ptr==NULL)
  {
    printf("no elements found\n");
    return INVALID;
  }
  else
  {
    int item;
    while(ptr->Rlink!=NULL)
      ptr=ptr->Rlink;
    item=ptr->data;
    ptr->Llink->Rlink=NULL;
    free(ptr);
    return item;
  }
}

int delete_any(int key)
{
  struct node* ptr=head->Rlink;
  if(ptr==NULL)
  {
    printf("List Empty\n");
    return INVALID;
  }
  else
  {
    while(ptr->data!=key && ptr!=NULL)
      ptr=ptr->Rlink;
    if(ptr==NULL)
      printf("Key not found\n");
    else
    {
      int item= ptr->data;
      ptr->Llink->Rlink=ptr->Rlink;
      if(ptr->Rlink!=NULL)
        ptr->Rlink->Llink=ptr->Llink;
      free(ptr);
      return item;
    }
  }
}

void reverse()
{
  struct node* ptr=head->Rlink;
  ptr->Llink=NULL;
  while(ptr->Rlink!=NULL)
  {
    struct node* temp;
    temp=ptr->Rlink;
    ptr->Rlink=ptr->Llink;
    ptr->Llink=temp;
    ptr=temp;
  }
  ptr->Rlink=ptr->Llink;
  ptr->Llink=head;
  head->Rlink=ptr;
}

/*void reverse()
{
  struct node* ptr=head;
  while(ptr->Rlink!=NULL)
  {
    struct node* temp=ptr->Llink;
    ptr->Llink=ptr->Rlink;
    ptr->Rlink=temp;
    ptr=ptr->Llink;
  }
  ptr->Rlink=ptr->Llink;
  ptr->Llink=head;
  
  head->Llink->Rlink=NULL;
  head->Llink=NULL;
  head->Rlink=ptr;
  ptr->Llink=head;
}*/

void display()
{
  struct node* ptr=head->Rlink;
  printf("\n\ncontents of list: \n");
  while(ptr!=NULL)
  {
    printf("%d\n",ptr->data);;
    ptr=ptr->Rlink;
  }
}

void returnNode()
{
  struct node* ptr=head;
  while(ptr!=NULL)
  {
    struct node* temp=ptr->Rlink;
    free(ptr);
    ptr=temp;
  }
}
void main()
{
  int choice,choice1,num,key;
  head=(struct node*)malloc(sizeof(struct node));
  head->Rlink=NULL;
  head->Llink=NULL;
  head->data=0;

  do
  {
    printf("Enter your choice:\n1)Insert\n2)Delete\n3)Display\n4)exit\n5)Reverse\n");
    scanf("%d",&choice);

    switch(choice)
    {
      case 1:printf("select:\n1)Insert beginning\n2)Insert End\n3)Insert at any position(after)\n4)Insert at any position(before)\n");
              scanf("%d",&choice1);
              switch(choice1)
              {
                case 1:printf("Enter the number to be inserted: ");
                        scanf("%d",&num);
                        InsertBeg(num);
                        display();
                        break;
                case 2:printf("Enter the number to be inserted: ");
                        scanf("%d",&num);
                        InsertEnd(num);
                        display();
                        break;
                case 3:printf("Enter the number to be inserted: ");
                        scanf("%d",&num);
                        printf("Enter the number after which %d is to be inserted: ",num);
                        scanf("%d",&key);
                        Insertafter(num,key);
                        display();
                        break;
                case 4:printf("Enter the number to be inserted: ");
                        scanf("%d",&num);
                        printf("Enter the number before which %d is to be inserted: ",num);
                        scanf("%d",&key);
                        Insertbefore(num,key);
                        display();
                        break;
                default:printf("Invalid\n");
              }
              break;
      case 2:printf("select:\n1)Delete from beginning\n2)Delete from end\n3)deletefrom any arbitrary position\n");
              scanf("%d",&choice1);
              switch(choice1)
              {
                case 1:deleteBeg();
                        display();
                        break;
                case 2:deleteEnd();
                        display();
                        break;
                case 3:printf("Enter the number to be deleted: ");
                      scanf("%d",&key);
                       delete_any(key);
                        display();
                       break;
                default:printf("Invalid\n");
              }
              break;
      case 3:display();
              break;
      case 4:returnNode();
              return;
      case 5:reverse();
              display();
              break;
      default:returnNode();
              return;
    }
  }
  while(1);
}