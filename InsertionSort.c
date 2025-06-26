#include<stdio.h>

void insertionSort(int a[],int n)
{
   int i,j,temp;
   for(i=1 ; i<n ; i++)
   {
      //num to be inserted is a[i]
      temp=a[i];
      j=i-1;
      while(j>=0 && a[j]>temp)
      {
         a[j+1]=a[j];//shift and produce space
         j--;
       //you can now insert temp in position j+1.To insert go out of loop        
      }
      //insert temp at j+1 th position if j==-1 or A[j]<=temp
      a[j+1]=temp;
   }
}

void main()
{
   int a[10],n,i;
   printf("How many elements: ");
   scanf("%d",&n);

   printf("Enter %d numbers: ",n);
   for(i=0 ; i<n ; i++)
      scanf("%d",&a[i]);

   insertionSort(a,n);

   printf("Sorted array:\n");
   for(i=0 ; i<n ; i++)
      printf("%d\n",a[i]);
}