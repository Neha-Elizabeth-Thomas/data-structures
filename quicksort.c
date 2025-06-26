#include<stdio.h>

void swap(int* i,int* j)
{
  int temp=*i;
  *i=*j;
  *j=temp;
}
int Partition(int a[],int low,int high)
{
  int pivot=a[low],i=low,j=high,temp;

  while(i<j)
  {
    while(a[i]<=pivot)
      i++;
    while(a[j]>pivot)
      j--;
    if(i<j)
    {
      /*temp=a[i];
      a[i]=a[j];
      a[j]=temp;*/
      swap(&a[i],&a[j]);
    }
  }
  /*temp=a[low];
  a[low]=a[j];
  a[j]=temp;*/
  swap(&a[low],&a[j]);
  return j;
}
void Quicksort(int a[],int low,int high)
{
  if(low<high)
  {
    int j=Partition(a,low,high);
    Quicksort(a,low,j-1);
    Quicksort(a,j+1,high);
  }
}
void main()
{
  int n,a[10],i;

  printf("How many ellemnts?");
  scanf("%d",&n);

  printf("Enter %d numbers: \n",n);
  for(i=0 ; i<n ; i++)
    scanf("%d",&a[i]);
  a[n]=99999;
  Quicksort(a,0,n-1);

  printf("Sorted array:\n");
  for(i=0 ; i<n ; i++)
    printf("%d\n",a[i]);
}