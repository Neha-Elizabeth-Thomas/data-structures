#include<stdio.h>
#include<stdlib.h>
#define INVALID -9999


void swap(int *a,int *b){
  int temp=*a;
  *a=*b;
  *b=temp;
}

void display(int A[],int n){
  int i;
  printf("array:\n");
  for(i=0 ; i<n ; i++)
    printf("%5d",A[i]);
  printf("\n");
}

void selectionSort(int A[],int n){
  int i,j;
  for(i=0 ; i<n-1 ; i++){
    int minindex=i;
    for(j=i+1 ; j<n ; j++){
      if(A[j]<A[minindex])
        minindex=j;
    }
    if(minindex!=i){
      swap(&A[i],&A[minindex]);
    }
  }
}

void main(){
  int A[10],n,i;

  printf("how many elements?");
  scanf("%d",&n);

  printf("enter %d numbers: \n",n);
  for(i=0 ; i<n ; i++)
    scanf("%d",&A[i]);
  
  display(A,n);

  selectionSort(A,n);

  display(A,n);
}