#include<stdio.h>
#define MAX 30
struct term
{
  float coeff;
  int exp;
};
struct poly
{
  struct term t[30];
  int n;  //no of terms
};

void initialize(struct poly*p)
{
  int i;
  p->n=0;
  for(i=0 ; i<MAX ; i++)
  {
    p->t[i].coeff=0;
    p->t[i].exp=0;
  }
}

void append(struct poly *p,float coeff,int exp)
{
  p->t[p->n].coeff=coeff;
  p->t[p->n].exp=exp;
  (p->n)++;
}

struct poly polyadd(struct poly p1,struct poly p2)
{
  struct poly p3;
  int i,j,k,exp;
  float coeff;
  initialize(&p3);
  
  i=j=0;
  while(i<p1.n && j<p2.n)
  {
    if(p1.t[i].exp>p2.t[j].exp)
    {
      coeff=p1.t[i].coeff;
      exp=p1.t[i].exp;
      append(&p3,coeff,exp);
      i++;
    }
    else if(p1.t[i].exp<p2.t[j].exp)
          {
            coeff=p2.t[j].coeff;
            exp=p2.t[j].exp;
            append(&p3,coeff,exp);
            j++;
          }
          else
          {
            coeff=p1.t[i].coeff+p2.t[j].coeff;
            exp=p1.t[i].exp;
            append(&p3,coeff,exp);
            i++; j++;
          }
  }
  while(i<p1.n)
  {
    coeff=p1.t[i].coeff;
    exp=p1.t[i].exp;
    append(&p3,coeff,exp);
    i++;
  }
  while(j<p2.n)
  {
    coeff=p2.t[j].coeff;
    exp=p2.t[j].exp;
    append(&p3,coeff,exp);
    j++;
  }
  return p3;
}

struct poly polymult(struct poly p1,struct poly p2)
{
  struct poly p,temp;
  int i,j,exp;
  float coeff;

  initialize(&p);
  for(i=0 ; i<p1.n ; i++)
  {
    initialize(&temp);

    for(j=0 ; j<p2.n ; j++)
    {
      coeff=p1.t[i].coeff*p2.t[j].coeff;
      exp=p1.t[i].exp+p2.t[j].exp;
      append(&temp,coeff,exp);
    }
    p=polyadd(p,temp);
  }
  return p;
}

void display(struct poly p)
{
  int i;
  for(i=0 ; i<p.n-1 ; i++)
  {
      printf("%.2fx^%d + ",p.t[i].coeff,p.t[i].exp);
  }
  if(p.t[i].exp!=0)
    printf("%.2fx^%d\n",p.t[i].coeff,p.t[i].exp);
  else
    printf("%.2f\n",p.t[i].coeff);
    printf("\n");
}


void main()
{
  struct poly p1,p2,p3;
  int i,exp,n;
  float coeff;

  initialize(&p1);
  initialize(&p2);

  /*append(&p1,2.5,6);
  append(&p1,5,5);
  append(&p1,9,3);
  append(&p1,14.3,0);
  append(&p2,65,3);
  append(&p2,25,2);
  append(&p2,6,1);*/
  printf("how many terms in 1st polynomial:");
  scanf("%d",&n);
  printf("Enter the coefficients and exponenets of %d terms in descending order of polynomials: ",n);
  for(i=0; i<n; i++)
  {
    scanf("%f %d",&coeff,&exp);
    append(&p1,coeff,exp);
  }
  printf("how many terms in 2nd polynomial:");
  scanf("%d",&n);
  printf("Enter the coefficients and exponenets of %d terms in descending order of polynomials: ",n);
  for(i=0; i<n; i++)
  {
    scanf("%f %d",&coeff,&exp);
    append(&p2,coeff,exp);
  }

  printf("First polynomial: ");
  display(p1);
  printf("Second polynomial: ");
  display(p2);
  p3=polyadd(p1,p2);
  printf("sum polynomial: ");
  display(p3);
  initialize(&p3);
  p3=polymult(p1,p2);
  printf("Product polynomial: ");
  display(p3);
}