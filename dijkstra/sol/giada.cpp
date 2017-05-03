/*
 * Soluzione di mincammino
 * 
 * Autore: Giada Franz
 * 
 */

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

const int MAXN = 1000000;
const int INF = 1000000000;

vector < pair <int,int> > aa[MAXN];
int dist[MAXN];
bool fatto[MAXN];


int mincammino(int N, int M, int X[], int Y[], int P[]) {
    for (int i = 0; i < M; i++) {
        aa[X[i]].push_back(make_pair(Y[i], P[i]));
    }
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        fatto[i] = false;
    }
    
    priority_queue < pair <int, int> > coda;
    coda.push(make_pair(0, 0));
    dist[0] = 0;
    
    while (!coda.empty()) {
        int v = coda.top().second;
        int d = -coda.top().first;
        //~ cout << v << " " << d << endl;
        coda.pop();
        if (!fatto[v]) {
            fatto[v] = true;
            for (pair <int, int> arco : aa[v]) {
                int a = arco.first;
                int p = arco.second;
                if (!fatto[a] and d+p < dist[a]) {
                    dist[a] = d+p;
                    coda.push(make_pair(-dist[a], a));
                }
            }
        }
    }
    return (dist[N-1] == INF)?-1 : dist[N-1];
}
#include <cstdio>
#include <cassert>
#include <cstdlib>

static FILE *fr, *fw;

// Declaring variables
static int N;
static int M;
static int* X;
static int* Y;
static int* P;
static int res;

// Declaring functions
int mincammino(int N, int M, int X[], int Y[], int P[]);

int main() {
	fr = stdin;
	fw = stdout;

	// Reading input
	fscanf(fr, " %d %d", &N, &M);
	X = (int*)malloc((M) * sizeof(int));
	Y = (int*)malloc((M) * sizeof(int));
	P = (int*)malloc((M) * sizeof(int));
	for (int i0 = 0; i0 < M; i0++) {
		fscanf(fr, " %d %d %d", &X[i0], &Y[i0], &P[i0]);
	}

	// Calling functions
	res = mincammino(N, M, X, Y, P);

	// Writing output
	fprintf(fw, "%d\n", res);

	fclose(fr);
	fclose(fw);
	return 0;
}
