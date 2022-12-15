#include "library.h"

int main() {
    int task = 0;
    while (1) {
        menu();
        getIntForTask(&task);
        void (*tasks[4])() = {task1, task2, task3, stopProgram};
        tasks[task - 1]();
    }
}
