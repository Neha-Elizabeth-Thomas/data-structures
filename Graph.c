#include<stdio.h>
#include<stdlib.h>

int q[20],f=-1,r=-1,s[10],top=-1;

struct node{
  int data;
  struct node* link;
};

struct graph
{
  int vertices;
  struct node** adj_list;//arry of struct node*
};

struct node* newNode(int data)
{
  struct node* new=(struct node*)malloc(sizeof(struct node));
  new->data=data;
  new->link=NULL;
  return new;
}

struct graph* createGraph()
{
  int i;
  struct graph* G=(struct graph*)malloc(sizeof(struct graph));
  printf("How many vertices? ");
  scanf("%d",&(G->vertices));

  G->adj_list=(struct node**)malloc((G->vertices)*sizeof(struct node*));
  for(i=0 ; i<G->vertices ; i++)
  {
    G->adj_list[i]=newNode(-1);//G->adj_list[i] act as the head 
    G->adj_list[i]->link=NULL;
  }

  return G;
}

void addEdge(struct graph* G,int src,int des)
{
  struct node* new=newNode(des);
  new->link=G->adj_list[src]->link;
  G->adj_list[src]->link=new; //insert at beg

  new=newNode(src);
  new->link=G->adj_list[des]->link;
  G->adj_list[des]->link=new;
}

void display(struct graph* G)
{
  int i;
  struct node* ptr;
  printf("ADJACENCY LIST rep of graph:\n");
  for(i=0 ; i<G->vertices ; i++)
  {
    printf("%d:  ",i);
    ptr=G->adj_list[i]->link;
    while(ptr!=NULL)
    {
      printf("%5d",ptr->data);
      ptr=ptr->link;
    }
    printf("\n\n");
  }
}

void enqueue(int item)
{
  if(f==-1)
    f=0;
  r++;
  q[r]=item;
}

int dequeue()
{
  if(f!=-1)
  {
    int item=q[f];
    f++;
    if(f==r+1)
      f=r=-1;
    return item;
  }
}

void BFS(struct graph* G,int start)
{
  int i;
  int* visited=(int*)malloc(G->vertices*sizeof(int));
  for(i=0 ; i<G->vertices ; i++)
    visited[i]=0;

  printf("BFS starting from %d:\n",start);

  enqueue(start);
  visited[start]=1;
  while(f!=-1)
  {
    struct node* temp;
    int num=dequeue();
    printf("%5d",num);

    temp=G->adj_list[num]->link;
    while(temp!=NULL)   
    {
      if(!visited[temp->data]){
        enqueue(temp->data);
        visited[temp->data]=1;
      }
      temp=temp->link;
    }
  }
  printf("\n\n");
  free(visited);
}

void push(int item)
{
  s[++top]=item;
}

int pop()
{
  if(top!=-1)
    return s[top--];
}

void DFS(struct graph* G,int start)
{
  int i;
  int* visited=(int*)malloc(G->vertices*sizeof(int));
  for(i=0 ; i<G->vertices ; i++)
    visited[i]=0;

  printf("DFS starting from %d:\n",start);

  push(start);
  visited[start]=1;
  while(top!=-1)
  {
    struct node* temp;
    int num=pop();
    printf("%5d",num);

    temp=G->adj_list[num]->link;
    while(temp!=NULL)   
    {
      if(!visited[temp->data])
        push(temp->data);
      visited[temp->data]=1;
      temp=temp->link;
    }
  }
  printf("\n\n");
}

void DFS_recursive(struct Graph* G,int start){
  
}

void main()
{
  int i,n,src,des,start,choice;
  struct graph*G=createGraph();

  printf("How many edges? ");
  scanf("%d",&n);
  for(i=0 ; i<n ; i++)
  {
    printf("Edge %d: ",i+1);
    scanf("%d %d",&src,&des);
    if(src==des || src>=G->vertices || des>=G->vertices)
    {
        printf("Invalid source or destination\n");
        i--;
        continue;
    }
    addEdge(G,src,des);
  }

  display(G);
  do 
  {
    printf("Enter your choice:\n1)BFS\n2)DFS\n3)EXIT\n");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1: printf("Enter the starting point: ");
              scanf("%d",&start);
              BFS(G,start);
              break;
      case 2: printf("Enter the starting point: ");
              scanf("%d",&start);
              DFS(G,start);
              break;
    }
  }
  while(choice!=3);

  free(G->adj_list);
  free(G);
}