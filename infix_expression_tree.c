#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Cnode
{
  char data;
  struct Cnode* link;
}*charhead,*Ctop=NULL;

struct TreeNode
{
  char data;
  struct TreeNode* lchild,*rchild;
}*root;

struct TSnode
{
  struct TreeNode* data;
  struct TSnode* link; 
}*TShead,*Ntop=NULL;


void charPush(char item)
{
  struct Cnode* new=(struct Cnode*)malloc(sizeof(struct Cnode));
  new->data=item;
  new->link=charhead->link;
  charhead->link=new;
  Ctop=new;
}

void NodePush(struct TreeNode* item)
{
  struct TSnode* new=(struct TSnode*)malloc(sizeof(struct TSnode));
  new->data=item;
  new->link=TShead->link;
  TShead->link=new;
  Ntop=new;
}

char charPop()
{
  struct Cnode* ptr=charhead->link;
  //char item=charhead->data;
  if(charhead->link==NULL)
    return '#';
  char item=ptr->data;
  charhead->link=ptr->link;
  Ctop=charhead->link;
  free(ptr);
  return item;
}

struct TreeNode* NodePop()
{
  struct TSnode* ptr=TShead->link;
  //char item=charhead->data;
  if(TShead->link==NULL)
    return NULL;
  struct TreeNode* item=ptr->data;
  TShead->link=ptr->link;
  Ntop=TShead->link;
  free(ptr);
  return item;
}

struct TreeNode* newTnode(char data)
{
  struct TreeNode* new=(struct TreeNode*)malloc(sizeof(struct TreeNode));
  new->data=data;
  new->lchild=new->rchild=NULL;
}

int isp(char ch)
{
  switch(ch)
  {
    case '+':
    case '-':return 2;
    case '*':
    case '/':return 4;
    case '^':return 5;
    case '(':return 0;
  }
}

int icp(char ch)
{
  switch(ch)
  {
    case '+':
    case '-':return 1;
    case '*':
    case '/':return 3;
    case '^':return 6;
    case '(':return 7;
  }
}

int isOperand(char c)
{
  return c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9';
}

void createExpnTree(char infix[])
{
  int i;
  charPush('(');
  strcat(infix,")");

  for(i=0 ; infix[i]!='\0' ; i++)
  {
    if(isOperand(infix[i]))
    {
      struct TreeNode* new=newTnode(infix[i]);
      NodePush(new);
    }
    else if(infix[i]==')')
         {
            while(Ctop!=NULL && Ctop->data!='(')
            {
              char optr=charPop();
              struct TreeNode* t=newTnode(optr),*t1,*t2;
              t1=NodePop();
              t2=NodePop();
              t->lchild=t1;
              t->rchild=t2;
              NodePush(t);
            }
            charPop();
         }
         else
         {
            while(icp(infix[i]<=isp(Ctop->data)) && Ctop!=NULL && Ntop!=NULL)
            {
              char optr=charPop();
              struct TreeNode* t=newTnode(optr);
              struct TreeNode* t1,*t2;
              t1=NodePop();
              t2=NodePop();
              t->lchild=t1;
              t->rchild=t2;
              NodePush(t);
            }
            charPush(infix[i]);
         }
  }

}

void preorder(struct TreeNode* ptr)
{
  if(ptr!=NULL)
  {
    printf("%c",ptr->data);
    preorder(ptr->lchild);
    preorder(ptr->rchild);
  }
}

void main()
{
  char infix[30];
  TShead=(struct TSnode*)malloc(sizeof(struct TSnode));
  charhead=(struct Cnode*)malloc(sizeof(struct Cnode));

  printf("Enter an infix expression: ");
  scanf(" %[^\n]",infix);

  createExpnTree(infix);

  preorder(root);
  printf("\n");
}