#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int t = *b;
    *b = *a;
    *a = t;
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

int main() {
    int num;
    int* data;
    scanf("%d", &num);
    data = malloc(sizeof(int) * num);
    int i;
    for (i=0; i<num; i++) {
        scanf("%d", &data[i]);
    }
    insertionsort(data, 0, num);
    for (i=0; i<num; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    return 0;
}
