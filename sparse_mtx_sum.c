#include<stdio.h>
void readMat(int A[][10],int m,int n)
{
  int i,j;
  for(i=0 ; i<m ; i++)
    for(j=0 ; j<n ; j++)
      scanf("%d",&A[i][j]);
}
void toTuple(int A[][10],int m,int n,int B[][3])
{
  int i,j,k;
  k=1;
  for(i=0 ; i<m ; i++)
    for(j=0 ; j<n ; j++)
        if(A[i][j]!=0)
        {
          B[k][0]=i;
          B[k][1]=j;
          B[k][2]=A[i][j];
          k++;
        }
  B[0][0]=m;
  B[0][1]=n;
  B[0][2]=k-1;
}

void toTranspose(int A[][3],int B[][3])
{
  int i,j,k;
  B[0][0]=A[0][1];
  B[0][1]=A[0][0];
  B[0][2]=A[0][2];
  k=1;
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

void display(int A[][3])
{
  int i;
  for(i=0 ; i<=A[0][2] ; i++)
    printf("%5d%5d%5d\n",A[i][0],A[i][1],A[i][2]);
  printf("\n");
}

void addTuple(int A[][3],int B[][3],int C[][3])
{
  int i,j,k,p,q;
  if(A[0][0]!=B[0][0] || A[0][1]!=B[0][1])
    printf("Addition impossible\n");
  else
  {
    p=1; q=1,k=1;
    for(i=0 ; i<A[0][0] ; i++)
      for(j=0 ; j<A[0][1] ; j++)//time complexity=O(m*n)
      {
          if(p<=A[0][2] && q<=B[0][2] && A[p][0]==i && A[p][1]==j && B[q][0]==i && B[q][1]==j)
          {
              C[k][0]=i;
              C[k][1]=j;
              C[k][2]=A[p][2]+B[q][2];
              k++;
              p++;
              q++;
          }
          else if(p<=A[0][2] && A[p][0]==i && A[p][1]==j)
                {
                  C[k][0]=i;
                  C[k][1]=j;
                  C[k][2]=A[p][2];
                  k++;
                  p++;
                }
                else if(q<=B[0][2] && B[q][0]==i && B[q][1]==j)
                      {
                        C[k][0]=i;
                        C[k][1]=j;
                        C[k][2]=B[q][2];
                        k++;
                        q++;
                      }
      }
      C[0][0]=A[0][0];
      C[0][1]=A[0][1];
      C[0][2]=k-1;
  }
}
void main()
{
  int A[10][10],B[10][10],m,n,C[10][3],D[10][3],Ct[10][3],Dt[10][3],S[10][3];

  printf("Enter the order of matrices: ");
  scanf("%d %d",&m,&n);

  printf("Enter the elements of a %d*%d matrix: ",m,n);
  readMat(A,m,n);

  printf("Enter the elemenrs of  a %d*%d matrix: ",m,n);
  readMat(B,m,n);

  toTuple(A,m,n,C);
  printf("Tuple form of A:\n");
  display(C);
  toTuple(B,m,n,D);
  printf("Tuple form of B:\n");
  display(D);

  toTranspose(C,Ct);
  printf("Transpose tuple form of A:\n");
  display(Ct);
  toTranspose(D,Dt);
  printf("Transpose tuple form of B:\n");
  display(Dt);

  addTuple(C,D,S);
  printf("Sum of A nd B:\n");
  display(S);

}