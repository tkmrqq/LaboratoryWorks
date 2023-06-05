#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100// максимальное количество вершин в графе



void printGraph(int mis_size, int *mis) {
    // Выводим максимальное независимое множество
    printf("Maximum independent set: ");
    for (int i = 0; i < mis_size - 1; i++) {
        printf("%d ", mis[i]);
    }
    printf("\n");
}

void menu(int mis_size, int *mis){
    int x;
    printf("Are you want to print arrays, that consist graphs?(1-Yes 0-No)");
    scanf_s("%d", &x);
    if (x == 1){
        printGraph(mis_size, mis);
    }
    else
        return;
}

void MIS(int mis_size, int num_vertices, int *visited, int *mis, int graph[MAX_VERTICES][MAX_VERTICES]) {
    // Находим максимальное независимое множество
    while (mis_size < num_vertices) {
        int v;
        for (v = 0; v < num_vertices; v++) {
            if (!visited[v]) {
                break;
            }
        }

        // Добавляем вершину в максимальное независимое множество
        mis[mis_size++] = v;
        visited[v] = 1;

        // Удаляем вершину и ее соседей
        for (int i = 0; i < num_vertices; i++) {
            if (graph[v][i]) {
                visited[i] = 1;
            }
        }
    }
    printGraph(mis_size, mis);
}

void initialization(int num_vertices, int graph[MAX_VERTICES][MAX_VERTICES], int *visited, int *mis) {

    // Инициализация матрицы смежности графа
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            graph[i][j] = 0;
        }
    }

    // Инициализация массива посещенных вершин
    for (int i = 0; i < num_vertices; i++) {
        visited[i] = 0;
    }

    // Инициализация максимального независимого множества
    for (int i = 0; i < num_vertices; i++) {
        mis[i] = -1;
    }

}

void printAll(int num_vertices, int graph[MAX_VERTICES][MAX_VERTICES], int *visited, int *mis){

    int x;
    printf("What you want to print?\n1)Matrix\n2)Visited vertices\n3)MIS");

    scanf_s("%d", &x);

    switch (x) {
        case 1:{
            printf("\ngraph:\n");
            for (int i = 0; i < num_vertices; i++) {
                for (int j = 0; j < num_vertices; j++) {
                    printf("%d ", graph[i][j]);
                }
                printf("\n");
            }
            break;
        }
        case 2:{
            printf("\nVisited:\n");
            // Инициализация массива посещенных вершин
            for (int i = 0; i < num_vertices; i++) {
                printf("%d ", visited[i]);
            }
            break;
        }
        case 3:{
            printf("\nMIS:\n");
            // Инициализация максимального независимого множества
            for (int i = 0; i < num_vertices; i++) {
                printf("%d ", mis[i]);
            }
            break;
        }
        default:{
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    int graph[MAX_VERTICES][MAX_VERTICES];// матрица смежности графа
    int visited[MAX_VERTICES];            // массив для отслеживания посещенных вершин
    int mis[MAX_VERTICES];                // массив для хранения максимального независимого множества
    int mis_size = 0;                     // размер максимального независимого множества

    int num_vertices, num_edges;
    printf("Enter the number of vertices:");
    scanf_s("%d %d", &num_vertices);
    printf("Enter the number of edges:");
    scanf_s("%d %d", &num_edges);

    initialization(num_vertices, graph, visited, mis);
    printAll(num_vertices, graph, visited, mis);
    // Ввод ребер графаpip install networkx matplotlib

    for (int i = 0; i < num_edges; i++) {
        int u, v;
        printf("Enter the edges (vertex pairs) [%d]: ", i + 1);
        scanf_s("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;// если граф неориентированный
    }

    MIS(mis_size, num_vertices, visited, mis, graph);

    printf("Processed:\n");
    menu(mis_size, mis);

    return 0;
}
