#include <stdio.h>
#include <stdlib.h>

struct Graph {
    int V;
    int** adj;
};

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = vertices;
    graph->adj = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adj[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->adj[i][j] = 0;
        }
    }
    return graph;
}

void addEdge(struct Graph* graph, int u, int v) {
    graph->adj[u][v] = 1;
    graph->adj[v][u] = 1;
}

int isSafe(struct Graph* graph, int v, int* color, int* result) {
    for (int i = 0; i < graph->V; i++) {
        if (graph->adj[v][i] && result[i] == *color) {
            return 0;
        }
    }
    return 1;
}

void maxIndependentSetUtil(struct Graph* graph, int* result, int current, int* max_count, int** max_set) {
    if (current == graph->V) {
        int count = 0;
        for (int i = 0; i < graph->V; i++) {
            if (result[i] == 1) {
                count++;
            }
        }
        *max_count = count;
        *max_set = (int*)malloc(count * sizeof(int));
        int index = 0;
        for (int i = 0; i < graph->V; i++) {
            if (result[i] == 1) {
                (*max_set)[index++] = i;
            }
        }
        return;
    }

    for (int color = 0; color <= 1; color++) {
        if (isSafe(graph, current, &color, result)) {
            result[current] = color;
            maxIndependentSetUtil(graph, result, current + 1, max_count, max_set);
            result[current] = -1;
        }
    }
}

int* maxIndependentSet(struct Graph* graph, int* max_count) {
    int* result = (int*)malloc(graph->V * sizeof(int));
    int* max_set;
    maxIndependentSetUtil(graph, result, 0, max_count, &max_set);
    return max_set;
}

int validateInput(int n, int** edges, int E) {
    if (n <= 0) {
        return 0;
    }
    for (int i = 0; i < E; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        if (u < 0 || u >= n || v < 0 || v >= n) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    int** edges = (int**)malloc(E * sizeof(int*));
    printf("Enter the edges (vertex pairs):\n");
    for (int i = 0; i < E; i++) {
        edges[i] = (int*)malloc(2 * sizeof(int));
        scanf("%d %d", &edges[i][0], &edges[i][1]);
    }

    if (!validateInput(V, edges, E)) {
        printf("Invalid input. Please try again.\n");
        return 0;
    }

    struct Graph* g = createGraph(V);

    for (int i = 0; i < E; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        addEdge(g, u, v);
    }

    int max_count;
    int* max_set = maxIndependentSet(g, &max_count);

    printf("Maximum Independent Set Size: %d\n", max_count);
    printf("Maximum Independent Set: ");
    for (int i = 0; i < max_count; i++) {
        printf("%d ", max_set[i]);
    }
    printf("\n");

    free(max_set);
    for (int i = 0; i < E; i++) {
        free(edges[i]);
    }
    free(edges);
    for (int i = 0; i < V; i++) {
        free(g->adj[i]);
    }
    free(g->adj);
    free(g);

    return 0;
}
