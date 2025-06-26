#include<stdio.h>
#include<stdlib.h>
#define SIZE 5
#define INVALID -9999

struct term{
    float coeff;
    int exp;
};

void readPoly(struct term P[],int n){
    int i;
    printf("Enter decreasing order of exp: \n");
    for(i=0 ; i<n ; i++){
        printf("Enter coeff%d and exp%d: ",i+1,i+1);
        scanf("%f %d",&P[i].coeff,&P[i].exp);
    }
}

void display(struct term P[],int m){
    int i;
    
    for(i=0 ; i<m ; i++){
        printf("%.2fx^%d + ",P[i].coeff,P[i].exp);
    }
    printf("\b \b\b \b\n\n");
}

int polyAdd(struct term P[],int m,struct term Q[],int n,struct term R[]){
    int i=0,j=0,k=0;
    
    while(i<m && j<n){
        if(P[i].exp>Q[j].exp)
            R[k++]=P[i++];
        else if(Q[j].exp>P[i].exp)
                R[k++]=Q[j++];
                else{
                    R[k].coeff=P[i].coeff+Q[j].coeff;
                    R[k].exp=P[i].exp;
                    k++; i++; j++;
                }                    
    }
    while(i<m){
        R[k++]=P[i++];
    }

    while(j<n){
        R[k++]=Q[j++];
    }
    return k;
}

int polyMult(struct term P[],int m,struct term Q[],int n,struct term R[]){
    int i,j,k,p;
    struct term temp1[10];
    int q=0;
    for(i=0 ; i<m ; i++){
        struct term temp2[10];
        k=0;
        for(j=0 ; j<n ; j++){
            temp2[k].coeff=P[i].coeff*Q[j].coeff;
            temp2[k].exp=P[i].exp+Q[j].exp;
            k++; 
        }
        q=polyAdd(temp1,q,temp2,k,R);
        for(p=0 ; p<q ; p++)
            temp1[p]=R[p];
    }
    return q;
}

void main(){
    struct term P[10],Q[10],R[20];
    int m,n,k;

    printf("How many terms in P?");
    scanf("%d",&m);
    readPoly(P,m);

    printf("How many terms in Q?");
    scanf("%d",&n);
    readPoly(Q,n);

    display(P,m);
    display(Q,n);
   // printf("neha\b \b");

    k=polyAdd(P,m,Q,n,R);
    display(R,k);

    k=polyMult(P,m,Q,n,R);
    display(R,k);
}

