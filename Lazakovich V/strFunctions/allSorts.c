void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(int *a, int n) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n - 1; i++)
            if (a[i] > a[i + 1])
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

void qsortRecursive(int *mas, int size) {
    int i = 0;
    int j = size - 1;
    int mid = mas[size / 2];
    do {
        while(mas[i] < mid) {
            i++;
        }
        while(mas[j] > mid) {
            j--;
        }
        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);

    if(j > 0) {
        qsortRecursive(mas, j + 1);
    }
    if (i < size) {
        qsortRecursive(&mas[i], size - i);
    }
}