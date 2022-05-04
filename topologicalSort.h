/*
    Name: Karanvir Basson
    Title: Topological Sort Algorithm
    Date: 04-23-2022
*/

//INCLUDE HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_NODES 7 //Number of nodes in graph
#define FILENAME "graph.txt" //Name of file containing adjacency matrix
#define ID_SIZE 20 //Num chars in Node id string

typedef struct node { //Struct representing graph node

    char id[ID_SIZE]; //String containing node ID
    struct edge* edges; //List of edges
    int visited; //Integer indicating if node has been visited

} Node;

typedef struct edge { //Struct representing graph edge

    struct node* dest; //String containing destination node ID
    int visited; //Integer indicating if edge has been visited
    struct edge* next; //Pointer to next edge

} Edge;

int getAdjacencyMatrix(int adjacencyMatrix[NUM_NODES][NUM_NODES]); //Given a file containing an adjacency matrix and store it in 2d array
int connectNodes(Node* nodes[NUM_NODES], int adjacencyMatrix[NUM_NODES][NUM_NODES]); //Given a list of nodes and an adjacency matrix, create graph edges

Node* createNode(char id[ID_SIZE]); //Given an id, create a node with that id
void printNode(Node* node); //Given a node, print it
void freeNode(Node* node); //Given a node, free it

Edge* createEdge(Node* dest); //Given a destination, create edge
void printEdges(Edge* edge); //Given a list of edges, print info

void topologicalSort(Node* nodes[NUM_NODES]); //Given a graph, display array in topological order
