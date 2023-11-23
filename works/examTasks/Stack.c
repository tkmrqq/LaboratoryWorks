#include <stdio.h>
#include <stdlib.h>

#define NMAX 10

typedef struct Stack {
    int elem[NMAX];
    int top;
} stack;

void push(stack *stk, int k) {
    if (stk->top < NMAX) {
        stk->elem[stk->top] = k;
        stk->top++;
    } else
        printf("Stack overflow!");
}

int isEmpty(stack *stk) {
    if (stk->top == 0) return 1;
    else
        return 0;
}

void print(stack *stk) {
    int i = stk->top;
    if(isEmpty(stk) == 1) return;
    do {
        i--;
        printf("%d ", stk->elem[i]);
    } while (i>0);
}

int main() {
    stack* stk = (stack*)malloc(NMAX*sizeof(stack));
    int k;
    for (int i = 0; i < NMAX; ++i) {
        printf("Input elem:");
        scanf_s("%d", &k);
        push(stk, k);
    }
    print(stk);
}