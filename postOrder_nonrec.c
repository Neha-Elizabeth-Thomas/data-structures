#include<stdio.h>
#include<stdlib.h>

struct node{
  int data;
  struct node* lchild;
  struct node* rchild;
  int visited;
};

struct Snode{
  struct node* data;
  struct Snode* link;
}*head,*top=NULL;


struct Snode* newSNode(struct node* data)
{
  struct Snode* new=(struct Snode*)malloc(sizeof(struct Snode));
  new->data=data;
  new->link=NULL;
  return new;
}

void push(struct node* item)
{
  struct Snode* new=newSNode(item);
  new->link=head->link;
  head->link=new;
  top=head->link;
}

struct node* pop()
{
  struct Snode* ptr;
  struct node* item;
  if(top==NULL)
    return NULL;
  ptr=head->link;
  item=ptr->data;
  head->link=ptr->link;
  free(ptr);
  top=head->link;
  return item;
}


struct node* newNode()
{
  struct node* new=(struct node*)malloc(sizeof(struct node));
  new->lchild=new->rchild=NULL;
  new->visited=0;
  return new;
}

void inorder(struct node* root)
{
  struct node* ptr=root;

  while(ptr!=NULL || top!=NULL)
  {
    while(ptr!=NULL)
    {
      push(ptr);
      ptr=ptr->lchild;
    }
    if(top!=NULL)
    {
      struct node* temp=pop();
      printf("%d\t",temp->data);
      ptr=temp->rchild;
    }
  }
}

void preorder(struct node* root)
{
  struct node* ptr=root;
  while(ptr!=NULL || top!=NULL)
  {
    while(ptr!=NULL)
    {
      printf("%d\t",ptr->data);
      push(ptr);
      ptr=ptr->lchild;
    }
    if(top!=NULL)
      ptr=pop()->rchild;

  }
}

void postorder(struct node* root)
{
  struct node* ptr;
  ptr=root;
  while(ptr!=NULL && !ptr->visited)
  {
    if(ptr->lchild!=NULL && !ptr->lchild->visited)
      ptr=ptr->lchild;
    else if(ptr->rchild!=NULL && ptr->rchild->visited==0)
            ptr=ptr->rchild;
          else
          {
              printf("%d\t",ptr->data);
              ptr->visited=1;
              ptr=root;
          }
  }
}

void BuildTree(struct node* ptr,int item)
{
  int num; char option;
  struct node* new;
  if(ptr!=NULL)
  {
    ptr->data=item;

    printf("does %d has left child(y/n)? ",item);
    scanf(" %c",&option);
    if(option=='y'||option=='Y')
    {
      printf("Enter the left child: ");
      scanf("%d",&num);
      new=newNode();
      ptr->lchild=new;;
      BuildTree(new,num);
    }

    printf("does %d has right child(y/n)? ",item);
    scanf(" %c",&option);
    if(option=='y'||option=='Y')
    {
      printf("Enter the right child: ");
      scanf("%d",&num);
      new=newNode();
      ptr->rchild=new;;
      BuildTree(new,num);
    }
  }
}

void main()
{
  struct node* root=newNode();
  BuildTree(root,1);
  head=newSNode(NULL);
  postorder(root);
  printf("\n\n");
  inorder(root);
  printf("\n\n");
  preorder(root);
}

