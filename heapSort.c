#include<stdio.h>

void swap(int* a,int* b)
{
  int temp=*a;
  *a=*b;
  *b=temp;
}

//from i to downwards it is heapified
void maxHeapify(int A[],int n,int i)
{
  int largest,left,right;
  largest=i;
  left=2*i;
  right=2*i+1;

  if(left<=n && A[left]>A[largest])
    largest=left;
  if(right<=n && A[right]>A[largest])
    largest=right;

  if(largest!=i)  
  {
    swap(&A[i],&A[largest]);
    //since A[largest] is now changed you have to check to maintain a heap down it
    maxHeapify(A,n,largest);
  }
}

void display(int a[],int n)
{
  int i;
  for(i=1 ; i<=n ; i++)  //always remember index starts from 1
    printf("%d\t",a[i]);
}

void heapsort(int A[],int n)
{
  //start from the nonleaf node at the largest index,which is at n/2
  int i;
  for(i=n/2 ; i>=1 ; i--)
    maxHeapify(A,n,i);

  printf("The array is now max heapified.\nMAXHEAP: ");
  display(A,n);

  //after creating heap you need to perfoem deletion(and storing back) to obtain sorted array
  //always delete root node i.e 1st element
  //deletion can be easily performed by swapping 1st and last element(of the current heap)
  //but after swapping ensure that heap is maintained from the 1st node itself
  for(i=n ; i>=1 ; i--)
  {
    swap(&A[1],&A[i]);
    maxHeapify(A,i-1,1);
  }
}
void main()
{
  int a[11],n,i;
  a[0]=9999;//not needed
  printf("How many numbers?");
  scanf("%d",&n);

  printf("Enter %d numbers: ",n); 
  for(i=1 ; i<=n ; i++)
    scanf("%d",&a[i]);//index starts at 1

  printf("Inorder to sort the array this array is considered as a complete binary tree\n\n");
  heapsort(a,n);

  printf("\n\n%d numbers sorted in ascending order: \n");
  display(a,n);
}