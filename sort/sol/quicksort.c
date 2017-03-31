#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int t = *b;
    *b = *a;
    *a = t;
}

int partition(int* arr, int begin, int end) {
    int pivot_position = (end+begin)/2;
    swap(&arr[begin], &arr[pivot_position]);
    pivot_position = begin;
    int i;
    for (i=begin+1; i<end; i++) {
        if (arr[i] < arr[pivot_position]) {
            swap(&arr[i], &arr[pivot_position]);
            pivot_position++;
            swap(&arr[i], &arr[pivot_position]);
        }
    }
    return pivot_position;
}

void quicksort(int* arr, int begin, int end) {
    if (end - begin <= 1) return;
    int pivot_position = partition(arr, begin, end);
    quicksort(arr, begin, pivot_position);
    quicksort(arr, pivot_position+1, end);
}

int main() {
    int num;
    int* data;
    scanf("%d", &num);
    data = malloc(sizeof(int) * num);
    int i;
    for (i=0; i<num; i++) {
        scanf("%d", &data[i]);
    }
    quicksort(data, 0, num);
    for (i=0; i<num; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    return 0;
}
