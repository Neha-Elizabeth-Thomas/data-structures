#include<stdio.h>
#include<stdlib.h>

struct term{
    float coeff;
    int exp;
    struct term* link;
};

struct term* newTerm(float coeff,int exp){
    struct term* new=(struct term*)malloc(sizeof(struct term));
    new->coeff=coeff;
    new->exp=exp;
    new->link=NULL;
    return new;
}

struct term* addPoly(struct term* Phead,struct term* Qhead){
    struct term* Rhead=newTerm(0,0);
    struct term* Pptr=Phead->link,*Qptr=Qhead->link,*Rptr=Rhead;
    
    while(Pptr!=NULL && Qptr!=NULL){
        if(Pptr->exp>Qptr->exp){
            struct term* new=newTerm(Pptr->coeff,Pptr->exp);
            Rptr->link=new;
            Pptr=Pptr->link; Rptr=Rptr->link;
        }else if(Qptr->exp>Pptr->exp){
                struct term* new=newTerm(Qptr->coeff,Qptr->exp);
                Rptr->link=new;
                Qptr=Qptr->link; Rptr=new;
            }else{
                struct term* new=newTerm(Pptr->coeff+Qptr->coeff,Pptr->exp);
                Rptr->link=new;
                Pptr=Pptr->link; Qptr=Qptr->link; Rptr=Rptr->link;
            }
    }

    while(Pptr!=NULL){
        struct term* new=newTerm(Pptr->coeff,Pptr->exp);
        Rptr->link=new;
        Pptr=Pptr->link; Rptr=Rptr->link;
    }

    while(Qptr!=NULL){
        struct term* new=newTerm(Qptr->coeff,Qptr->exp);
        Rptr->link=new;
        Qptr=Qptr->link; Rptr=Rptr->link;
    }
    return Rhead;
}

void insertOrdered(struct term* head,float coeff,int exp){
    struct term* new=newTerm(coeff,exp);
    struct term* ptr=head->link,*prev=head;

    //insert Before ptr and after prev
    while(ptr!=NULL && ptr->exp>exp){
        prev=ptr;
        ptr=ptr->link;
    }
    new->link=ptr;
    prev->link=new;
}

void removeDuplicates(struct term* head){
    struct term* prev=head->link,*ptr;
    if(prev)
        ptr=prev->link;
    while(ptr!=NULL){
        if(prev->exp==ptr->exp){
            prev->coeff+=ptr->coeff;
            prev->link=ptr->link;
            free(ptr);
            ptr=prev->link;
        }else{
            prev=ptr;
            ptr=ptr->link;
        }
    }
}

struct term* multPoly(struct term* Phead,struct term* Qhead){
    struct term* Rhead=newTerm(0,0);
    struct term* Pptr=Phead->link;
    while(Pptr!=NULL){
        struct term* Qptr=Qhead->link;
        while(Qptr!=NULL){
            insertOrdered(Rhead,Pptr->coeff*Qptr->coeff,Pptr->exp+Qptr->exp);
            Qptr=Qptr->link;
        }
        Pptr=Pptr->link;
    }
    removeDuplicates(Rhead);
    return Rhead;
}

void readPoly(struct term* head){
    int n,i;
    struct term* ptr=head;
    printf("How many terms?");
    scanf("%d",&n);
    printf("Enter terms in decreasing order of exponents: \n");
    for(i=0 ; i<n ; i++){
        struct term* new; int exp; float coeff;                
        printf("coeff%d exp%d: ",i+1,i+1);
        scanf("%f %d",&coeff,&exp);
        new=newTerm(coeff,exp);
        ptr->link=new;
        ptr=new;
    }
}

void display(struct term* head){
    struct term* ptr=head->link;

    while(ptr!=NULL){
        printf("%.2fx^%d + ",ptr->coeff,ptr->exp);
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
    struct term *Qhead,*Phead,*Rhead;
    
    Phead=newTerm(0,0);
    Qhead=newTerm(0,0);

    readPoly(Phead);
    readPoly(Qhead);

    display(Phead);
    display(Qhead);

    Rhead=addPoly(Phead,Qhead);
    display(Rhead);

    Rhead=multPoly(Phead,Qhead);
    display(Rhead);

    destroy(Phead);
    destroy(Qhead);
    destroy(Rhead);
}

