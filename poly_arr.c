#include<stdio.h>

struct term
{
  float coeff;
  int exp;
};
void display(struct term[],int);

void readPoly(struct term P[],int m)
{
  int i;
  printf("Enter %d terms: \n",m);
  for(i=0 ; i<m ; i++)
  {
    printf("Enter coeff%d and exp%d: ",i+1,i+1);
    scanf("%f %d",&P[i].coeff,&P[i].exp);
  }
}

int polyAdd(struct term P[],int m,struct term Q[],int n,struct term R[])
{
  int i,j,k;
  i=j=k=0;
  while(i<m && j<n)
  {
    if(P[i].exp>Q[j].exp)
    {
      R[k]=P[i];
      k++;
      i++;
    }
    else if(P[i].exp<Q[j].exp)
          {
            R[k]=Q[j];
            k++; j++;
          }
          else
          {
            R[k].coeff=P[i].coeff+Q[j].coeff;
            R[k].exp=P[i].exp;
            k++; i++; j++;
          }
  }
  while(i<m)
  {
    R[k]=P[i];
    k++; i++;
  }
  while(j<n)
  {
    R[k]=Q[j];
    k++; j++;
  }
  return k;
}

int polyMult(struct term P[],int m,struct term Q[],int n,struct term R[])
{
  struct term temp1[10],temp2[20];
  int i,j,k,count=0,p,q,c;
  for(i=0 ; i<m ; i++)
  {
    k=0;
    for(j=0 ; j<n ; j++)
    {
      temp1[k].coeff=P[i].coeff*Q[j].coeff;
      temp1[k].exp=P[i].exp+Q[j].exp;
      k++;
    }
   // display(temp1,k);
    c=count;
    count=polyAdd(temp1,k,R,c,temp2);
    for(p=0 ; p<count ; p++)
      R[p]=temp2[p];
  }
  return count;
}

void display(struct term P[],int m)
{
  int i;
  for(i=0 ; i<m-1 ; i++)
  {
    printf("%.2fx^%d + ",P[i].coeff,P[i].exp);
  }
  printf("%.2fx^%d\n\n",P[i].coeff,P[i].exp);
}

void main()
{
  struct term P[10],Q[10],S[10],R[20];
  int m,n,i;

  printf("How many terms in poly1: ");
  scanf("%d",&m);
  readPoly(P,m);

  printf("How many terms in poly1: ");
  scanf("%d",&n);
  readPoly(Q,n);

  printf("poly1:\n");
  display(P,m);
  printf("poly2:\n");
  display(Q,n);

  i=polyAdd(P,m,Q,n,S);
  printf("The resultant polynomial is:\n");
  display(S,i);

  i=polyMult(P,m,Q,n,R);
  printf("product of A and B is:\n");
  display(R,i);
}