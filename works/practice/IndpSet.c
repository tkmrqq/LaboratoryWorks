#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100  // максимальное количество вершин в графе

int graph[MAX_VERTICES][MAX_VERTICES];  // матрица смежности графа
int visited[MAX_VERTICES];  // массив для отслеживания посещенных вершин
int mis[MAX_VERTICES];  // массив для хранения максимального независимого множества
int mis_size = 0;  // размер максимального независимого множества

int main() {
    system("chcp 65001");
    int num_vertices, num_edges;
    printf("Введите количество вершин и ребер графа: ");
    scanf_s("%d %d", &num_vertices, &num_edges);

    // Инициализация матрицы смежности графа
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            graph[i][j] = 0;
        }
    }

    // Ввод ребер графа
    for (int i = 0; i < num_edges; i++) {
        int u, v;
        printf("Введите ребро %d: ", i+1);
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;  // если граф неориентированный
    }

    // Инициализация массива посещенных вершин
    for (int i = 0; i < num_vertices; i++) {
        visited[i] = 0;
    }

    // Инициализация максимального независимого множества
    for (int i = 0; i < num_vertices; i++) {
        mis[i] = -1;
    }

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

    // Выводим максимальное независимое множество
    printf("Максимальное независимое множество: ");
    for (int i = 0; i < mis_size; i++) {
        printf("%d ", mis[i]);
    }
    printf("\n");

    return 0;
}
