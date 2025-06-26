#include<stdio.h>
#include<stdlib.h>

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

void swap(struct node* a,struct node* b){
    struct node temp=*a;
    *a=*b;
    *b=temp;
}

/*void sort(){
    struct node* i,*j,*temp;
    i=head->link;
    while(i->link!=NULL){
        j=i->link;
        while(j!=NULL){
            if(i->data>j->data){
                swap(i,j);
                temp=i->link;
                i->link=j->link;
                j->link=temp;
            }
            j=j->link;
        }
        i=i->link;
    }
}
*/

void bubblesort(){
    struct node *j,*end,*temp,*prev;
    int i,n=1,swapped;
    end=head->link;
    while(end->link!=NULL){
        n++;
        end=end->link;
    }
    for(i=1 ; i<=n-1 ; i++){
        j=head->link;
        swapped=0;
        while(j!=end){
            if(j->data > j->link->data){
                struct node* k=j->link;
                swap(j,k);
                swapped=1;
                temp=j->link;
                j->link=k->link;
                k->link=temp;
                /*int data=j->data;
                j->data=j->link->data;  
                j->link->data=data; 
                swapped=1;*/
            }
            prev=j;
            j=j->link;
        }
        if(!swapped)
            break;
        end=prev;
    }
}

void sort(){
    struct node* i,*j,*temp;

    i=head->link;
    while(i->link!=NULL){
        struct node* min=i;
        j=i->link;
        while(j!=NULL){
            if(j->data<min->data)
                min=j;
            j=j->link;
        }
        if(min!=i){
            swap(i,min);
            temp=i->link;
            i->link=min->link;
            min->link=temp;
        }
        i=i->link;
    }
}

int findMax(){
    struct node* ptr=head->link;
    struct node* max=ptr;
    ptr=ptr->link;
    while(ptr!=NULL){
        if(ptr->data > max->data)
            max=ptr;
        ptr=ptr->link;
    }
    return max->data;
}

void display(){
    struct node* ptr=head->link;
    printf("List\n-------------\n");
    while(ptr!=NULL){
        printf("%d -> ",ptr->data);
        ptr=ptr->link;
    }
    printf("\b \b\b \b\b \b\n---------------\n");
}

void destroy(){
    struct node* ptr=head;
    while(ptr!=NULL){
        struct node* temp=ptr->link;
        free(ptr);
        ptr=temp;
    }
}

void main(){
    int n,i,num;
    struct node* ptr;
    head=newNode(0);
    printf("How many numbers?");
    scanf("%d",&n);
    printf("Enter %d num: ",n);

    ptr=head;
    for(i=0 ; i<n ; i++){
        struct node* new;
        scanf("%d",&num);
        new=newNode(num);
        ptr->link=new;
        ptr=new;
    }
    display();
    printf("max=%d\n",findMax());
    bubblesort();

    display();
    destroy();
}