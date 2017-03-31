#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int* data = malloc(sizeof(int)*n);
    for (int i=0; i<n; i++) {
        scanf("%d", &data[i]);
    }
    int cursum = 0;
    for (int i=0; i<n; i++) {
        cursum += data[i];
    }
    printf("%d\n", cursum);
}

