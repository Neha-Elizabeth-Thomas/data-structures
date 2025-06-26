#include<stdio.h>
#include<stdlib.h>

#define SIZE 20

struct node{
  int data;
  struct node* link;
};

struct Graph{
  int vertices;
  struct node** adj_list;
};

struct node* newNode(int data){
  struct node* new=(struct node*)malloc(sizeof(struct node));
  new->data=data;
  new->link=NULL;
  return new;
}

struct Graph* createGraph(){
  int i;
  struct Graph* G=(struct Graph*)malloc(sizeof(struct Graph));
  printf("How many vertices: ");
  scanf("%d",&G->vertices);

  G->adj_list=(struct node**)malloc(G->vertices*sizeof(struct node*));
  for(i=0 ; i<G->vertices ; i++){
    G->adj_list[i]=newNode(-1);//adj_list[i]=head of list of vertices adj to i^th vertex
  }

  return G;
}

void addEdge(struct Graph*G,int src,int des){
  struct node* new=newNode(des);
  new->link=G->adj_list[src]->link;//insert_beg T=O(1)
  G->adj_list[src]->link=new;

  new=newNode(src);
  new->link=G->adj_list[des]->link;
  G->adj_list[des]->link=new;
}

void display(struct Graph* G){
  int i;
  for(i=0 ; i<G->vertices ; i++){
    struct node* ptr=G->adj_list[i]->link;
    printf("%d|",i);
    while(ptr!=NULL){
      printf("  %d  ->",ptr->data);
      ptr=ptr->link;
    }
    printf("\n");
  }
}

void destroy(struct Graph* G){
  int i;
  for(i=0 ; i<G->vertices ; i++){
    struct node* ptr=G->adj_list[i];
    while(ptr!=NULL){
      struct node* temp=ptr->link;
      free(ptr);
      ptr=temp;
    }
    free(G->adj_list);
    free(G);
  }

  free(G->adj_list);
  free(G);
}

int Q[SIZE],f=-1,r=-1;

void enqueue(int item){
  if(r==SIZE-1)
    printf("queue overflow\n");
  else{
    if(f==-1)
      f=0;
    r++;
    Q[r]=item;
  }
}

int dequeue(){
  if(f==-1)
  {
    printf("queue empty\n");
    return -9999;
  }
  else{
    int item=Q[f];
    f++;
    if(f==(r+1))
      f=r=-1;
    return item;
  }
}

void BFS(struct Graph* G,int start){
  int visited[G->vertices],i;
  for(i=0 ; i<G->vertices ; i++)
    visited[i]=0;

  enqueue(start);
  visited[start]=1;
  printf("BFS:  ");
  while(f!=-1){
    int temp=dequeue();
    struct node* ptr=G->adj_list[temp]->link;
    printf("%5d",temp);

    while(ptr!=NULL){
      if(visited[ptr->data]==0){
        enqueue(ptr->data);
        visited[ptr->data]=1;
      }
      ptr=ptr->link;
    }
  }
  printf("\n");
}

void DFS_rec(struct Graph* G,int start,int visited[]){
  //static int visited[G->vertices];
  struct node* ptr=G->adj_list[start]->link;
  visited[start]=1;
  printf("%5d\n",start);
  while(ptr!=NULL){
    if(!visited[ptr->data])
      DFS_rec(G,ptr->data,visited);
    ptr=ptr->link;
  }
}

int s[SIZE],top=-1;

void push(int item){
  if(top==SIZE-1){
    printf("stack full\n");
  }else{
    s[++top]=item;
  }
}

int pop(){
  if(top==-1){
    printf("stack is empty\n");
  }else{
    return s[top--];
  }
}

void DFS(struct Graph* G,int start){
  int visited[G->vertices],i;
  for(i=0 ; i<G->vertices ; i++)
    visited[i]=0;

  push(start);
  visited[start]=1;
  printf("DFS:  ");
  while(top!=-1){
    int temp=pop();
    struct node* ptr=G->adj_list[temp]->link;
    printf("%5d",temp);

    while(ptr!=NULL){
      if(visited[ptr->data]==0){
        push(ptr->data);
        visited[ptr->data]=1;
      }
      ptr=ptr->link;
    }
  }
  printf("\n");
}


void main(){
  int choice,src,des;
  struct Graph* G=createGraph();
  int visited[G->vertices],i;
  
  do{
    printf("Enter your choice: \n1)add edges\n2)BFS\n3)DFS\n4)display\n5)exit\n");
    scanf("%d",&choice);

    switch(choice){
      case 1: printf("Enter sorce and destination: ");
              scanf("%d %d",&src,&des);
              if(src>=G->vertices || des>=G->vertices || src==des)
                  printf("invalid vertex num\n");
              else
                  addEdge(G,src,des);
              display(G);
              break;
      case 2: printf("Enter starting vertex: ");
              scanf("%d",&src);
              if(src>=G->vertices)
                  printf("invalid vertex num\n");
              else
                  BFS(G,src);
              break;
      case 3: printf("Enter starting vertex: ");
              scanf("%d",&src);
              if(src>=G->vertices)
                  printf("invalid vertex num\n");
              else{
                   printf("DFS\n");
                   DFS(G,src);
                   for(i=0 ; i<G->vertices ; i++)
                    visited[i]=0;
                   DFS_rec(G,src,visited);
              }
              break;
      case 5: destroy(G);
              return ;
    }
  }while(1);
}