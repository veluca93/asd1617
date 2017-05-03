#include <iostream>
#include <fstream>
#include <queue>
#include <iterator>
#include <stack>
#include <algorithm>
#include <cassert>
using namespace std;

const int MAX_N = 1000000;
const int MAX_M = 1000000;


int N, M;
vector<int> distanza;
vector<int> padre;

vector<vector<pair<int,int> > > lista_vicini;

template<class T>
class radix_heap{
    vector<pair<int, T> > buckets[33];
    int minidx[33];
    int last_deleted;
    int nel;
    inline void ins(int v, T w){
        if(v == last_deleted)
            buckets[0].push_back(make_pair(v, w));
        else{
            int b = 32-__builtin_clz(v^last_deleted);
            if(minidx[b] == -1) minidx[b] = 0;
            else if(buckets[b][minidx[b]].first > v) minidx[b] = buckets[b].size();
            buckets[b].push_back(make_pair(v, w));
        }
    }
    public:
    radix_heap(): last_deleted(-2147483648), nel(0) {
        for(int i=0; i<33; i++) minidx[i] = -1;
    }
    pair<int, T> pop() {
        nel--;
        int b = 0;
        while(buckets[b].empty()) b++;
        if(b==0){
            pair<int, T> r = buckets[0][buckets[0].size()-1];
            buckets[0].resize(buckets[0].size()-1);
            return r;
        }
        int m = minidx[b];
        last_deleted = buckets[b][m].first;
        pair<int, T> r = buckets[b][m];
        for(unsigned i=0; i<buckets[b].size(); i++)
            if(i != m)
                ins(buckets[b][i].first, buckets[b][i].second);
        buckets[b].resize(0);
        minidx[b] = -1;
        return r;
    }
    inline void push(pair<int, T> v){
        nel++;
        ins(v.first, v.second);
    }
    inline bool empty(){
        return !nel;
    }
};

int mincammino(int N, int M, int X[], int Y[], int P[]) {
    ::N = N;
    ::M = M;
    
    distanza.resize(N, -1);
    padre.resize(N, -1);
    lista_vicini.resize(N);
    for (int i(0); i < M; ++i) {
        lista_vicini[X[i]].push_back(make_pair(Y[i], P[i]));
    }
    
    int start = 0;
    
  radix_heap<pair<int, int> > coda;

  coda.push(make_pair(0, make_pair(start, -1)));

  while(!coda.empty()) {
    pair<int, pair<int, int> > e = coda.pop();
    int dist = e.first;
    int nodo = e.second.first;
    int from = e.second.second;
    if (distanza[nodo] != -1)
      continue;

    distanza[nodo] = dist;
    padre[nodo] = from;

    const vector<pair<int, int> >& vicini(lista_vicini[nodo]);
    for (vector<pair<int, int> >::const_iterator i(vicini.begin()); i != vicini.end(); ++i) {
      int vicino = i->first;
      int peso = i->second;
      if (vicino != from) // per grafi non diretti, ma fa cmq comodo
        if(distanza[vicino] == -1)
	      coda.push(make_pair(dist + peso, make_pair(vicino, nodo)));
    }
  }
  return distanza[N-1];
}

#include <cstdio>
#include <cassert>
#include <cstdlib>

static FILE *fr, *fw;

// Declaring variables
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
