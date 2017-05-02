#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int bfs(int** edges, int* degree, int N, int start) {
    int* distance = malloc(sizeof(int)*N);
    int* queue = malloc(sizeof(int)*N);
    int q_start = 0;
    int q_end = 0;
    for (int i=0; i<N; i++) distance[i] = 2*N;
    distance[start] = 0;
    queue[q_end++] = start;
    int maxdist = 0;
    while (q_start != q_end) {
        int cur = queue[q_start++];
        maxdist = distance[cur]; // distance is increasing
        int i;
        for (i=0; i<degree[cur]; i++) {
            if (distance[edges[cur][i]] != 2*N) continue;
            distance[edges[cur][i]] = distance[cur] + 1;
            queue[q_end++] = edges[cur][i];
        }
    }
    assert(q_start == N);
    free(distance);
    free(queue);
    return maxdist;
}

int int_cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    int* from = malloc(sizeof(int)*M);
    int* to = malloc(sizeof(int)*M);
    int* degree = calloc(N, sizeof(int));
    int* pos = calloc(N, sizeof(int));
    int** edges = malloc(sizeof(int*)*N);
    int i, j;
    for (i=0; i<M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        from[i] = a;
        to[i] = b;
        degree[a]++;
        degree[b]++;
    }
    for (i=0; i<N; i++) {
        edges[i] = malloc(sizeof(int)*degree[i]);
    }
    for (i=0; i<M; i++) {
        int a = from[i];
        int b = to[i];
        edges[b][pos[b]++] = a;
        edges[a][pos[a]++] = b;
    }
    free(pos);
    free(from);
    free(to);
    for (i=0; i<N; i++) {
        qsort(edges[i], degree[i], sizeof(int), int_cmp);
    }
    int diam = 0;
    for (i=0; i<N; i++) {
        int dst = bfs(edges, degree, N, i);
        if (dst > diam) diam = dst;
    }
    printf("%d\n", diam);
}
