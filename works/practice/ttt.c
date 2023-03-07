#include <stdio.h>
//#include <stdlib.h>
#include <stdbool.h>

#define MAXV 100 // maximum number of vertices in the graph

typedef struct {
    int v[MAXV+1][MAXV+1]; // adjacency matrix
    int nvertices; // number of vertices in the graph
} Graph;

bool is_independent_set(Graph g, const int *set, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            if (g.v[set[i]][set[j]] == 1) {
                return false;
            }
        }
    }
    return true;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int max_independent_set(Graph g, int *set, int size, int index, int max_size) {
    if (index >= g.nvertices) {
        if (is_independent_set(g, set, size)) {
            return max(size, max_size);
        } else {
            return max_size;
        }
    }
    int new_set[size+1];
    for (int i = 0; i < size; i++) {
        new_set[i] = set[i];
    }
    new_set[size] = index;
    return max(max_independent_set(g, set, size, index+1, max_size),
               max_independent_set(g, new_set, size+1, index+1, max_size));
}

int main() {
    Graph g = {{{0}}};
    int n, m; // number of vertices and edges
    scanf_s("%d %d", &n, &m);
    g.nvertices = n;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf_s("%d %d", &u, &v);
        g.v[u][v] = g.v[v][u] = 1;
    }
    int set[MAXV];
    printf("Maximum independent set size: %d\n", max_independent_set(g, set, 0, 0, 0));
    return 0;
}
