#include<stdio.h>

void merge(int a[],int low,int mid,int high)
{
  int i=low,j=mid+1,k=0,b[10],p;

  while(i<=mid && j<=high)
  {
    if(a[i]<a[j])
    {
      b[k]=a[i];
      i++; k++;
    }
    else 
    {
      b[k]=a[j];
      k++; j++;
    }
  }
  while(i<=mid)
  {
    b[k]=a[i];
    k++; i++;
  }
  while(j<=high)
  {
    b[k]=a[j];
    k++; j++;
  }
  for(p=0 ; p<k ; p++)
    a[low+p]=b[p];
}

void mergeSort(int a[],int low,int high)
{
  if(low<high)
  {
    int mid=(low+high)/2;
    mergeSort(a,low,mid);
    mergeSort(a,mid+1,high);
    merge(a,low,mid,high);
  }
}

void main()
{
  int a[10],n,i;
  printf("How many elements?");
  scanf("%d",&n);

  printf("Enter %d numbers to sort: \n",n);
  for(i=0 ; i<n ; i++)
    scanf("%d",&a[i]);

  mergeSort(a,0,n-1);

  printf("%d numbers in sorted order:\n",n);
  for(i=0 ; i<n ; i++)
    printf("%d\n",a[i]);
}