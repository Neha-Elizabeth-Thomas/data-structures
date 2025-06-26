#include<stdio.h>
#include<stdlib.h>
#define SIZE 20

struct node{
  int data;
  struct node* lchild;
  struct node* rchild;
}*root=NULL;

struct node* newNode(){
  struct node* new=(struct node*)malloc(sizeof(struct node));
  new->lchild=new->rchild=NULL;
  return new;
}

void BuildTree(struct node* ptr,int data){
  char option;
  if(ptr==NULL) return;

  ptr->data=data;

  printf("does %d has lchild(y/n)?",data);
  scanf(" %c",&option);
  if(option=='y' || option=='Y'){
    int item;
    struct node* new=newNode();
    ptr->lchild=new;
    printf("Enter the lchild: ");
    scanf("%d",&item);
    BuildTree(new,item);
  }else
    ptr->lchild=NULL;

  printf("does %d has rchild(y/n)?",data);
  scanf(" %c",&option);
  if(option=='y' || option=='Y'){
    int item;
    struct node* new=newNode();
    ptr->rchild=new;
    printf("Enter the rchild: ");
    scanf("%d",&item);
    BuildTree(new,item);
  }else
    ptr->rchild=NULL;

}

struct node* S[SIZE];
int top=-1;

void push(struct node* item){
  if(top==SIZE-1)
    printf("stack overflow\n");
  else
    S[++top]=item;
}

struct node* pop(){
  if(top==-1)
    printf("stack empty\n");
  else
    return S[top--];
}

void inorder_iter(struct node* root){
  struct node* ptr=root;

  printf("INORDER:\n");
  while(ptr!=NULL || top!=-1){
    while(ptr!=NULL){
      push(ptr);
      ptr=ptr->lchild;
    }
    if(top!=-1){
      struct node* temp=pop();
      printf("%d\n",temp->data);
      ptr=temp->rchild;
    }
  }
}

void preorder_iter(struct node* root){
  struct node* ptr=root;
  printf("preorder: \n");
  while(ptr!=NULL || top!=-1){
    while(ptr!=NULL){
      printf("%d\n",ptr->data);
      push(ptr);
      ptr=ptr->lchild;
    }

    if(top!=-1){
      struct node* temp=pop();
      ptr=temp->rchild;
    }
  }
}

void postorder_iter(struct node* root){
  struct  node* ptr=root;

  printf("POSTORDER: \n");
  do{   
    while(ptr!=NULL){
      if(ptr->rchild!=NULL)
        push(ptr->rchild);
      push(ptr);
      ptr=ptr->lchild;
    }

    if(top!=-1){
      ptr=pop();

      if(ptr->rchild!=NULL && S[top]==ptr->rchild){
        pop();
        push(ptr);
        ptr=ptr->rchild;
      }
      else
      {
        printf("%d\n",ptr->data);
        ptr=NULL;
      }
    }
  }while(top!=-1);
}

void inorder(struct node* ptr){
  if(ptr==NULL) return;

  inorder(ptr->lchild);
  printf("%d\n",ptr->data);
  inorder(ptr->rchild);
}

void preorder(struct node* ptr){
  if(ptr==NULL) return;

  printf("%d\n",ptr->data);
  preorder(ptr->lchild);
  preorder(ptr->rchild);
}

void postorder(struct node* ptr){
  if(ptr==NULL) return;

  postorder(ptr->lchild);
  postorder(ptr->rchild);
  printf("%d\n",ptr->data);
}

int max(int a,int b){
 return a>b?a:b;
}

/*int maxDepth(struct node* ptr)
{
  if(ptr->lchild!=NULL && ptr->rchild!=NULL)
    return 0;
  return max(maxDepth(ptr->lchild),maxDepth(ptr->rchild))+1;
}*/

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
}

int countNode(struct node* ptr)
{
  if(ptr==0)
    return 0;
  return countNode(ptr->lchild)+countNode(ptr->rchild)+1;
  //return count;
}

void destroy(struct node* root){
  if(root==NULL) return;

  destroy(root->lchild);
  destroy(root->rchild);
  free(root);
}

void main(){
  int rt;
  root=newNode();
  printf("Enter the root: ");
  scanf("%d",&rt);

  BuildTree(root,rt);

  printf("INORDER\n");
  inorder(root);
  inorder_iter(root);

  printf("preORDER\n");
  preorder(root);
  preorder_iter(root);

  printf("postRDER\n");
  postorder(root);
  postorder_iter(root);

  printf("\ncountNode: %d",countNode(root));
  printf("\nterminalNodes: %d",terminalNodes(root));
  printf("\nheight: %d",height(root));
  printf("\nmaxdepth: %d\n",height(root)-1);
  destroy(root);
}