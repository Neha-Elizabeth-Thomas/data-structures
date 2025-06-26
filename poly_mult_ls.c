#include<stdio.h>
#include<stdlib.h>

struct term
{
  float coeff ;
  int exp;
  struct term *link;
};

void InsertEnd(struct term* head,float c,int e)
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

/*void InsertEnd(struct term* head,float c,int e)
{
  struct term* ptr=head;
  while(ptr->link!=NULL)
    ptr=ptr->link;
  struct term* new=(struct term*)malloc(sizeof(struct term));
  new->coeff=c;
  new->exp=e;
  new->link=NULL;
  ptr->link=new;
}*/

struct term* polyAdd(struct term* Phead,struct term* Qhead)
{
  struct term* Shead=(struct term*)malloc(sizeof(struct term));
  struct term *Pptr,*Qptr;
  Shead->link=NULL;
  Pptr=Phead->link;
  Qptr=Qhead->link;

  while(Pptr!=NULL && Qptr!=NULL)
  {
    if(Pptr->exp==Qptr->exp)
    {
      int e; float c;
      c=Pptr->coeff+Qptr->coeff;
      e=Pptr->exp;
      InsertEnd(Shead,c,e);
      Pptr=Pptr->link;
      Qptr=Qptr->link;
    }
    else if(Pptr->exp>Qptr->exp)
          {
            InsertEnd(Shead,Pptr->coeff,Pptr->exp);
            Pptr=Pptr->link;
          }
          else
          {
            InsertEnd(Shead,Qptr->coeff,Qptr->exp);
            Qptr=Qptr->link;
          }
  }
  while(Pptr!=NULL)
  {
    InsertEnd(Shead,Pptr->coeff,Pptr->exp);
    Pptr=Pptr->link;
  }
  while(Qptr!=NULL)
  {
    InsertEnd(Shead,Qptr->coeff,Qptr->exp);
    Qptr=Qptr->link;
  }

  return Shead;
}

void displayPoly(struct term* head)
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
    {
      if(ptr->exp==0)
        printf("%.2fx\n\n",ptr->coeff);
      else
        printf("%.2fx^%d\n\n",ptr->coeff,ptr->exp);
    }
    else
      printf("%.2fx^%d + ",ptr->coeff,ptr->exp);

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

/*void initialize(struct term* head)
{
  struct term* ptr=head->link;
  head->link=NULL;

  while(ptr!=NULL)
  {
    struct term* temp=ptr->link;
    free(ptr);
    ptr=temp;
  }
}*/
void poyMult(struct term* Phead,struct term* Qhead,struct term* Rhead)
{
  struct term *Pptr,*Qptr,*tHead,*temp;
  int e; float c;
  tHead=(struct term*)malloc(sizeof(struct term));
  tHead->link=NULL;

  Pptr=Phead->link;
  //Qptr=Qhead->link;

  while(Pptr!=NULL)
  {
    returnNode(tHead->link);
    tHead->link=NULL;
    Qptr=Qhead->link;

    while(Qptr!=NULL)
    {
      c=Pptr->coeff*Qptr->coeff;
      e=Pptr->exp+Qptr->exp;
      InsertEnd(tHead,c,e);
      Qptr=Qptr->link;
    }
    temp=Rhead;
    Rhead=polyAdd(Rhead,tHead);
    returnNode(temp);
    Pptr=Pptr->link;
  }
  returnNode(tHead);
}


void main()
{
  int m,n,coeff,exp,i;
  struct term *Phead,*Qhead,*Rhead;

  Phead=(struct term*)malloc(sizeof(struct term));
  Qhead=(struct term*)malloc(sizeof(struct term));
  //Shead=(struct term*)malloc(sizeof(struct term));
  Rhead=(struct term*)malloc(sizeof(struct term));
  Phead->link=Qhead->link=Rhead->link=NULL;

  printf("How many terms in 1st polynomial?");
  scanf(" %d",&m);
  printf("Enter the coefficients and exponents of %d terms of 1st polynomial in the decreasing orer of exponents:\n",m);
  for(i=0 ; i<m ; i++)
  {
    scanf("%f %d",&coeff,&exp);
    InsertEnd(Phead,coeff,exp);
  }

  printf("How many terms in 1st polynomial?");
  scanf("%d",&n);
  printf("Enter the coefficients and exponents of %d terms of 1st polynomial in the decreasing orer of exponents:\n",n);
  for(i=0 ; i<n ; i++)
  {
    scanf("%f %d",&coeff,&exp);
    InsertEnd(Qhead,coeff,exp);
  }

  poyMult(Phead,Qhead,Rhead);

  printf("1st polynomial: \n");
  displayPoly(Phead);
  printf("2nd polynomial: \n");
  displayPoly(Qhead);
  printf("PRODUCT of two polynomials:\n");
  displayPoly(Rhead);

  returnNode(Phead);
  returnNode(Qhead);
  returnNode(Rhead);
}