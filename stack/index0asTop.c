#include<stdio.h>
#define SIZE 10
#define INVALID -9999

int A[SIZE],first=-1;

void push(int item){
    if(first==SIZE-1)
        printf("stack full\n");
    else if(first==-1)
                A[++first]=item;
        else{
            int i;
            for(i=first ; i>=0 ; i--)
                A[i+1]=A[i];
            A[0]=item;
            first++;//imp
        }         
}

int pop(){
    if(first==-1)
        return INVALID;
    else{
        int item=A[0];
        int i;
        for(i=1 ; i<=first ; i++)
            A[i-1]=A[i];
        first--;
        return item;
    }
}

void display(){
    int i;
    printf("index 0:\n");
    for(i=0 ; i<=first ; i++)
        printf("%d\n",A[i]);
    printf("first inserted element\n\n");
}

void main(){
    int choice,num;
    do{
        printf("Enter your choice:\n1)push\n2)pop\n3)display\n4)exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: printf("Enter the num to be pushed: ");
                    scanf("%d",&num);
                    push(num);
                    display();
                    break;
            case 2: printf("popped=%d\n",pop());
                    display();
                    break;  
            case 3: display();
                    break;
            case 4: return;
        }
    }while(1);
}