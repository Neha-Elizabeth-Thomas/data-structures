#include<stdio.h>
#include<stdlib.h>
#define INVALID -9999
 
struct node{
    int data;
    struct node* link;
}*head;

struct node* newNode(int data){
    struct node* new=(struct node*)malloc(sizeof(struct node));
    new->data=data;
    new->link=NULL;
    return new;
}

void insertBeg(int item){
    struct node* new=newNode(item);
    new->link=head->link;
    head->link=new;
}

void insertEnd(int item){
    struct node* new=newNode(item);
    struct node* ptr=head->link;
    while(ptr->link!=head)
        ptr=ptr->link;
    new->link=head;
    ptr->link=new;
}

void insertAfter(int item,int key){
    struct node* ptr=head->link;
    struct node* new=newNode(item);
    while(ptr!=head && ptr->data!=key)
        ptr=ptr->link;
    if(ptr==head)
        printf("%d not found\n",key);
    else{
        new->link=ptr->link;
        ptr->link=new;
    }
}

void insertBefore(int item,int key){
    struct node* new=newNode(item);
    struct node* ptr=head->link,*prev=head;

    while(ptr!=head && ptr->data!=key){
        prev=ptr;
        ptr=ptr->link;
    }
    if(ptr==head)
        printf("%d not found\n",key);
    else{
        new->link=ptr;
        prev->link=new;
    }
}

int deleteBeg(){
    struct node* ptr=head->link;
    if(ptr==head)
        printf("list empty\n");
    else{
        int item=ptr->data;
        head->link=ptr->link;
        free(ptr);
        return item;
    }
}

int deleteEnd(){
    int item;
    struct node* ptr=head->link,*prev=head;
    if(ptr==head){
        printf("list empty\n");
        return INVALID;
    }

    while(ptr->link!=head){
        prev=ptr;
        ptr=ptr->link;
    }
    item=ptr->data;
    prev->link=head;//imp
    free(ptr);
    return item;
}

int deleteAny(int key){
    struct node* ptr=head->link,*prev=head;
    if(ptr==head)
        printf("List empty\n");
    else{
        while(ptr!=head && ptr->data!=key){
            prev=ptr;
            ptr=ptr->link;
        }
        if(ptr==head)
            printf("%d not found\n",key);
        else{
            int item=ptr->data;
            prev->link=ptr->link;
            free(ptr);
            return item;
        }
    }
}

void reverse(struct node* head){
    struct node* prev=head,*ptr=head->link;

    while(ptr!=head){
        struct node* temp=ptr->link;
        ptr->link=prev;
        prev=ptr;
        ptr=temp;
    }
    ptr->link=prev;
}

void display(){
    struct node* ptr=head->link;
    printf("Circ Linked list: ");
    while(ptr!=head){
        printf("%5d ->",ptr->data);
        ptr=ptr->link;
    }
    printf("\b \b\b \b\n\n");
}

void destroy(struct node* head){
    struct node* ptr=head->link;
    while(ptr!=head){
        struct node* temp=ptr->link;
        free(ptr);
        ptr=temp;
    }
    free(head);
}

void main(){
    int choice,num,key;
    head=newNode(0);
    head->link=head;//most imp

    do{
        printf("Enter your choice:\n1)InsertBeg\n2)InsertEnd\n3)InsertAfter\n4)InsertBefore\n5)Reverse\n6)DeleteBeg\n7)DeleteEnd\n8)DeleteAny\n9)exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: printf("Enter the num to be inserted: ");
                    scanf("%d",&num);
                    insertBeg(num);
                    display();
                    break;
            case 2: printf("Enter the num to be inserted: ");
                    scanf("%d",&num);
                    insertEnd(num);
                    display();
                    break;
            case 3: printf("Enter the num to be inserted: ");
                    scanf("%d",&num);
                    printf("Enter the num after which it is to be inserted: ");
                    scanf("%d",&key);
                    insertAfter(num,key);
                    display();
                    break;
            case 4: printf("Enter the num to be inserted: ");
                    scanf("%d",&num);
                    printf("Enter the num before which it is to be inserted: ");
                    scanf("%d",&key);
                    insertBefore(num,key);
                    display();
                    break;
            case 5: reverse(head);
                    display();
                    break;
            case 6: printf("deleted num=%d\n",deleteBeg());
                    display();
                    break;
            case 7: printf("deleted num=%d\n",deleteEnd());
                    display();
                    break;
            case 8: printf("Enter the num to be deleted: ");
                    scanf("%d",&key);
                    printf("deleted num=%d\n",deleteAny(key));
                    display();
                    break;
            case 9: destroy(head);
                    return;
        }
    }while(1);
}