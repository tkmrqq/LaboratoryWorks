void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(int *a, int n) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n - 1; i++)
            // сравниваем элемент со следующим
            if (a[i] > a[i + 1])
                // меняем местами, если следующий меньше
                swap(&a[i], &a[i + 1]);
}

void selection_sort(int *a, int n) {
    for (int k = 0; k < n - 1; k++)
        for (int j = k + 1; j < n; j++)
            if (a[k] > a[j])
                swap(&a[j], &a[k]);
}

void insertion_sort(int *a, int n) {
    for (int k = 1; k < n; k++)
        for (int i = k; i > 0 && a[i - 1] < a[i]; i--)
            // мы ещё не дошли до начала массива и предыдущий элемент меньше
            swap(&a[i], &a[i - 1]);
}

void shell_sort(int *array, int size) {
    for (int s = size / 2; s > 0; s /= 2) {
        for (int i = s; i < size; ++i) {
            for (int j = i - s; j >= 0 && array[j] > array[j + s]; j -= s) {
                int temp = array[j];
                array[j] = array[j + s];
                array[j + s] = temp;
            }
        }
    }
}