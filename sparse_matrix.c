#include<stdio.h>

void toTriplet(int A[][5],int m,int n,int B[][3])
{
  int i,j,k,nz;
  nz=0;
  k=1;
  for(i=0 ; i<m ; i++)
    for(j=0 ; j<n ; j++)
      if(A[i][j]!=0)
      {
        B[k][0]=i;
        B[k][1]=j;
        B[k][2]=A[i][j];
        k++;
        nz++;
      }
  B[0][0]=m;
  B[0][1]=n;
  B[0][2]=nz;//k-1

}

void readmat(int A[][5],int m,int n)
{
  int i,j;
  for(i=0 ; i<m ; i++)
    for(j=0 ; j<n ; j++)
      scanf("%d",&A[i][j]);
}

void display(int A[][5],int m,int n)
{
  int i,j;
  for(i=0 ; i<m ; i++)
  {
    for(j=0 ; j<n ; j++)
      printf("%-5d",A[i][j]);
    printf("\n");
  }
}

void toTranspose(int A[][5],int B[][5])
{
  int i,j,k=1;

  B[0][0]=A[0][1];
  B[0][1]=A[0][0];
  B[0][2]=A[0][2];
  for(i=0 ; i<A[0][1] ; i++)
  {
    for(j=1 ; j<=A[0][2] ; j++)
    {
      if(A[j][1]==i)
      {
        B[k][0]=A[j][1];
        B[k][1]=A[j][0];
        B[k][2]=A[j][2];
        k++;
      }
    }
  }
}

int checkSparse(int A[][5],int m,int n)
{
  int i,j,countofZero=0;
  for(i=0 ; i<m ; i++)
    for(j=0 ; j<n ; j++)
      if(A[i][j]==0)
        countofZero++;
  return countofZero>=(m*n)/2;
}
void main()
{
  int A[5][5],m,n,B[5][5],C[5][5];

  printf("Enter the order of matrix: ");
  scanf("%d %d",&m,&n);
  printf("Enter the elements of %d*%d matrix:\n",m,n);
  readmat(A,m,n);
  printf("Sparse matrix:\n");
  display(A,m,n);

  if(checkSparse(A,m,n)==0)
  {
    printf("The matrix is not sparse\n");
    return;
  }

  toTriplet(A,m,n,B);
  printf("Triplet representation:\n");
  display(B,B[0][2]+1,3);

  toTranspose(B,C);
  printf("Transpose Triplet representation:\n");
  display(C,C[0][2]+1,3);
}