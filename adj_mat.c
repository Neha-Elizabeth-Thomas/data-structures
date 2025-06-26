#include<stdio.h>
#include<stdlib.h>

int** createGraph(int vertices)
{
  int** G,i,j;
  
  G=(int**)malloc(vertices*sizeof(int*));
  for(i=0 ; i<vertices ; i++)
  {
    G[i]=(int*)malloc(vertices*sizeof(int));
    for(j=0 ; j<vertices ; j++)
      G[i][j]=0;
  }
  return G;
}

void addEdge(int** G,int src,int des)
{
  G[src][des]=1;
  G[des][src]=1;//since this is an undirected graph
}

void display(int** G,int vertices)
{
  int i,j;
  for(i=0 ; i<vertices ; i++)
  {
    for(j=0 ; j<vertices ; j++)
        printf("%5d",G[i][j]);
    printf("\n");
  }
}

void main()
{
  int **G,vertices,n,src,des,i;
  printf("How many vertices: ");
  scanf("%d",&vertices);
  G=createGraph(vertices);

  printf("How many edges? ");
  scanf("%d",&n);
  for(i=0 ; i<n ; i++)
  {
    printf("Edge %d(src,des) : ",i+1);
    scanf("%d %d",&src,&des);
    if(src==des || src>vertices || des>vertices)
    {
        printf("Invalid source or destination\n");
        i--;
        continue;
    }
    addEdge(G,--src,--des);
  }
  display(G,vertices);
}