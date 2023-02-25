#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 20 // число студентов

int A[N][N] = { /* Матрица знакомств */ };

int team1[N], team2[N]; // массивы для хранения номеров студентов в командах
int size1, size2; // текущие размеры команд

bool visited[N]; // массив для хранения информации о посещении студентов

/* Рекурсивная функция для обхода в глубину */
void dfs(int u, int team[], int *size, int max_size) {
    visited[u] = true;
    team[(*size)++] = u;

    /* Обходим всех соседей студента u */
    for (int v = 0; v < N; v++) {
        if (A[u][v] && !visited[v] && *size <= max_size) {
            dfs(v, team, size, max_size);
        }
    }
}

/* Функция для поиска максимально связной группы студентов */
int find_max_connected(int team[], int *size, int max_size) {
    int max_connected = 0;
    int max_connected_size = 0;

    for (int i = 0; i < N; i++) {
        if (!visited[i] && *size <= max_size) {
            *size = 0;
            dfs(i, team, size, max_size);
            if (*size > max_connected_size) {
                max_connected_size = *size;
                max_connected = i;
            }
        }
    }

    return max_connected;
}

/* Главная функция */
int main() {
    size1 = size2 = 0;

    /* Пока есть непосещенные студенты */
    while (size1 + size2 < N) {
        int max_connected = find_max_connected(
                size1 <= size2 ? team1 : team2, // выбираем команду, в которую добавляем студентов
                size1 <= size2 ? &size1 : &size2,
                size1 <= size2 ? size2/2 + 1 : size1/2 + 1 // максимальный размер команды
        );

        /* Добавляем максимально связную группу студентов в выбранную команду */
        for (int i = 0; i < size1 + size2; i++) {
            if (team1[i] == max_connected) {
                printf("%d ", max_connected);
                break;
            } else if (team2[i] == max_connected) {
                printf("%d ", max_connected);
                break;
            }
        }
    }

    return 0;
}