/*
    Name: Karanvir Basson
    Title: Topological Sort Algorithm
    Date: 04-23-2022
*/

#include "topologicalSort.h"

int getAdjacencyMatrix(int adjacencyMatrix[NUM_NODES][NUM_NODES]) { //Given a file containing an adjacency matrix and store it in 2d array

    FILE* file = fopen(FILENAME, "r"); //Open file for reading

    if (file == NULL) { //If file doesn't exist

        printf("%s not found!\n", FILENAME);
        return 0;

    }
    
    for (int i = 0; i < NUM_NODES; i++) { //Initialize matrix to all zeores

        for (int j = 0; j < NUM_NODES; j++) {

            adjacencyMatrix[i][j] = 0;

        }

    }

    int size = ((NUM_NODES * 2) + 2) * sizeof(char); //Get size of string contining row of matrix
    char matrixRow[size]; //Initialize string contining row of matrix

    int i = 0; //Row index

    while (fgets(matrixRow, size, file)) { //Read matrix

        int j = 0;//Column index
        char* entry = strtok(matrixRow, " \n"); //Get current matrix entry as string

        while (entry != NULL) { //If string entry is not null

            adjacencyMatrix[i][j] = atoi(entry); //Convert string to int
            entry = strtok(NULL, " \n"); //Get next entry
            j++;

        }

        i++;

    }

    fclose(file); //Close file ptr
    return 1;

}

int connectNodes(Node* nodes[NUM_NODES], int adjacencyMatrix[NUM_NODES][NUM_NODES]) { //Given a list of nodes and an adjacency matrix, create graph edges

    for (int i = 0; i < NUM_NODES; i++) { //For all rows in matrix

        for (int j = 0; j < NUM_NODES; j++) { //For all columns in matrix

            if (adjacencyMatrix[i][j] == 1) { //If edge exists

                if (nodes[i] -> edges == NULL) { //If no edges currently in list

                    nodes[i] -> edges = createEdge(nodes[j]); //Create edge
                    if (nodes[i] -> edges == NULL) return 0; //NULL ptr check

                } else { //if edges already exist

                    Edge* temp = nodes[i] -> edges; //Temp pointer to first edge

                    while (temp -> next != NULL) { //Get last edge

                        temp = temp -> next;

                    }

                    temp -> next = createEdge(nodes[j]); //Create edge
                    if (temp -> next == NULL) return 0; //NULL ptr check

                }

            }

        }

    }

    return 1; //Return 1, indicating success

}

Node* createNode(char id[ID_SIZE]) { //Given an id, create a node with that id

    Node* node = malloc(sizeof(Node)); //Allocate memory
    if (node == NULL) return NULL; //NULL ptr check

    //Initialize Node
    strcpy(node -> id, id);
    node -> edges = NULL;
    node -> visited = 0;

    return node; //Return node

}

void printNode(Node* node) { //Given a node, print it

    if (node == NULL) return; //NULL ptr check
    
    //PRINT NODE INFO
    printf("\nNode ID: %s\nVisited = %d\n%s EDGES:\n\n", node -> id, node -> visited, node -> id);
    printEdges(node -> edges);

}

void freeNode(Node* node) { //Given a node, free it

    if (node == NULL) return; //NULL ptr check

    //FREE NODE EDGES
    while (node -> edges != NULL) {

        Edge* temp = node -> edges;
        node -> edges = node -> edges -> next;
        free(temp);

    }

    //FREE NODE
    free(node);

}

Edge* createEdge(Node* dest) { //Given a destination, create edge

    if (dest == NULL) return NULL; //NULL ptr check

    Edge* edge = malloc(sizeof(Edge)); //Allocate struct
    if (edge == NULL) return NULL; //NULL ptr check

    //INITIALIZE EDGE
    edge -> dest = dest;
    edge -> visited = 0;
    edge -> next = NULL;

    return edge; //Return newly allocated edge

}

void printEdges(Edge* edge) { //Given a list of edges, print info

    if (edge == NULL) return; //NULL ptr check
    if (edge -> dest != NULL) printf("DEST ID: %s\n", edge -> dest -> id); //Print id of destination

    //Display if edge was visited
    if (edge -> visited) printf("Edge was visited\n");
    else printf("Edge was NOT visited\n");

    printEdges(edge -> next); //Print next edge

}

void topologicalSort(Node* nodes[NUM_NODES]) { //Given a graph, display array in topological order

    if (nodes == NULL || NUM_NODES <= 1) return; //NULL ptr check

    //Array that holds topologically sorted graph
    int popIndex = 0;
    Node* popStack[NUM_NODES];

    for (int i = 0; i < NUM_NODES; i++) { //Initialize popstack

        popStack[i] = NULL;

    }

    while (popIndex < (NUM_NODES - 1)) { //While not all node have been added to popStack

        Node* current = NULL; //First node in current traversal
        int i = 0; //Index used to find current node
        
        do { //Find first node to begin traversal
            
            current = nodes[i++]; //Initizalize current node
            if (current == NULL) return;

        } while (current -> visited == 1 && i < NUM_NODES);

        if (i >= NUM_NODES) break; //If all nodes have been visited, shouldn't ever occur due to while loop condition

        //Temporary stack to hold traversed nodes
        int travIndex = 0;
        Node* traversalStack[NUM_NODES];

        for (int i = 0; i < NUM_NODES; i++) { //Initialize traversalStack

            traversalStack[i] = NULL;

        }

        traversalStack[0] = current; //Initizalize stack

        while (travIndex >= 0) { //While traversal stack not empty

            //printf("Node ID: %s\n", current -> id); //Print current visited node
            Edge* nextEdge = current -> edges; //Get next edge

            while (nextEdge != NULL && nextEdge -> dest -> visited) { //Find next vertex we can access that hasn't been accessed yet
                    
                nextEdge = nextEdge -> next;

            }

            if (nextEdge != NULL) { //If next vertex exists

                nextEdge -> visited = 1; //Mark edge as visited
                traversalStack[++travIndex] = nextEdge -> dest; //Push next verted to traversal stack

            } else { //If next vertex doesn't exist

                current -> visited = 1; //Set current node to visited
                traversalStack[travIndex--] = NULL; //Pop current node from traversal stack
                popStack[popIndex++] = current; //Push current node to pop stack

            }

            current = traversalStack[travIndex]; //Update current node

        }

        //printf("\n");

    }

    //DISPLAY RESULTS OF TOPOLOGICAL SORT

    printf("\nPOPSTACK FINAL! \n");

    for (int i = popIndex - 1; i >= 0; i--) {

        printf("Node ID: %s\n", popStack[i] -> id);

    }

    printf("\n");

}
