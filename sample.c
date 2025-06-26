#include<stdio.h>
#include<stdlib.h>
#define INVALID -9999

struct node{
    int data;
    struct node* llink,*rlink;
}*head;

struct node* newNode(int data){
    struct node* new=(struct node*)malloc(sizeof(struct node));
    new->data=data;
    new->llink=new->rlink=NULL; 
    return new;
}

void insertBeg(int data){
    struct node* new=newNode(data);
    new->llink=head;
    new->rlink=head->rlink;
    head->rlink=new;
    if(new->rlink!=NULL)
        new->rlink->llink=new;
}

void insertEnd(int data){
    struct node* ptr=head;
    struct node* new=newNode(data);
    while(ptr->rlink!=NULL)
        ptr=ptr->rlink;
    new->llink=ptr;
    ptr->rlink=new;
}

void insertBefore(int data,int key){
    struct node* new=newNode(data);
    struct node* ptr=head->rlink;
    while(ptr!=NULL && ptr->data!=key)
        ptr=ptr->rlink;
    if(ptr==NULL){
        printf("%d not found\n",key);
        return;
    }
    new->rlink=ptr;
    new->llink=ptr->llink;
    ptr->llink=new;
    new->llink->rlink=new;
}

void insertAfter(int data,int key){
    struct node* new=newNode(data);
    struct node* ptr=head->rlink;
    while(ptr!=NULL && ptr->data!=key)
        ptr=ptr->rlink;
    if(ptr==NULL){
        printf("%d not found\n",key);
        return;
    }

    new->rlink=ptr->rlink;
    new->llink=ptr;
    ptr->rlink=new;
    if(new->rlink!=NULL)
        new->rlink->llink=new;
}

int deleteBeg(){
    struct node* ptr=head->rlink;
    if(ptr==NULL)
        return INVALID;
    else{
        int item=ptr->data;
        head->rlink=ptr->rlink;
        if(ptr->rlink!=NULL)
            ptr->rlink->llink=head;
        free(ptr);
        return item;
    }
}

int deleteEnd(){
    struct node* ptr=head->rlink;
    int item;
    if(ptr==NULL){
        printf("list empty\n");
        return INVALID;
    }
    while(ptr->rlink!=NULL)
        ptr=ptr->rlink;
    item=ptr->data;
    ptr->llink->rlink=NULL;
    free(ptr);
    return item;
}

int deleteAny(int key){
    struct node* ptr=head->rlink;
    if(ptr==NULL)
        return INVALID;
    else{
        while(ptr!=NULL && ptr->data!=key)
            ptr=ptr->rlink;
        if(ptr==NULL){
            printf("%d not found\n",key);
            return INVALID;
        }else{
            int item=ptr->data;
            ptr->llink->rlink=ptr->rlink;
            if(ptr->rlink!=NULL)
                ptr->rlink->llink=ptr->llink;
            free(ptr);
            return item;
        }
    }
}

void reverse(){
    struct node* ptr=head->rlink;
    ptr->llink=NULL;
    while(ptr->rlink!=NULL)
    {
        struct node* temp=ptr->rlink;   
        ptr->rlink=ptr->llink;
        ptr->llink=temp;
        ptr=temp;
    }
    ptr->rlink=ptr->llink;
    ptr->llink=head;
    head->rlink=ptr;
}

void display(){
    struct node* ptr=head->rlink;
    printf("start: ");
    while(ptr!=NULL){
        printf("%5d -> ",ptr->data);
        ptr=ptr->rlink;
    }
    printf(":end\n\n");
}

void returnNode(){
    struct node* ptr=head;
    while(ptr!=NULL){
        struct node* temp=ptr->rlink;
        free(ptr);
        ptr=temp;
    }
}

void main()
{
  int choice,choice1,num,key;
  
  head=newNode(0);

  do
  {
    printf("Enter your choice:\n1)Insert\n2)Delete\n3)Display\n4)exit\n5)Reverse\n");
    scanf("%d",&choice);

    switch(choice)
    {
      case 1:printf("select:\n1)Insert beginning\n2)Insert End\n3)Insert at any position(after)\n4)Insert at any position(before)\n");
              scanf("%d",&choice1);
              switch(choice1)
              {
                case 1:printf("Enter the number to be inserted: ");
                        scanf("%d",&num);
                        insertBeg(num);
                        display();
                        break;
                case 2:printf("Enter the number to be inserted: ");
                        scanf("%d",&num);
                        insertEnd(num);
                        display();
                        break;
                case 3:printf("Enter the number to be inserted: ");
                        scanf("%d",&num);
                        printf("Enter the number after which %d is to be inserted: ",num);
                        scanf("%d",&key);
                        insertAfter(num,key);
                        display();
                        break;
                case 4:printf("Enter the number to be inserted: ");
                        scanf("%d",&num);
                        printf("Enter the number before which %d is to be inserted: ",num);
                        scanf("%d",&key);
                        insertBefore(num,key);
                        display();
                        break;
                default:printf("Invalid\n");
              }
              break;
      case 2:printf("select:\n1)Delete from beginning\n2)Delete from end\n3)deletefrom any arbitrary position\n");
              scanf("%d",&choice1);
              switch(choice1)
              {
                case 1:deleteBeg();
                        display();
                        break;
                case 2:deleteEnd();
                        display();
                        break;
                case 3:printf("Enter the number to be deleted: ");
                      scanf("%d",&key);
                       deleteAny(key);
                        display();
                       break;
                default:printf("Invalid\n");
              }
              break;
      case 3:display();
              break;
      case 4:returnNode();
              return;
      case 5:reverse();
              display();
              break;
      default:returnNode();
              return;
    }
  }
  while(1);
}