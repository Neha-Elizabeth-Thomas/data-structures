#include<stdio.h>
#include<stdlib.h>
#define SIZE 20
struct node{
  int data;
  struct node* lchild;
  struct node* rchild;
}*root=NULL;

struct node* Q[SIZE];
int f=-1,r=-1;

void enqueue(struct node* item){
  if(f==(r+1)%SIZE){
    printf("queue overflow\n");
    return;
  }else if(f==-1)
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
  }
  else{
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

void Qdisplay(){
  int i;
  printf("Queue\n");
  for(i=f ; i!=r ; i=(i+1)%SIZE)
    printf("%d\n",Q[i]->data);
  printf("%d\n",Q[r]->data);
}

int Qempty(){
  return f==-1;
}

struct node* newNode(int data){
  struct node* new=(struct node*)malloc(sizeof(struct node));
  new->data=data;
  new->lchild=new->rchild=NULL;
  return new;
}

void insert(int num){
  struct node* new=newNode(num);
  if(root==NULL){
    root=new;
    return;
  }

  enqueue(root);
  while(f!=-1){
    struct node* temp=dequeue();
    if(temp->lchild==NULL){
      temp->lchild=new;
      f=r=-1;
      return;
    }else {
      enqueue(temp->lchild);
    }

    if(temp->rchild==NULL){
      temp->rchild=new;
      f=r=-1;
      return;
    }else{
      enqueue(temp->rchild);
    }
    
  }
}

void delete(int num){
  struct node* keynode=NULL,*prev,*temp;
  if(root==NULL)
    return;
  if(root->data==num && root->lchild==NULL && root->rchild==NULL){
    root=NULL;
    return;
  }
  enqueue(root);
  while(!Qempty){
    temp=dequeue();

    if(temp->data==num){
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
  if(keynode==NULL){
    printf("%d not found\n",num);
  }
  else{
    keynode->data=temp->data;
    if(prev->lchild==temp)
      prev->lchild=NULL;
    else  
      prev->rchild=NULL;
    free(temp);
  }
}

struct node* Q2[SIZE];
int f2=-1,r2=-1;

void enqueue2(struct node* item){
  if(f2==(r2+1)%SIZE){
    printf("queue overflow\n");
    return;
  }else if(f2==-1)
          f2=r2=0;
        else if(r2==SIZE-1)
                r2=0;
              else
                r2++;
  Q2[r2]=item;
}

struct node* dequeue2(){
  if(f2==-1){
    printf("queue empty\n");
    return NULL;
  }
  else{
    struct node* item=Q2[f2];
    if(f2==SIZE-1)
      f2=0;
    else 
      f2++;
    if(f2==(r2+1)%SIZE)
      f2=r2=-1;
    return item;
  }

}


void display(){
  f2=r2=-1;
  enqueue(root);
  while(f2!=-1){
    struct node* temp=dequeue();
    printf("%d\t",temp->data);

    if(temp->lchild)
      enqueue2(temp->lchild);
    if(temp->rchild)
      enqueue2(temp->rchild);
  }
}

void main(){
  int choice,num;
  do{
    printf("Enter your choice:\n1)insert\n2)delete\n3)preorder\n4)postorder\n5)inorder\n6)exit\n");
    scanf("%d",&choice);

    switch(choice){
      case 1: printf("Enter the num to be inserted: ");
              scanf("%d",&num);
              insert(num);
              printf("successfully inserted\n");
              display();
              printf("successfully inserted\n");
              break;
    }
  }while(1);
}