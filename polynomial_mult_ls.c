#include<stdio.h>
#include<stdlib.h>

struct term
{
  float coeff;
  int exp;
  struct term* link;
};

void insert(struct term* head,float c,int e)
{
  struct term* ptr=head,*prev=head;
  struct term* new=(struct term*)malloc(sizeof(struct term));
  new->coeff=c;
  new->exp=e;
  new->link=NULL;

  /*if(ptr->link==NULL)
  {
    head->link=new;
  }
  else
  {*/
    prev=head;
    while(ptr!=NULL && ptr->exp>e){
      prev=ptr;
      ptr=ptr->link;
    }
    
    new->link=ptr;
    prev->link=new;

    /*while(ptr->link!=NULL && ptr->link->exp>=e) //the exponent of ptr is greater than equal to e.but exp of ptr->link is less than e.then exit loop.the position of term is between ptr and ptr->link
    {
      //prev=ptr;
      ptr=ptr->link;
    }

    new->link=ptr->link;
    ptr->link=new;
    //new->link=ptr;*/
}

void removeDuplicates(struct term* head)
{
  struct term* ptr=head->link;

  while(ptr->link!=NULL)
  {
    if(ptr->exp==ptr->link->exp)
    {
      struct term* temp;
      ptr->coeff=ptr->coeff+ptr->link->coeff;
      temp=ptr->link;
      ptr->link=ptr->link->link;//we are updating ptr->link,which needs to 
      free(temp);                //compared
    }
    else
    {
      ptr=ptr->link;
    }
  }
}
void multPoly(struct term* Phead,struct term* Qhead,struct term* Rhead)
{
  struct term *Pptr=Phead->link,*Qptr=Qhead->link;

  if(Pptr==NULL && Qptr==NULL)
  {
    printf("zero polynomial\n");
    return ;
  }
  while(Pptr!=NULL)
  {
    Qptr=Qhead->link;
    while(Qptr!=NULL)
    {
      int e=Pptr->exp+Qptr->exp;
      float c=Pptr->coeff*Qptr->coeff;     
      insert(Rhead,c,e);
      Qptr=Qptr->link;
    }
    Pptr=Pptr->link;
  }

  removeDuplicates(Rhead);
}
void readPoly(struct term* head)
{
  int n,e,i;
  float c;
  printf("How many terms in the polynomial? ");
  scanf("%d",&n);

  for(i=0 ; i<n ; i++)
  {
    printf("Enter the term(coeff%d and exp%d): ",i+1,i+1);
    scanf("%f %d",&c,&e);
    insert(head,c,e);
  }
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

  Phead=(struct term*)malloc(sizeof(struct term));
  Phead->link=NULL;
  Qhead=(struct term*)malloc(sizeof(struct term));
  Qhead->link=NULL;
  Rhead=(struct term*)malloc(sizeof(struct term));
  Rhead->link=NULL;

  printf("Enter the 1st polynomial: \n");
  readPoly(Phead);
  printf("Enter the 2nd polynomial: \n");
  readPoly(Qhead);

  multPoly(Phead,Qhead,Rhead);

  printf("First polynomial:\n");
  displayPoly(Phead);
  printf("second polynomial: \n");
  displayPoly(Qhead);
  printf("product polynomial:\n");
  displayPoly(Rhead);

  returnNode(Phead);
  returnNode(Qhead);
  returnNode(Rhead);
}