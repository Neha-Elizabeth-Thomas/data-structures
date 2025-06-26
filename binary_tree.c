#include<stdio.h>
#include<stdlib.h>

struct node{
  int data;
  struct node* lchild;
  struct node* rchild;
}*root;

struct qnode{
  struct node* data;
  struct qnode* link;
}*head,*front=NULL,*rear=NULL;

void Enqueue(struct node* item)
{
  struct qnode* new=(struct qnode*)malloc(sizeof(struct qnode));
  new->data=item;
  if(front==NULL)
  {
    new->link=NULL;
    head->link=new;
    front=rear=new;
  }
  else
  {
    new->link=rear->link;//NULL
    rear->link=new;
    rear=new;
  }
}

struct node* Dequeue()
{
  if(front==NULL)
    return NULL;
  else
  {
    struct node* item=front->data;
    head->link=front->link;
    free(front);
    front=head->link;
    if(front==NULL)
      rear=NULL;
    return item;
  }
}

struct node* newTnode(int num)
{
  struct node* new=(struct node*)malloc(sizeof(struct node));
  new->data=num;
  new->lchild=new->rchild=NULL;
  return new;
}

void insert(struct node* root,int num)
{
  struct node* new=newTnode(num);
  if(root==NULL)
  {
    root=new;
    return ;
  }
  Enqueue(root);
  while(front!=NULL)
  {
    struct node* temp=Dequeue();
    if(temp->lchild!=NULL)
      Enqueue(temp->lchild);
    else
    {
      temp->lchild=new;
      break;
    }

    if(temp->rchild!=NULL)
      Enqueue(temp->rchild);
    else
    {
      temp->rchild=new;
      break;
    }
  }
}

void delete(struct node* root,int key)
{
  struct node* keynode=NULL,*temp,*prev;

  if(root!=NULL && root->lchild==NULL && root->rchild==NULL&&root->data==key)
  {
    root=NULL;
    return ;
  }
  Enqueue(root);

  while(front!=NULL)
  {
    temp=Dequeue();
    if(temp->data==key)
    {
      keynode=temp;
    }
    if(temp->lchild!=NULL)
    {
      prev=temp;
      Enqueue(temp->lchild);
    }
    if(temp->rchild!=NULL)
    {
      prev=temp;
      Enqueue(temp->rchild);
    }
  }
  if(keynode!=NULL)
  {
    keynode->data=temp->data;
    //free(temp);
    if(prev->lchild==temp)
      prev->lchild=NULL;
    else
      prev->rchild=NULL;
    free(temp);
  }
}

void preorder(struct node* ptr)
{
  if(ptr!=NULL)
  {
    printf("%d\n",ptr->data);
    preorder(ptr->lchild);
    preorder(ptr->rchild);
  }
}

void inorder(struct node* ptr)
{
  if(ptr!=NULL)
  {
    inorder(ptr->lchild);
    printf("%d\n",ptr->data);
    inorder(ptr->rchild);
  }
}

void postorder(struct node* ptr)
{
  if(ptr!=NULL)
  {
    postorder(ptr->lchild);
    postorder(ptr->rchild);
    printf("%d\n",ptr->data);
  }
}

void returnNode(struct node* ptr)
{
  if(ptr!=NULL)
  {
    struct node* temp=ptr;
    inorder(ptr->lchild);
    free(ptr);
    inorder(temp->rchild);
  }
}

void main()
{
  int choice,num,key;
  head=(struct qnode*)malloc(sizeof(struct qnode));
  head->link=NULL;
  printf("Enter the root: ");
  scanf("%d",&num);
  root=newTnode(num);
  do
  {
    printf("Enter your choice:\n1)Insertion\n2)Inorder traversal\n3)Preorder traversal\n4)Postorder Traversal\n5)Deletion\n6)Exit\n");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1:printf("Enter the data to be inserted: ");
             scanf("%d",&num);
             insert(root,num);
             break;
      case 2:printf("Inorder traversal\n");
            inorder(root);
             break;
      case 3:printf("preorder traversal\n");
            preorder(root);
            break;
      case 4:printf("postorder traversal\n");
             postorder(root);
             break;
      case 5:printf("Enter the number to be deleted: ");
             scanf("%d",&key);
             delete(root,key);
             break;
      case 6:returnNode(root);
            return;
      default:returnNode(root);
            return;
      
    }
  }
  while(1);
}