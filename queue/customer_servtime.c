#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 5

struct customer{
    char name[30];
    int no;
    int serv_time;
};

struct customer* Q[SIZE];
int f=-1,r=-1;

struct customer* newCustomer(char name[],int no,int serv_time){
    struct customer* new=(struct customer*)malloc(sizeof(struct customer));
    strcpy(new->name,name);
    new->no=no;
    new->serv_time=serv_time;
    return new;
}

void enqueue(char name[],int no,int serv_time){
    struct customer* new=newCustomer(name,no,serv_time);
    if(f==(r+1)%SIZE){
        free(new);
        printf("queue full\n");
        return;
    }
    else if(f==-1)
            f=r=0;
            else if(r==SIZE-1)
                    r=0;
                    else
                        r++;
    Q[r]=new;
}

struct customer* dequeue(){
    if(f==-1){
        printf("queue empty\n");
        return NULL;
    }else{
        struct customer* item=Q[f];
        if(f==SIZE-1)
            f=0;
        else
            f++;
        if(f==(r+1)%SIZE)
            f=r=-1;
        return item;
    }
}

void display(){
    int i;
    printf("Customer queue:\n");
    printf("----------------------\nfront:\n");
    if(f==-1){
        printf("EMPTY\n");
        return;
    }
    for(i=f ; i!=r ; i=(i+1)%SIZE){
        printf("customer no=%d\n",Q[i]->no);
        printf("customer name=%s\n",Q[i]->name);
        printf("customer serv_time=%d\n\n",Q[i]->serv_time);
    }
    printf("customer no=%d\n",Q[r]->no);
    printf("customer name=%s\n",Q[r]->name);
    printf("customer serv_time=%d\n\n",Q[r]->serv_time);
    printf("rear\n-----------------------\n\n");
}

void printWaitingTime(int custNo){
    int wait_time=0,i;
    for(i=f ; i!=r ; i=(i+1)%SIZE){
        if(Q[i]->no==custNo)
            break;
        wait_time+=Q[i]->serv_time;
    }
    if(i!=r || Q[r]->no==custNo)
        printf("waiting time=%d\n",wait_time);
    else 
        printf("cust no %d not found\n",custNo);
}

void destroy(){
    int i;
    for(i=f ; i!=r ; i=(i+1)%SIZE)
        free(Q[i]);
    free(Q[r]);
}

void main(){
    int choice,no,serv_time;
    struct customer* c;
    char name[30];
    do{
        printf("Enter choice:\n1)enqueue\n2)dequeue\n3)print wait_time\n4)display\n5)exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: printf("Enter the cust num to be enqueued: ");
                    scanf("%d",&no);
                    printf("Enter the cust name: ");
                    scanf(" %[^\n]",name);
                    printf("Enter the cust serv_time: ");
                    scanf("%d",&serv_time);
                    enqueue(name,no,serv_time);
                    display();
                    break;
            case 2: c=dequeue();
                    printf("cust name : %s\n",c->name);
                    display();
                    break;
            case 3: printf("Enter the cust num : ");
                     scanf("%d",&no);
                    printWaitingTime(no);
                    break;
            case 4: display();
                    break;
            case 5: destroy();
                    return;
        }
    }while(1);
}