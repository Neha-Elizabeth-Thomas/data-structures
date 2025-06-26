#include<stdio.h>
#include<stdlib.h>

struct term{
  float coeff;
  int exp;
  struct term* link;
};

struct term* newTerm(float coeff,int exp)
{
  struct term* new=(struct term*)malloc(sizeof(struct term));
  new->coeff=coeff;
  new->exp=exp;
  new->link=NULL;
  return new;
}

void InsertEnd(struct term* head,float coeff,int exp)
{
  struct term* ptr=head;

  struct term* new=newTerm(coeff,exp);

  while(ptr->link!=NULL)
    ptr=ptr->link;

  ptr->link=new;
}

void readPoly(struct term* head)
{
  int n,i,e;
  float c;
  printf("how many terms: ");
  scanf("%d",&n);
  printf("enter %d terms in decreasing order of exp: \n",n);
  for(i=0 ; i<n ; i++)
  {
    printf("Enter coeff%d and exp%d: ",(i+1),(i+1));
    scanf("%f %d",&c,&e);
    InsertEnd(head,c,e);
  }
}

struct term* polyAdd(struct term* Phead,struct term *Qhead)
{
  struct term* Rhead;
  struct term* Qptr,*Pptr,*Rptr;
  Rhead=newTerm(0,0);//you cannot call a fn within declaration you
  Rptr=Rhead;
  Qptr=Qhead->link;//fool
  Pptr=Phead->link;
  
  while(Pptr!=NULL && Qptr!=NULL)
  {
   
    if(Pptr->exp>Qptr->exp)
    {
      //InsertEnd(Rhead,Pptr->coeff,Pptr->exp);
      struct term* new=newTerm(Pptr->coeff,Pptr->exp);
      Rptr->link=new;
      Rptr=new;
      Pptr=Pptr->link;
    }
    else if(Qptr->exp>Pptr->exp)
          {
            //InsertEnd(Rhead,Qptr->coeff,Qptr->exp);
            struct term* new=newTerm(Qptr->coeff,Qptr->exp);
            Rptr->link=new;
            Rptr=new;
            Qptr=Qptr->link;
          }
          else
          {
            //InsertEnd(Rhead,(Pptr->coeff+Qptr->coeff),Pptr->exp);
            struct term* new=newTerm(Pptr->coeff+Qptr->coeff,Pptr->exp);
            Rptr->link=new;
            Rptr=new;
            Pptr=Pptr->link;
            Qptr=Qptr->link;
          }
  }
  
  while(Pptr!=NULL)
  {
    //InsertEnd(Rhead,Pptr->coeff,Pptr->exp);
    struct term* new=newTerm(Pptr->coeff,Pptr->exp);
    Rptr->link=new;
    Rptr=new;
    Pptr=Pptr->link;
  }
  while(Qptr!=NULL)
  {
   // InsertEnd(Rhead,Qptr->coeff,Qptr->exp);
    struct term* new=newTerm(Pptr->coeff,Pptr->exp);
   Rptr->link=new;
    Rptr=new;
    Qptr=Qptr->link;
  }

  return Rhead;
}

void display(struct term* head)
{
  struct term* ptr=head->link;
  if(ptr==NULL) return ;
  while(ptr->link!=NULL)
  {
    printf("%.2fx^%d + ",ptr->coeff,ptr->exp);
    ptr=ptr->link;
  }
  if(ptr->exp==0)
    printf("%.2f\n\n",ptr->coeff);
  else
    printf("%.2fx^%d\n\n",ptr->coeff,ptr->exp);
}

void main()
{
  struct term* Rhead,*Phead,*Qhead;
  Phead=newTerm(0,0);
  Qhead=newTerm(0,0);

  printf("Enter the elements of 1st polynomial: \n");
  readPoly(Phead);
  
  printf("Enter the elements of 2nd polynomial: \n");
  readPoly(Qhead);
 
  Rhead=polyAdd(Phead,Qhead);

  printf("1st polynomial:\n");
  display(Phead);
  printf("2nd polynomial:\n");
  display(Qhead);
  printf("sum polynomial:\n");
  display(Rhead);
}