/*
    Name: Karanvir Basson
    Title: Topological Sort Algorithm
    Date: 04-23-2022
*/

#include "topologicalSort.h"

int main() {

    int adjacencyMatrix[NUM_NODES][NUM_NODES]; //Integer matrix representing adjacency matrix
    int res = getAdjacencyMatrix(adjacencyMatrix); //Initialize adjacency matrix from file
    if (res == 0) return -1; //If file read doesn't work

    Node* nodes[NUM_NODES]; //Array of nodes in graph
    char* IDs[NUM_NODES] = {"plankton", "shrimp", "fish", "wheat", "sheep", "human", "tiger"}; //IDs of nodes

    for (int i = 0; i < NUM_NODES; i++) { //Create all nodes in array

        nodes[i] = createNode(IDs[i]); //Create node
        if (nodes[i] == NULL) return -1; //If node creation fails

    }

    res = connectNodes(nodes, adjacencyMatrix); //Connect all nodes using adjacency matrix
    if (res == 0) return -1; //If node connection fails

    topologicalSort(nodes); //Topological sort algorithm

    for (int i = 0; i < NUM_NODES; i++) { //For all nodes

        freeNode(nodes[i]); //Free current node

    }

    return 1;

}
