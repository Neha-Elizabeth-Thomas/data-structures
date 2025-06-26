#include <stdio.h>
#include <stdlib.h>

// Node structure for representing a vertex in the graph
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Graph structure with an array of adjacency lists
typedef struct Graph {
    int vertices;
    Node** adjList;
} Graph;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjList = (Node**)malloc(vertices * sizeof(Node*));

    for (int i = 0; i < vertices; ++i)
        graph->adjList[i] = NULL;

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Function to perform Breadth First Search
void BFS(Graph* graph, int start) {
    int* visited = (int*)malloc(graph->vertices * sizeof(int));
    for (int i = 0; i < graph->vertices; ++i)
        visited[i] = 0;

    // Create a queue for BFS
    int* queue = (int*)malloc(graph->vertices * sizeof(int));
    int front = -1, rear = -1;

    // Enqueue the starting vertex and mark it as visited
    queue[++rear] = start;
    visited[start] = 1;

    printf("Breadth First Search starting from vertex %d: ", start);

    while (front < rear) {
        int current = queue[++front];
        printf("%d ", current);

        // Visit all adjacent vertices of the current vertex
        Node* temp = graph->adjList[current];
        while (temp != NULL) {
            int adjVertex = temp->data;
            if (!visited[adjVertex]) {
                queue[++rear] = adjVertex;
                visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }

    printf("\n");

    free(visited);
    free(queue);
}

// Recursive function for Depth First Search
void DFSUtil(Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    // Visit all adjacent vertices of the current vertex
    Node* temp = graph->adjList[vertex];
    while (temp != NULL) {
        int adjVertex = temp->data;
        if (!visited[adjVertex]) {
            DFSUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

// Function to perform Depth First Search
void DFS(Graph* graph, int start) {
    int* visited = (int*)malloc(graph->vertices * sizeof(int));
    for (int i = 0; i < graph->vertices; ++i)
        visited[i] = 0;

    printf("Depth First Search starting from vertex %d: ", start);
    DFSUtil(graph, start, visited);
    printf("\n");

    free(visited);
}

int main() {
    // Create a graph with 5 vertices
    Graph* graph = createGraph(5);

    // Add edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);

    // Perform BFS starting from vertex 0
    BFS(graph, 0);

    // Perform DFS starting from vertex 0
    DFS(graph, 0);

    // Free allocated memory
    free(graph->adjList);
    free(graph);

    return 0;
}
