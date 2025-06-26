#include<stdio.h>
#include<stdlib.h>

struct term
{
  float coeff;
  int xexp;
  int yexp;
  struct term* link;
};

void InsertEnd(struct term* head,float c,int e1,int e2)
{
  struct term *ptr=head,*new;

  while(ptr->link!=NULL)
      ptr=ptr->link;
  new=(struct term*)malloc(sizeof(struct term));
  new->coeff=c;
  new->xexp=e1;
  new->yexp=e2;
  new->link=NULL;
  ptr->link=new;
}

void addPoly(struct term* Phead,struct term* Qhead,struct term* Rhead)
{
  struct term *Pptr,*Qptr;
  Pptr=Phead->link;
  Qptr=Qhead->link;
  while(Pptr!=NULL && Qptr!=NULL)
  {
    if(Pptr->xexp==Qptr->xexp && Pptr->yexp==Qptr->yexp)
    {
      float c;
      c=Pptr->coeff+Qptr->coeff;
      InsertEnd(Rhead,c,Pptr->xexp,Pptr->yexp);
      Pptr=Pptr->link;
      Qptr=Qptr->link;
    }
    else if(Pptr->xexp>Qptr->xexp)
          {
            InsertEnd(Rhead,Pptr->coeff,Pptr->xexp,Pptr->yexp);
            Pptr=Pptr->link;
          }
          else if(Qptr->xexp>Pptr->xexp)
              {
                InsertEnd(Rhead,Qptr->coeff,Qptr->xexp,Qptr->yexp);
                Qptr=Qptr->link;
              }
              else if(Pptr->yexp>Qptr->yexp)
                   {
                     InsertEnd(Rhead,Pptr->coeff,Pptr->xexp,Pptr->yexp);
                     Pptr=Pptr->link;
                   }
                   else if(Qptr->yexp>Pptr->yexp)
                        {
                          InsertEnd(Rhead,Qptr->coeff,Qptr->xexp,Qptr->yexp);
                          Qptr=Qptr->link;
                        }

  }
  while(Pptr!=NULL)
  {
    InsertEnd(Rhead,Pptr->coeff,Pptr->xexp,Pptr->yexp);
    Pptr=Pptr->link;
  }
  while(Qptr!=NULL)
  {
    InsertEnd(Rhead,Qptr->coeff,Qptr->xexp,Qptr->yexp);
    Qptr=Qptr->link;
  }
}

void displayPoly(struct term* head)
{
  struct term* ptr=head->link;
  if(ptr==NULL)
    printf("No terms in polynomial\n");
  else
  {
    printf("%.2fx^%dy^%d ",ptr->coeff,ptr->xexp,ptr->yexp);
    ptr=ptr->link;
    while(ptr!=NULL)
    {
      if(ptr->coeff==0)
      {
        ptr=ptr->link;
        continue;
      }
      else if(ptr->coeff<0)
            {
              if(ptr->xexp==0)
                printf("%.2fy^%d ",ptr->coeff,ptr->yexp);
              else if(ptr->yexp==0)
                      printf("%.2fx^%d ",ptr->coeff,ptr->xexp);
                    else 
                      printf("%.2fx^%dy^%d ",ptr->coeff,ptr->xexp,ptr->yexp);
            }
            else
            {
              if(ptr->xexp==0)
                printf("+%.2fy^%d ",ptr->coeff,ptr->yexp);
              else if(ptr->yexp==0)
                      printf("+%.2fx^%d ",ptr->coeff,ptr->xexp);
                    else 
                      printf("+%.2fx^%dy^%d ",ptr->coeff,ptr->xexp,ptr->yexp);
            }
      ptr=ptr->link;
    }   
    printf("\n\n");
  }
}

void returnNode(struct term* head)
{
  struct term* ptr=head;

  while(ptr!=NULL)
  {
    struct term* temp=ptr->link;
    free(ptr);
    ptr=temp;
  }
}

void readPoly(struct term* head)
{
  int n,i,e1,e2;
  float c;
  printf("How many terms: ");
  scanf("%d",&n);
  for(i=0 ; i<n ; i++)
  {
    printf("Enter coeff%d,xexp%d,yexp%d: ",i+1,i+1,i+1);
    scanf("%f %d %d",&c,&e1,&e2);
    InsertEnd(head,c,e1,e2);
  }
}
void main()
{
  int m,n,e1,e2,i;
  float c;
  struct term *Phead,*Qhead,*Rhead;
  Phead=(struct term*)malloc(sizeof(struct term));
  Qhead=(struct term*)malloc(sizeof(struct term));
  Rhead=(struct term*)malloc(sizeof(struct term));
  Phead->link=NULL;
  Qhead->link=NULL;
  Rhead->link=NULL;

  printf("Enter 1st polynomial\n");
  readPoly(Phead);
  printf("Enter 2nd polynomial\n");
  readPoly(Qhead);
  /*printf("How many terms in 1st polynomial? ");
  scanf("%d",&m);
  printf("Enter the coefficients and exponents(x and y) of %d terms of 1st polynomial in decresing order of exponents: ",m);
  for(i=0 ; i<m ; i++)
  {
    scanf("%f %d %d",&c,&e1,&e2);
    InsertEnd(Phead,c,e1,e2);
  }

  printf("How many terms in 2nd polynomial? ");
  scanf("%d",&n);
  printf("Enter the coefficients and exponents(x and y) of %d terms of 2nd polynomial in decresing order of exponents: ",n);
  for(i=0 ; i<n ; i++)
  {
    scanf("%f %d %d",&c,&e1,&e2);
    InsertEnd(Qhead,c,e1,e2);
  }*/

  addPoly(Phead,Qhead,Rhead);

  printf("1st polynomial:\n");
  displayPoly(Phead);
  printf("2nd polynomial:\n");
  displayPoly(Qhead);
  printf("The SUM of the 2 polynomials is\n");
  displayPoly(Rhead);

  returnNode(Phead);
  returnNode(Qhead);
  returnNode(Rhead);
}