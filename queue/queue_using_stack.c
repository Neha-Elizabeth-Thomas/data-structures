#include<stdio.h>
#define SIZE 10
#define INVALID -9999

int S1[SIZE],top1=-1;
//S1 act as queue
void push1(int item){
    if(top1==SIZE-1){
        printf("stack full\n");
    }else
        S1[++top1]=item;
}

int pop1(){
    if(top1==-1)
        return INVALID;
    else
        return S1[top1--];
}

int S2[SIZE],top2=-1;

void push2(int item){
    if(top2==SIZE-1){
        printf("stack full\n");
    }else
        S2[++top2]=item;
}

int pop2(){
    if(top2==-1)
        return INVALID;
    else
        return S2[top2--];
}

/*void enqueue( int item){
    push1(item);
}

int dequeue(){
    int item;
    while(top1>0){
        int num=pop1();
        push2(num);
    }
    item=pop1();
    while(top2>-1){
        int num=pop2();
        push1(num);
    }
    return item;
}*/

int dequeue(){
    int item=pop1();
    return item;
}

void enqueue(int item){
    if(top1==SIZE-1)
        return;
    while(top1!=-1){
        int num=pop1();
        push2(num);
    }
    push1(item);
    while(top2!=-1){
        int num=pop2();
        push1(num);
    }
}

void main(){
    int i;
    /*for(i=0 ; i<15 ; i++)
        push1(i);

    for(i=0 ; i<15 ; i++)
        printf("%d\n",pop1());
    printf("\n\n");
    for(i=0 ; i<15 ; i++)
        push2(i);

    for(i=0 ; i<15 ; i++)
        printf("%d\n",pop2());
     printf("\n\n");*/
    for(i=0 ; i<15 ; i++)
        enqueue(i);

    for(i=0 ; i<15 ; i++)
        printf("%d\n",dequeue());
}