#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

struct Deque {
    int data[MAX_SIZE];
    int front;
    int rear;
    int size;
};

int isFull(struct Deque *deque) {
    return deque->size == MAX_SIZE;
}

int isEmpty(struct Deque *deque) {
    return deque->size == 0;
}

void push_front(struct Deque *deque, int item) {
    if (isFull(deque)) {
        printf("Deque overflow");
        return;
    }
    deque->data[--deque->front] = item;
    deque->size++;
}

void push_back(struct Deque *deque, int item) {
    if (isFull(deque)) {
        printf("Deque overflow");
        return;
    }
    deque->data[++deque->rear] = item;
    deque->size++;
}

int pop_front(struct Deque *deque) {
    if (isEmpty(deque)) {
        printf("Deque underflow");
        return -1;
    }
    int item = deque->data[deque->front++];
    deque->size--;
    return item;
}

int pop_back(struct Deque *deque) {
    if (isEmpty(deque)) {
        printf("Deque underflow");
        return -1;
    }
    int item = deque->data[deque->rear--];
    deque->size--;
    return item;
}

int main() {
    struct Deque deque = { {0}, MAX_SIZE, -1, 0 };

    push_back(&deque, 1);
    push_back(&deque, 2);
    push_front(&deque, 3);
    push_front(&deque, 4);

    printf("%d\n", pop_back(&deque)); // 2
    printf("%d\n", pop_back(&deque)); // 1

    return 0;
}