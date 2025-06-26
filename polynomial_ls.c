#include<stdio.h>
#include<stdlib.h>

struct term
{
  float coeff;
  int exp;
  struct term* link;
};

void insertEnd(struct term* head,float c,int e)
{
  struct term *ptr=head,*new;
  while(ptr->link!=NULL)
    ptr=ptr->link;
  new=(struct term*)malloc(sizeof(struct term));
  new->coeff=c;
  new->exp=e;
  new->link=NULL;
  ptr->link=new;
}

void addPoly(struct term* Phead,struct term* Qhead,struct term* Rhead)
{
  struct term* Pptr,*Qptr;
  float c;
  int e;
  Pptr=Phead->link;
  Qptr=Qhead->link;

  while(Pptr!=NULL && Qptr!=NULL)
  {
    if((Pptr->exp)==(Qptr->exp))
    {
      c=Pptr->coeff+Qptr->coeff;
      e=Pptr->exp;
      insertEnd(Rhead,c,e);
      Pptr=Pptr->link;
      Qptr=Qptr->link;
    }
    else if((Pptr->exp)>(Qptr->exp))
          {
            c=Pptr->coeff;
            e=Pptr->exp;
            insertEnd(Rhead,c,e);
            Pptr=Pptr->link;
          }
          else
          {
            c=Qptr->coeff;
            e=Qptr->exp;
            insertEnd(Rhead,c,e);
            Qptr=Qptr->link;
          }
  }
  while(Pptr!=NULL)
  {
    c=Pptr->coeff;
    e=Pptr->exp;
    insertEnd(Rhead,c,e);
    Pptr=Pptr->link;
  }
  while(Qptr!=NULL)
  {
    c=Qptr->coeff;
    e=Qptr->exp;
    insertEnd(Rhead,c,e);
    Qptr=Qptr->link;
  }
}

void display(struct term* head)
{
  struct term* ptr=head->link;
  if(ptr==NULL)
  {
    printf("No elements in the polynomial\n");
    return;
  }
  while(ptr!=NULL)
  {
    if(ptr->link==NULL)
      printf("%.2fx%d\n\n",ptr->coeff,ptr->exp);
    else
      printf("%.2fx%d + ",ptr->coeff,ptr->exp);

    ptr=ptr->link;
  }
}

void returnNode(struct term* head)
{
  struct term* ptr,*temp;
  ptr=head;
  while(ptr!=NULL)
  {
    temp=ptr->link;
    free(ptr);
    ptr=temp;
  }
}
void main()
{
  struct term *Phead,*Qhead,*Rhead;
  int m,n,i,e;
  float c;
  Phead=(struct term*)malloc(sizeof(struct term));
  Phead->link=NULL;
  Qhead=(struct term*)malloc(sizeof(struct term));
  Qhead->link=NULL;

  Rhead=(struct term*)malloc(sizeof(struct term));
  Rhead->link=NULL;

  printf("How many terms in polynomial1: ");
  scanf("%d",&m);
  printf("Enter the coefficients and exponents of %d terms of polynomial1 in descending orderof exponents: ",m);
  for(i=0 ; i<m ; i++)
  {
    scanf("%f %d",&c,&e);
    insertEnd(Phead,c,e);
  }

  printf("How many terms in polynomial2: ");
  scanf("%d",&n);
  printf("Enter the coefficients and exponents of %d terms of polynomial2 in descending orderof exponents: ",n);
  for(i=0 ; i<n ; i++)
  {
    scanf("%f %d",&c,&e);
    insertEnd(Qhead,c,e);
  }

  addPoly(Phead,Qhead,Rhead);

  printf("1st polynomial\n");
  display(Phead);
  printf("2nd polynomial:\n");
  display(Qhead);
  printf("Resultant polynomial:\n");
  display(Rhead);

  returnNode(Phead);
  returnNode(Qhead);
  returnNode(Rhead);
}