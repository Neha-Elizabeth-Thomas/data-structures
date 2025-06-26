#include<stdio.h>
#include<stdlib.h>
#define INVALID -9999

struct node{
    int data;
    struct node* llink,*rlink;
}*Qhead,*rear=NULL,*front=NULL;

struct node* newNode(int data){
    struct node* new=(struct node*)malloc(sizeof(struct node));
    new->data=data;
    new->llink=new->rlink=NULL;
    return new;
}

void insertRear(int item){
    struct node* new=newNode(item);
    if(front==NULL){
        new->llink=Qhead;
        Qhead->rlink=new;
        front=rear=new;
    }else{
        new->llink=rear;
        rear->rlink=new;
        rear=new;
    }
}

int deleteFront(){
    if(front==NULL){
        printf("dequeue empty\n");
        return INVALID;
    }else{
        int item=front->data;
        Qhead->rlink=front->rlink;
        if(front->rlink!=NULL)
            front->rlink->llink=Qhead;
        free(front);
        front=Qhead->rlink;
        if(front==NULL)
            rear=NULL;
        return item;
    }
}

void insertFront(int item){
    struct node* new=newNode(item);
    if(front==NULL){
        new->llink=Qhead;
        Qhead->rlink=new;
        front=rear=new;
    }else{
        new->rlink=front;
        new->llink=Qhead;
        Qhead->rlink=new;
        front->llink=new;
        front=new;
    }
}

int deleteRear(){
    if(front==NULL){
        printf("dequeue empty\n");
        return INVALID;
    }else{
        int item=rear->data;
        struct node* temp=rear->llink;
        temp->rlink=NULL;
        free(rear);
        rear=temp;
        if(rear==Qhead)//imp
            rear=front=NULL;
        return item;
    }
}

void display(){
    struct node* ptr=Qhead->rlink;
    if(ptr==NULL){
        printf("queue empty\n");
        return;
    }
    printf("Front\n");
    printf("----------------\n");
    while(ptr){
        printf("%d\n",ptr->data);
        ptr=ptr->rlink;
    }
    printf("----------------\n");
    printf("Rear\n\n");

}

void destroy(){
    struct node* ptr=Qhead;
    while(ptr){
        struct node* temp=ptr->rlink;
        free(ptr);
        ptr=temp;
    }
}

void main(){
    int choice,num;
    Qhead=newNode(0);
    do{
        printf("Enter your choice:\n1)insertRear\n2)deleteFront\n3)insertFront\n4)deleteRear\n5)display\n6)exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: printf("Enter the num to be insrted: ");
                    scanf("%d",&num);
                    insertRear(num);
                    display();
                    break;
            case 2: printf("deleted=%d\n",deleteFront());
                    display();
                    break;
            case 3: printf("Enter the num to be insrted: ");
                    scanf("%d",&num);
                    insertFront(num);
                    display();
                    break;
            case 4: printf("deleted=%d\n",deleteRear());
                    display();
                    break;
            case 5: display();
                    break;
            case 6: destroy();
                    return;
        }
    }while(1);
}