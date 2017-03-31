#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
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
    qsort(data, num, sizeof(int), cmp);
    for (i=0; i<num; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    return 0;
}
