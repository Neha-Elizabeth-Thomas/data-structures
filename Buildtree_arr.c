#include<stdio.h>
#define SIZE 30
int a[30];

void BuildTree(int i,int item)
{
  char option;
  int num;
  if(i!=0)
  {
    a[i]=item;
    printf("does %d has left child?(y/n) ",item);
    scanf(" %c",&option);
    if(option=='y' || option=='Y')
    {
      printf("Enter the left child: ");
      scanf("%d",&num);
      BuildTree(2*i,num);
    }

    printf("does %d has right child?(y/n) ",item);
    scanf(" %c",&option);
    if(option=='y' || option=='Y')
    {
      printf("Enter the right child: ");
      scanf("%d",&num);
      BuildTree(2*i+1,num);
    }
  }
}

void inorder(int A[],int i){
  if(i>=SIZE || A[i]==0)
    return;
  inorder(A,2*i);
  printf("%d\n",A[i]);
  inorder(A,2*i+1);
}


void main()
{
  int root,i;
  /*for(i=0 ; i<30 ; i++) //global variables are automatically initialized with 0
    a[i]=0;*/
  printf("Enter the root: ");
  scanf("%d",&root);
  BuildTree(1,root);

  printf("lINEAR REPRESENTATION OF binary tree:\n");
  for(i=1 ; i<30 ; i++)
    printf("%d\n",a[i]);
  printf("\n");
}