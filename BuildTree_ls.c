#include<stdio.h>
#include<stdlib.h>

struct node 
{
  int data;
  struct node* lchild;
  struct node* rchild;
};
struct node* root;

struct stknode
{
  struct node* data;
  struct stknode* link;
};
struct stknode* head,*top=NULL,*head2,*top2=NULL;

void push(struct stknode* head,struct stknode* top,struct node* item)
{
  struct stknode* new=(struct stknode*)malloc(sizeof(struct stknode));
  new->data=item;
  new->link=head->link;
  head->link=new;
  top=head->link;
}

struct node* pop(struct stknode* head,struct stknode* top)
{
  struct node* item;
  struct stknode* ptr=head->link;
  if(ptr==NULL)
    return NULL;
  item=ptr->data;
  head->link=ptr->link;
  free(ptr);
  top=head->link;
  return item;
}

int isEmpty()
{
  if(top==NULL)
    return 1;
  else
    return 0;
}

void inorder()
{
  struct node* ptr=root;
  while(ptr!=NULL || !isEmpty())//or is v.imp
  {
    while(ptr!=NULL)
    {
      push(head,top,ptr);
      ptr=ptr->lchild;
    }
    if(!isEmpty())
    {
      struct node* temp=pop(head,top);
      printf("%d\n",temp->data);
      ptr=temp->rchild;
    }
  }

}

void preorder(struct node* root)
{
  struct node* ptr=root;
  while(ptr!=NULL || !isEmpty())
  {
    while(ptr!=NULL)
    {
      printf("%d\n",ptr->data);
      push(head,top,ptr);
      ptr=ptr->lchild;
    }
    if(!isEmpty())
    {
      ptr=pop(head,top)->rchild;
    }
  }

}

void postorder()
{
  push(head,top,root);
  while(top!=NULL)
  {
    struct node* temp=pop(head,top);
    push(head2,top2,temp);
    if(temp->lchild)
      push(head,top,temp->lchild);
    if(temp->rchild)
      push(head,top,temp->rchild);
  }
  while(top2!=NULL)
  {
    printf("%d\t",pop(head2,top2)->data);
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
      new=(struct node*)malloc(sizeof(struct node));
      new->lchild=NULL;
      new->rchild=NULL;
      ptr->lchild=new;;
      BuildTree(new,num);
    }

    printf("does %d has right child(y/n)? ",item);
    scanf(" %c",&option);
    if(option=='y'||option=='Y')
    {
      printf("Enter the right child: ");
      scanf("%d",&num);
      new=(struct node*)malloc(sizeof(struct node));
      new->lchild=NULL;
      new->rchild=NULL;
      ptr->rchild=new;;
      BuildTree(new,num);
    }
  }
}



/*void preorder(struct node* ptr)
{
  if(ptr!=NULL)
  {
    printf("%d\n",ptr->data);
    preorder(ptr->lchild);
    preorder(ptr->rchild);
  }
}*/

/*void inorder(struct node* ptr)
{
  if(ptr!=NULL)
  {
    inorder(ptr->lchild);
    printf("%d\n",ptr->data);
    inorder(ptr->rchild);
  }
}*/

/*void postorder(struct node* ptr)
{
  if(ptr!=NULL)
  {
    postorder(ptr->lchild);
    postorder(ptr->rchild);
    printf("%d\n",ptr->data);
  }
}*/

int maxDepth(struct node* ptr)
{
  if(ptr->lchild!=NULL && ptr->rchild!=NULL)
    return 0;
  return max(maxDepth(ptr->lchild),maxDepth(ptr->rchild))+1;
}

int height(struct node* ptr){
  if(ptr==NULL)
    return 0;

  return max(height(ptr->lchild),height(ptr->rchild))+1;
}

int terminalNodes(struct node* ptr)
{
  if(ptr==NULL)
    return 0;
  if(ptr->lchild==NULL && ptr->rchild==NULL)
    return 1;

  return terminalNodes(ptr->lchild)+terminalNodes(ptr->rchild);

  /*static int count=0;

  if(ptr!=NULL)
  {
    if(ptr->lchild==NULL && ptr->rchild==NULL)
      count++;
    terminalNodes(ptr->lchild);
    terminalNodes(ptr->rchild);
    return count;
  }
  //return 0;*/
}

int countNode(struct node* ptr)
{
  if(ptr==0)
    return 0;
  return count(ptr->lchild)+count(ptr->rchild)+1;
  //return count;
}
void main()
{
  int num;
  root=(struct node*)malloc(sizeof(struct node));
  root->lchild=NULL;
  root->rchild=NULL;

  head=(struct stknode*)malloc(sizeof(struct stknode));
  head->link=NULL;
  head2=(struct stknode*)malloc(sizeof(struct stknode));
  head2->link=NULL;

  printf("enter the root: ");
  scanf("%d",&num);
  BuildTree(root,num);

 // printf("INORDER:\n");
  //inorder();

  printf("Total number of nodes=%d\n",countNode(root));
  printf("maximum depth=%d\n",maxDepth(root));
  printf("maximum no of terminal nodes=%d\n",terminalNodes(root));
  printf("PREORDER representation:\n");
  preorder(root);

  printf("INORDER representation:\n");
  //inorder(root);
  inorder();

  printf("POSTORDER representation:\n");
  postorder();
}