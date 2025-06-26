#include<stdio.h>
#define SIZE 10
#define INVALID -9999

int Q1[SIZE],f1=-1,r1=-1;

void enqueue1(int item){
    if(r1==SIZE-1)
        printf("queue full\n");
    else{
        if(f1==-1)
            f1=0;
        r1++;
        Q1[r1]=item;
    }
}

int dequeue1(){
    if(f1==-1)
        return INVALID;
    else{
        int item=Q1[f1];
        f1++;
        if(f1==r1+1)
            f1=r1=-1;
        return item;
    }
}

int Q2[SIZE],f2=-1,r2=-1;

void enqueue2(int item){
    if(r2==SIZE-1)
        printf("queue full\n");
    else{
        if(f2==-1)
            f2=0;
        r2++;
        Q2[r2]=item;
    }
}

int dequeue2(){
    if(f2==-1)
        return INVALID;
    else{
        int item=Q2[f2];
        f2++;
        if(f2==r2+1)
            f2=r2=-1;
        return item;
    }
}


/*int pop(){
    int item=dequeue1();
    return item;
}

void push(int item){
    if(r1==SIZE-1)
        return;
    while(f1!=-1){
        int num=dequeue1();
        enqueue2(num);
    }
    enqueue1(item);
    while(f2!=-1){
        int num=dequeue2();
        enqueue1(num);
    }
}*/

void push(int item){
    enqueue1(item);
}

int pop(){
    int item;
    if(f1==-1){
        printf("stack empty\n");
        return INVALID;
    }.
    while(f1!=r1){
        int num=dequeue1();
        enqueue2(num);
    }
    item=dequeue1();
    while(f2!=-1){
        int num=dequeue2();
        enqueue1(num);
    }
    return item;
}

void main(){
    int i;
    for(i=0 ; i<15 ; i++)
        push(i);
    for(i=0 ; i<15 ; i++)
        printf("%d\n",pop());
}