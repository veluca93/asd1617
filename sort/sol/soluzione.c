#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

void insertionsort(int* arr, int begin, int end) {
    int i, j;
    for (i=begin+1; i<end; i++) {
        for (j=i-1; j>=begin; j--) {
            if (arr[j] > arr[j+1]) swap(&arr[j], &arr[j+1]);
            else break;
        }
    }
}

void quicksort(int* arr, int begin, int end) {
    if (end - begin <= 1) return;
    if (end - begin <= 16) return insertionsort(arr, begin, end);
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
