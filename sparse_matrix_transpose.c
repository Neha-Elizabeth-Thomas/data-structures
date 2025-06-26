#include<stdio.h>
#include<stdlib.h>
struct term
{
  int row;
  int col;
  int val;
};
int checkSparse(int A[][5],int m,int n)
{
  int i,j,countofZero=0;
  for(i=0 ; i<m ; i++)
    for(j=0 ; j<n ; j++)
      if(A[i][j]==0)
        countofZero++;

  if(countofZero >= (m*n)/2)
    return 0;
  else
    return 1;
}
void toTriplet(int A[][5],int m,int n,struct term B[])
{
  int i,j,k=1,nz=0;
  for(i=0 ; i<m ; i++)
    for(j=0 ; j<n ; j++)
      if(A[i][j]!=0)
      {
        B[k].row=i;
        B[k].col=j;
        B[k].val=A[i][j];
        k++;
        nz++;
      }
  B[0].row=m;
  B[0].col=n;
  B[0].val=nz;//k-1
}
void toTranspose(struct term B[],struct term C[])
{
  int i,j,k=1;
  C[0].row=B[0].col;
  C[0].col=B[0].row;
  C[0].val=B[0].val;

  for(i=0 ; i<B[0].col ; i++)
  {
    for(j=1 ; j<=B[0].val ; j++)
    {
      if(i==B[j].col)
      {
        C[k].row=B[j].col;
        C[k].col=B[j].row;
        C[k].val=B[j].val;
        k++;
      }
    }
  }
}
void display(struct term A[])
{
  int i;
  for(i=0 ; i<=A[0].val ; i++)
  {
    printf("%-5d %-5d %-5d\n",A[i].row,A[i].col,A[i].val);
  }
}
void main()
{
  int A[5][5],m,n,i,j,nz;
  struct term B[10],C[10];
  printf("Enter the order of a matrix: ");
  scanf("%d %d",&m,&n);
  printf("Enter a %d*%d matrix:\n",m,n);
  for(i=0 ; i<m ; i++)
    for(j=0 ; j<n ; j++)
      scanf("%d",&A[i][i]);

 /* if(!checkSparse(A,m,n))
  {
    printf("Given matrix is not sparse\n");
    return;
  }*/

  toTriplet(A,m,n,B);
  toTranspose(B,C);

  printf("Sparse Matrix: \n");
  //display(A,m,n);
  printf("Triplet representation of the above matrix is:\n");
  display(B);
  printf("Transpose of the above matrix: \n");
  display(C);


}
