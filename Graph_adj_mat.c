#include<stdio.h>
#include<stdlib.h>
#define size 20

struct Graph{
  int** adj_mat;
  int vertices;
};

struct Graph* createGraph(){
  int i,j;
  struct Graph* G=(struct Graph*)malloc(sizeof(struct Graph));
  printf("How many vertices?"); 
  scanf("%d",&G->vertices);

  G->adj_mat=(int**)malloc(G->vertices*sizeof(int*));
  for(i=0 ; i<G->vertices ; i++){
    G->adj_mat[i]=(int*)malloc(sizeof(int)*(G->vertices));
  }

  for(i=0 ; i<G->vertices ; i++)
    for(j=0 ; j<G->vertices ; j++)
      G->adj_mat[i][j]=0;

  return G;
}


void addEdge(struct Graph* G,int src,int des){
  G->adj_mat[src][des]=1;
  G->adj_mat[des][src]=1;
}


void display(struct Graph* G){
  int i,j;
  printf("    ");
  for(i=0 ; i<G->vertices ; i++)
    printf("%5d",i);
  printf("   ----------------------\n");
  for(i=0 ; i<G->vertices ; i++)
  {
    printf("\n%d:  ",i);
    for(j=0 ; j<G->vertices ; j++){
      printf("%5d",G->adj_mat[i][j]);
    }
  }
  printf("\n");
}

void destroy(struct Graph* G){
  int i;
  for(i=0 ; i<G->vertices ; i++)
    free(G->adj_mat[i]);
  free(G->adj_mat);
  free(G);
}

int Q[size],f=-1,r=-1;

void enqueue(int item){
  if(f==((r+1)%size)){
    printf("queue full\n");
    return;
  }
  else if(f==-1){
        r=f=0;
      }
      else if(r==size-1)
              r=0;
            else  
              r++;
  Q[r]=item;
}

int dequeue(){
  if(f==-1){
    printf("queue empty\n");
  }
  else{
    int item=Q[f];
    if(f==size-1)
        f=0;
    else
        f++;
    if(f==(r+1)%size)
      f=r=-1;
    return item;
  }
}

void Qdisplay(){
  int i;
  for(i=f ; i!=r ; i=(i=1)%size)
    printf("%d\n",Q[i]);
  printf("%d\n",Q[r]);
}

int Qempty(){
  return f==-1;
}

void BFS(struct Graph* G,int start){
  int visited[G->vertices],i;
  for(i=0 ; i<G->vertices ; i++)
    visited[i]=0;

  printf("BFS: ");
  enqueue(start);
  visited[start]=1;
  while(f!=-1){
    int temp=dequeue();
    printf("%d\t",temp);
    for(i=0 ; i<G->vertices ; i++)
    {
      int num=G->adj_mat[temp][i];
      if(num==1 && visited[i]==0){
        enqueue(i);
        visited[i]=1;
      }
    }
  }
}

void main(){
  struct Graph* G;
  int choice,src,des;
  G=createGraph();

  do{
    printf("Enter your choice: \n1)addEdge\n2)BFS\n3)DFS\n4)display\n5)exit\n");
    scanf("%d",&choice);
    switch(choice){
      case 1: printf("Enter src and des: ");
              scanf("%d %d",&src,&des);
              if(src==des || src>=G->vertices || des>=G->vertices)
                printf("invalid\n");
              else 
                addEdge(G,src,des);
              display(G);
              break;
      case 2: printf("Enter the starting vertex: ");
              scanf("%d",&src);
              BFS(G,src);
              break;
      case 3: printf("Enter the starting vertex: ");
              scanf("%d",&src);
              //DFS(G,src);
              break;
      case 4: display(G);
              break;
      case 5: destroy(G); 
              return;
    }
  }while(1);
}