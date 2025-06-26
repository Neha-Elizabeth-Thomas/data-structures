#include<stdio.h>
#include<stdlib.h>
#define INVALID -9999

struct node
{
  int data;
  struct node* link;
};
struct node *head;

void InsertBeg(int item)
{
  struct node* new;
  new=(struct node*)malloc(sizeof(struct node));
  if(new==NULL)
    printf("memory Underflow\n");
  else
  {
    new->link=head->link;
    new->data=item;
    head->link=new;
  }
}

void InsertEnd(int item)
{
  struct node*ptr,*new;
  ptr=head;
  while(ptr->link!=NULL)
      ptr=ptr->link;
  new=(struct node*)malloc(sizeof(struct node));
  if(new == NULL)
    printf("Memory Underflow\n");
  else{
    new->data=item;
    new->link=NULL;
    ptr->link=new;
  }
}

void Insertafter(int item,int key)
{
  struct node *ptr,*new;

  new=(struct node*)malloc(sizeof(struct node));
  if(new ==  NULL)
    printf("memory Underflow\n");
  else
  {
    ptr=head->link;
    while( ptr!=NULL && ptr->data != key)
      ptr=ptr->link;
    if(ptr==NULL) 
      printf("%d not found\n",key);
    else
    {
      new->data=item;
      new->link=ptr->link;
      ptr->link=new;
    }
  }
}

void Insertbefore(int item,int key)
{
  struct node *new,*ptr,*prev=head;

  new=(struct node*)malloc(sizeof(struct node));
  if(new==NULL)
    printf("Memory Underflow\n");
  else
  {              
      ptr=head->link;
      while(ptr->data != key && ptr!=NULL)
      {
        prev=ptr;
        ptr=ptr->link;
      }
      if(ptr==NULL)
        printf("%d not found\n",key);
      else
      {
        new->data=item;
        new->link=ptr;
        prev->link=new;
      }
  }
}

void deleteBeg()
{
  struct node*ptr;
  ptr=head->link;
  if(ptr==NULL)
    printf("no items\n");
  else
  {
    head->link=ptr->link;
    free(ptr);
  }
}
void deleteEnd()
{
  struct node*ptr,*prev=head;
  if(head->link==NULL)
    printf("List empty\n");
  else
  {
    ptr=head;
    while(ptr->link!=NULL)
    {
      prev=ptr;
      ptr=ptr->link;
    }
    prev->link=NULL;
    free(ptr);
  }
}

void delete_any(int key)
{
  struct node*ptr,*prev=head;//if prev not initialized ,we wont be able to delete
  if(head->link==NULL)        //1st element
    printf("List empty\n");
  else
  {
    ptr=head->link;
    while(ptr->data!=key && ptr!=NULL)
    {
      prev=ptr;
      ptr=ptr->link;
    }
    if(ptr==NULL)
      printf("%d not found\n",key);
    else
    {
      prev->link=ptr->link;
      free(ptr);
    }
  }
}

void reverse()
{
  struct node*ptr,*next,*prev;
  prev=NULL;//imp
  ptr=head->link;
  while(ptr!=NULL)
  {

    next=ptr->link;
    ptr->link=prev;
    prev=ptr;
    ptr=next;
  }
  head->link=prev;
}
void display()
{
  struct node *temp,*ptr;
  printf("The contents of linked list:\n");
  ptr=head->link;
  while(ptr!=NULL)
  {
    printf("%d\t",ptr->data);
    ptr=ptr->link;
  }
  printf("\n");
}

int count()
{
  struct node *ptr;
  int c=0;
  ptr=head->link;
  while(ptr != NULL)
  {
    c++;
    ptr=ptr->link;
  }
  return c;
}

int search(int key)
{
  struct node *ptr;
  int pos=0;
  ptr=head->link;
  while(ptr!=NULL)
  {
    pos++;
    if(ptr->data==key)
      break;
    ptr=ptr->link;
  }
  if(ptr==NULL)
    return INVALID;
  else
    return pos;
}

void Free()
{
  struct node *ptr,*temp;
  ptr=head;
  while(ptr!=NULL)
  {
    temp=ptr->link;
    free(ptr);
    ptr=temp;
  }
}
void main()
{
  int choice,choice1,num,key,pos;
  head=(struct node*)malloc(sizeof(struct node));
  head->link=NULL;
  do
  {
    printf("Enter your choice:\n1)Insert\n2)Delete\n3)Display\n4)Count\n5)Reverse\n6)search\n7)Exit\n");
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
                        break;
                case 2:printf("Enter the number to be inserted: ");
                        scanf("%d",&num);
                        InsertEnd(num);
                        break;
                case 3:printf("Enter the number to be inserted: ");
                        scanf("%d",&num);
                        printf("Enter the number after which %d is to be inserted: ",num);
                        scanf("%d",&key);
                        Insertafter(num,key);
                        break;
                case 4:printf("Enter the number to be inserted: ");
                        scanf("%d",&num);
                        printf("Enter the number before which %d is to be inserted: ",num);
                        scanf("%d",&key);
                        Insertbefore(num,key);
                        break;
                default:printf("Invalid\n");
              }
              break;
      case 2:printf("select:\n1)Delete from beginning\n2)Delete from end\n3)deletefrom any arbitrary position\n");
              scanf("%d",&choice1);
              switch(choice1)
              {
                case 1:deleteBeg();
                        break;
                case 2:deleteEnd();
                        break;
                case 3:printf("Enter the number to be deleted: ");
                      scanf("%d",&key);
                       delete_any(key);
                       break;
                default:printf("Invalid\n");
              }
              break; 
      case 3:display();
              break;
      case 4:printf("Count=%d\n",count());
              break;
      case 5:reverse();
              break;
      case 6:printf("Enter the number to be searched: ");
             scanf("%d",&key);
             pos=search(key);
             if(pos==INVALID)
              printf("%d is not present in this list\n",key);
             else
              printf("%d is present at position %d\n",key,pos);
            break;
      case 7:Free();
              printf("Successfully exited\n");
              return ;
      default:printf("Invalid\n");
    } 
  }
  while(1);
}
