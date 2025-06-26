#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int isPrime(int num);

struct node{
    int data;
    struct node* link;;
}*head=NULL;

struct node* newNode(int num){
    struct node* new=(struct node*)malloc(sizeof(struct node));
    new->data=num;
    new->link=NULL;
    return new;
}

void insertEnd(int data){
    struct node* new=newNode(data);
    struct node* ptr=head;
    while(ptr->link!=NULL)
        ptr=ptr->link;

    new->link=NULL;
    ptr->link=new;
}

void display(){
    struct node* ptr=head->link;
    printf("\nLinked List:");
    printf("\n--------------\n");
    while(ptr!=NULL){
        printf("%d -> ",ptr->data);
        ptr=ptr->link;
    }
    printf("\n--------------\n\n");
}

void printPrime(){
    struct node* ptr=head->link;
    printf("\nPrime numbers in Linked List:");
    printf("\n----------------------------\n");
    while(ptr!=NULL){
        if(isPrime(ptr->data))
            printf("%6d\n",ptr->data);
        ptr=ptr->link;
    }
    printf("-------------------------\n\n");
}

int isPrime(int num){
    int i;
    if(num==0 || num==1)
        return 0;
    for(i=2 ; i<=sqrt(num) ; i++){
        if(num%i==0)
            return 0;
    }
    return 1;
}

void main(){
    int n,data,i;
    head=newNode(0);

    printf("How many numbers?");
    scanf("%d",&n);

    printf("Enter %d numbers: ",n);
    for(i=0 ; i<n ; i++){
        scanf("%d",&data);
        insertEnd(data);
    }

    display();
    printPrime();
}