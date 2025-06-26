#include<stdio.h>
#include<stdlib.h>
#define SIZE 20

struct node{
    int data;
    struct node* lchild;
    struct node* rchild;
}*root=NULL;

struct node* newNode(){
    struct node* new=(struct node*)malloc(sizeof(struct node));
    //new->data=data;
    new->lchild=new->rchild=NULL;
    return new;
}

void bt(struct node* ptr,int data){
    char option;
    if(ptr==NULL)
        return;
    ptr->data=data;

    printf("do %d has lchild(y/n)?",data);
    scanf(" %c",&option);
    if(option=='y' || option=='Y'){
        int item;
        struct node *new=newNode();
        ptr->lchild=new;
        printf("Enter the lchild: ");
        scanf("%d",&item);
        bt(new,item);
    }

    printf("do %d has rchild(y/n)?",data);
    scanf(" %c",&option);
    if(option=='y' || option=='Y'){
        int item;
        struct node *new=newNode();
        ptr->rchild=new;
        printf("Enter the rchild: ");
        scanf("%d",&item);
        bt(new,item);
    }
}

struct node* Q[SIZE];
int f=-1,r=-1;

void enqueue(struct node* item){
    if(f==(r+1)%SIZE){
        printf("queeu full\n");
        return;
    }
    else if(f==-1)
            f=r=0;
         else if(r==SIZE-1)
                r=0;
                else
                    r++;
    Q[r]=item;
}

struct node* dequeue(){
    if(f==-1){
        printf("queue empty\n");
        return NULL;
    }else{
        struct node* item=Q[f];
        if(f==SIZE-1)
            f=0;
        else
            f++;
        if(f==(r+1)%SIZE)
            f=r=-1;
        return item;
    }
}

void insert(int item){
    struct node* new=newNode();
    new->data=item;
    if(root==NULL){
        root=new;
        return;
    }
    enqueue(root);
    while(f!=-1){
        struct node* temp=dequeue();
        if(temp->lchild==NULL){
            temp->lchild=new;
            return;
        }else
            enqueue(temp->lchild);

        if(temp->rchild==NULL){
            temp->rchild=new;
            return;
        }else
            enqueue(temp->rchild);
    }
}

void delete(int key){
    struct node* keynode=NULL,*temp,*prev;
    if(root==NULL)
        return;
    if(root->lchild==NULL && root->rchild==NULL && root->data==key)
        return;
    enqueue(root);
    while(f!=-1){
        temp=dequeue();
        if(temp->data==key){
            keynode=temp;
        }

        if(temp->lchild!=NULL){
            prev=temp;
            enqueue(temp->lchild);
        }
        if(temp->rchild!=NULL){
            prev=temp;
            enqueue(temp->rchild);
        }
    }
    if(keynode==NULL)
        printf("%d not found\n",key);
    else{
        keynode->data=temp->data;
        if(prev->lchild==temp)
            prev->lchild=NULL;
        else
            prev->rchild=NULL;
        free(temp);
    }
}

void inorder(struct node* ptr){
    if(ptr!=NULL){
        inorder(ptr->lchild);
        printf("%d\n",ptr->data);   
        inorder(ptr->rchild);
    }
}

void preorder(struct node* ptr){
    if(ptr!=NULL){
        printf("%d\n",ptr->data);
        preorder(ptr->lchild);
        preorder(ptr->rchild);
    }
}

void postorder(struct node* ptr){
    if(ptr!=NULL){
        postorder(ptr->lchild);
        postorder(ptr->rchild);
        printf("%d\n",ptr->data);
    }
}

int top=-1;
struct node* S[SIZE];

void push(struct node* item){
    if(top==SIZE-1)
        printf("tsack full\n");
    else{
        S[++top]=item;
    }
}

struct node* pop(){
    if(top==-1){
        printf("stack empty\n");
        return NULL;
    }else{
        return S[top--];
    }
}

void inorder_iter(){
    struct node* ptr=root;
    printf("inorder iter:\n");
    while(ptr!=NULL || top!=-1){
        while(ptr!=NULL){
            push(ptr);
            ptr=ptr->lchild;
        }

        if(top!=-1){
            struct node* temp=pop();
            printf("%d\n",temp->data);
            ptr=temp->rchild;
        }
    }
}

void preorder_iter(){
    struct node* ptr=root;
    printf("preorder iter:\n");
    while(ptr!=NULL || top!=-1){
        while(ptr!=NULL){
            printf("%d\n",ptr->data);
            push(ptr);
            ptr=ptr->lchild;
        }

        if(top!=-1){
            struct node* temp=pop();           
            ptr=temp->rchild;
        }
    }
}

void postorder_iter1(){
    struct node* ptr=root;
    printf("postorder iter:\n");
    do{
        while(ptr!=NULL){
            if(ptr->rchild!=NULL)
                push(ptr->rchild);
            push(ptr);
            ptr=ptr->lchild;
        }

        if(top!=-1){
            struct node* temp=pop();
            if(temp->rchild!=NULL && S[top]==temp->rchild){
                ptr=pop();
                push(temp);
            }else{
                printf("%d\n",temp->data);
                ptr=NULL;
            }
        }
    }while(top!=-1);
}

struct node* S2[SIZE];
int top2=-1;

void push2(struct node* item){
    if(top2==SIZE-1)
        printf("tsack full\n");
    else{
        S2[++top2]=item;
    }
}

struct node* pop2(){
    if(top2==-1){
        printf("stack empty\n");
        return NULL;
    }else{
        return S2[top2--];
    }
}

void postorder_iter2(){
    struct node* ptr=root;
    printf("postorder iter:\n");
    push(root);
    while(top!=-1){
        struct node* temp=pop();
        push2(temp);
        if(temp->lchild!=NULL)
            push(temp->lchild);
        if(temp->rchild!=NULL)
            push(temp->rchild);
    }
    while(top2!=-1)
        printf("%d\n",pop2()->data);
}

void destroy(struct node* root){
    if(root!=NULL){
        destroy(root->lchild);
        destroy(root->rchild);
        free(root);
    }
}

void main(){
    int rt,choice,num;
    root=newNode();
    printf("Enter the root: ");
    scanf("%d",&rt);

    bt(root,rt);

//    inorder(root);
    do{
        printf("Enter the choice:\n1)insert\n2)delete\n3)inorder\n4)preorder\n5)postorder\n6)exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: printf("Enter the num to be inserted: ");
                    scanf("%d",&num);
                    insert(num);
                    inorder(root);
                    break;
            case 2: printf("Enter the num to be deleted: ");
                    scanf("%d",&num);
                    delete(num);
                    inorder(root);
                    break;
            case 3: inorder(root);
                    inorder_iter();
                    break;
            case 4: preorder(root);
                    preorder_iter();
                    break;
            case 5: postorder(root);
                    postorder_iter1();
                    postorder_iter2();
                    break;
            case 6: destroy(root);
                    return ;
        }
    }while(1);
}