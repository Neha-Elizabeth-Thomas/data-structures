#include<stdio.h>
#include<stdlib.h>

struct node{
  int data;
  struct node* lchild;
  struct node* rchild;
}*root=NULL;


struct node* newNode(int item)
{
    struct node* new=(struct node*)malloc(sizeof(struct node));
    new->data=item;
    new->lchild=NULL;
    new->rchild=NULL;
    return new;
}

void inorder(struct node* ptr)
{
  //struct node* ptr=root;
  if(ptr!=NULL)
  {
    inorder(ptr->lchild);
    printf("%d\n",ptr->data);
    inorder(ptr->rchild);
  }
}

void insert(int item)
{
    struct node* ptr=root,*new,*prev;
    new=newNode(item);
    if(ptr==NULL)
    {
      root=new;
      return ;
    }

    while(ptr!=NULL)
    {
        if(item>ptr->data)
        {
            prev=ptr;
            ptr=ptr->rchild;
        }
        else if(item<ptr->data)
              {
                  prev=ptr;
                  ptr=ptr->lchild;
              }
              else
              {
                  printf("Item alrady found\n");
                  free(new);
                  return ;
              }
    }
    if(prev!=NULL)
    {
        if(item>prev->data)
            prev->rchild=new;
        else 
            prev->lchild=new;
    }

}

struct node* inSucsr(struct node* ptr)
{
  struct node* temp;
  if(ptr==NULL)
  {
    printf("INVALID\n");
    return NULL;
  }
  temp=ptr->rchild;
  if(temp!=NULL)
  {
    while(temp->lchild!=NULL)
        temp=temp->lchild;
  }
  return temp;
}

void delete(int item)
{
  struct node* ptr=root,*prev=root;
  int Case;
  if(ptr==NULL) 
  {
    printf("no items found\n");
    return;
  }
  //search for the item
  while(ptr!=NULL)
  {
    if(item>ptr->data)
    {
      prev=ptr;
      ptr=ptr->rchild;
    }
    else if(item<ptr->data)
          {
            prev=ptr;
            ptr=ptr->lchild;
          }
          else 
            break;
  }

  if(ptr==NULL)
  {
    printf("%d not found\n",item);
    return;
  }

  if(ptr->lchild==NULL && ptr->rchild==NULL)
        Case=1;
  else if(ptr->lchild!=NULL && ptr->rchild!=NULL) 
              Case=3;
        else 
              Case=2;

  if(Case==1)//case is a keyword
  {
    if(ptr==prev)
    {
      free(ptr);
      root=NULL;
      return ;
    }
    if(prev->lchild==ptr)
      prev->lchild=NULL;
    else if(prev->rchild==ptr)
            prev->rchild=NULL;
    free(ptr);

  }

  if(Case==2)
  {
    if(ptr==prev)
    {
      if(ptr->lchild!=NULL)
          root=ptr->lchild;
      else
        root=ptr->rchild;
      free(ptr);
      return ;
    }
    if(prev->lchild==ptr)
    {
      if(ptr->lchild!=NULL)
          prev->lchild=ptr->lchild;
      else if(ptr->rchild!=NULL)
              prev->lchild=ptr->rchild;
    }
    else if(prev->rchild==ptr)
          {
              if(ptr->lchild!=NULL)
                 prev->rchild=ptr->lchild;
              else if(ptr->rchild!=NULL)
                        prev->rchild=ptr->rchild;
          }
    free(ptr);
  }

  if(Case==3)
  {
      int item;
      struct node* temp=inSucsr(ptr);
      item=temp->data;
      delete(item);
      ptr->data=item;
  }
}

int leafnode(struct node* ptr)
{
  if(ptr->lchild==NULL && ptr->rchild==NULL)
    return 1;
  return leafnode(ptr->lchild)+leafnode(ptr->rchild);
 
}

void returnNode(struct node* ptr)
{
  if(ptr!=NULL)
  {
    returnNode(ptr->lchild);
    returnNode(ptr->rchild);
    free(ptr);
  }
}

void main()
{
  int option,num,choice;
  
  do
  {
     printf("Enter your choice:\n1)INSERT\n2)DELETE\n3)SORT\n4)DISPLAY\n5)Count Leafnode\n6)EXIT\n");
     scanf("%d",&option);
    switch(option)
    {
      case 1:printf("Enter the no to be inserted: ");
            scanf("%d",&num);
            insert(num);
            inorder(root);
            break;
      case 2:printf("Enter the num to be deleted: ");
              scanf("%d",&num);
              delete(num);
              inorder(root);
              break;
      case 3:printf("Sorted order is:\n");
              inorder(root);
              break;
      case 4:printf("enter your choice:\n1)inorder\n2)preorder\n3)postorder\n");
             scanf("%d",&choice);
             switch(choice)
             {
              case 1:inorder(root);
                     break;
             }
              break;
      case 5:printf("The no of leafnodes=%d\n",leafnode(root));
              break;
      case 6:returnNode(root);
              printf("successfully freed memory\n");
              return;
      default:printf("Invalid choice.Enter again..\n");         
    }
  }
  while(1);
}