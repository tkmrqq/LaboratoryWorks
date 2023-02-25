#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Graph structure
struct Graph {
    int V;    // Number of vertices
    int **adj;// Adjacency matrix
};

// Function to create a new graph with V vertices
struct Graph *create_graph(int V) {
    struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph));
    graph->V = V;

    // Allocate memory for the adjacency matrix
    graph->adj = (int **) malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        graph->adj[i] = (int *) malloc(V * sizeof(int));
        memset(graph->adj[i], 0, V * sizeof(int));
    }

    return graph;
}

// Function to add an edge to the graph
void add_edge(struct Graph *graph, int u, int v) {
    graph->adj[u][v] = 1;
    graph->adj[v][u] = 1;
}

// Function to find the maximum independent set
void max_independent_set(struct Graph *graph, int *independent_set) {
    // Initialize the set of vertices
    int *vertices = (int *) malloc(graph->V * sizeof(int));
    for (int i = 0; i < graph->V; i++) {
        vertices[i] = i;
    }

    int set_size = 0;
    // Loop until all vertices are covered
    while (set_size < graph->V) {
        // Choose a vertex with the smallest degree
        int min_degree = graph->V;
        int min_degree_vertex = -1;
        for (int i = 0; i < graph->V; i++) {
            if (graph->adj[i][i] != -1 && graph->adj[i][i] < min_degree) {
                min_degree = graph->adj[i][i];
                min_degree_vertex = i;
            }
        }

        // Add it to the independent set
        independent_set[set_size++] = min_degree_vertex;

        // Remove it and its neighbors from the set of vertices
        for (int i = 0; i < graph->V; i++) {
            if (graph->adj[min_degree_vertex][i] == 1) {
                graph->adj[i][i] = -1;// Mark the vertex as deleted
                for (int j = 0; j < graph->V; j++) {
                    graph->adj[i][j] = 0;
                    graph->adj[j][i] = 0;
                }
            }
        }
    }

    // Free memory
    free(vertices);
}

// Driver code
int main() {
    // Create a graph
    int V = 5;
    struct Graph *graph = create_graph(V);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 3);
    add_edge(graph, 3, 4);

    // Find the maximum independent set
    int *independent_set = (int *) malloc(V * sizeof(int));
    max_independent_set(graph, independent_set);

    // Print the maximum independent set
    printf("Maximum independent set: ");
    for (int i = 0; i < V; i++) {
        printf("%d ", independent_set[i]);
    }
    printf("\n");

    // Free memory
    for (int i = 0; i < V; i++) {
        free(graph);
    }
}