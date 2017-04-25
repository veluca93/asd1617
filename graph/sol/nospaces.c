#include <stdio.h>
#include <stdlib.h>

int int_cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    int* from = malloc(sizeof(int)*M);
    int* to = malloc(sizeof(int)*M);
    int* indegree = calloc(N, sizeof(int));
    int* outdegree = calloc(N, sizeof(int));
    int* inpos = calloc(N, sizeof(int));
    int* outpos = calloc(N, sizeof(int));
    int** inedges = malloc(sizeof(int*)*N);
    int** outedges = malloc(sizeof(int*)*N);
    int i, j;
    for (i=0; i<M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        from[i] = a;
        to[i] = b;
        outdegree[a]++;
        indegree[b]++;
    }
    for (i=0; i<N; i++) {
        inedges[i] = malloc(sizeof(int)*indegree[i]);
        outedges[i] = malloc(sizeof(int)*outdegree[i]);
    }
    for (i=0; i<M; i++) {
        int a = from[i];
        int b = to[i];
        inedges[b][inpos[b]++] = a;
        outedges[a][outpos[a]++] = b;
    }
    free(inpos);
    free(outpos);
    free(from);
    free(to);
    for (i=0; i<N; i++) {
        qsort(inedges[i], indegree[i], sizeof(int), int_cmp);
        qsort(outedges[i], outdegree[i], sizeof(int), int_cmp);
    }
    for (i=0; i<N; i++) {
        for (j=0; j<indegree[i]; j++) {
            if (j + 1 != indegree[i]) printf("%d ", inedges[i][j]);
            else printf("%d", inedges[i][j]);
        }
        printf("\n");
    }
}
