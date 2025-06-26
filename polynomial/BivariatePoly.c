#include<stdio.h>
#include<stdlib.h>

struct term{
    float coeff;
    int xexp;
    int yexp;
    struct term* link;
};

struct term* newTerm(float coeff,int xexp,int yexp){
    struct term* new=(struct term*)malloc(sizeof(struct term));
    new->coeff=coeff;
    new->xexp=xexp;
    new->yexp=yexp;
    new->link=NULL;
    return new;
}

struct term* addPoly(struct term* Phead,struct term* Qhead){
    struct term* Rhead=newTerm(0,0,0);
    struct term* Pptr=Phead->link,*Qptr=Qhead->link,*Rptr=Rhead;

    while(Pptr!=NULL && Qptr!=NULL){
        if(Pptr->xexp>Qptr->xexp || (Pptr->xexp==Qptr->xexp && Pptr->yexp>Qptr->yexp)){
            struct term* new=newTerm(Pptr->coeff,Pptr->xexp,Pptr->yexp);
            Rptr->link=new;
            Rptr=Rptr->link;
            Pptr=Pptr->link;
        }else if(Qptr->xexp>Pptr->xexp || (Pptr->xexp==Qptr->xexp && Pptr->yexp<Qptr->yexp)){
                    struct term* new=newTerm(Qptr->coeff,Qptr->xexp,Qptr->yexp);
                    Rptr->link=new;
                    Rptr=Rptr->link;
                    Qptr=Qptr->link;
                }else{
                    struct term* new=newTerm(Pptr->coeff+Qptr->coeff,Pptr->xexp,Qptr->yexp);
                    Rptr->link=new;
                    Rptr=Rptr->link;
                    Qptr=Qptr->link;
                    Pptr=Pptr->link;
                }
    }

    while(Pptr!=NULL){
        struct term* new=newTerm(Pptr->coeff,Pptr->xexp,Pptr->yexp);
        Rptr->link=new;
        Rptr=Rptr->link;
        Pptr=Pptr->link;
    }

    while(Qptr!=NULL){
        struct term* new=newTerm(Qptr->coeff,Qptr->xexp,Qptr->yexp);
        Rptr->link=new;
        Rptr=Rptr->link;
        Qptr=Qptr->link;
    }
    return Rhead;
}

void readPoly(struct term* head){
    int n,i,xexp,yexp;
    float coeff;
    struct term* ptr=head,*new;
    printf("How many terms: ");
    scanf("%d",&n);

    for(i=0 ; i<n ; i++){
        printf("Enter coeff %d ,xexp %d,yexp %d: ",i+1,i+1,i+1);
        scanf("%f %d %d",&coeff,&xexp,&yexp);
        new=newTerm(coeff,xexp,yexp);
        ptr->link=new;
        ptr=ptr->link;
    }
}

void display(struct term* head){
    struct term* ptr=head->link;

    while(ptr!=NULL){
        printf("%.2fx^%dy^%d + ",ptr->coeff,ptr->xexp,ptr->yexp);
        ptr=ptr->link;
    }
    printf("\b \b\b \b\n\n");
}

void destroy(struct term* head){
    struct term* ptr=head;
    while(ptr!=NULL){
        struct term* temp=ptr->link;
        free(ptr);
        ptr=temp;
    }
}

void main(){
    struct term* Phead,*Qhead,*Rhead;

    Phead=newTerm(0,0,0);
    Qhead=newTerm(0,0,0);

    readPoly(Phead);
    readPoly(Qhead);

    display(Phead);
    display(Qhead);

    Rhead=addPoly(Phead,Qhead);
    display(Rhead);
}