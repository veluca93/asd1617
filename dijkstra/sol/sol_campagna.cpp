#include <iostream>
#include <fstream>
#include <queue>
#include <iterator>
#include <stack>
#include <cassert>
using namespace std;

const int MAX_N = 1000000;
const int MAX_M = 1000000;

//~ #ifdef EVAL
//~ ifstream in("input.txt");
//~ ofstream out("output.txt");
//~ #else
//~ istream &in(cin);
//~ ostream &out(cout);
//~ #endif


int N, M;
vector<int> distanza;
vector<int> padre;

vector<vector<pair<int,int> > > lista_vicini;

//~ inline int nextInt(){
    //~ char c;
    //~ int xx,yy,cnt;
	//~ xx = 0;
	//~ while (!isdigit(c = getchar_unlocked()));
	//~ do{
		//~ xx = xx * 10 + c - '0';
		//~ c = getchar_unlocked();
	//~ }
	//~ while (isdigit(c));
	//~ return xx;
//~ }

int mincammino(int N, int M, int X[], int Y[], int P[]) {
    ::N = N;
    ::M = M;
    
    distanza.resize(N, -1);
    padre.resize(N, -1);
    lista_vicini.resize(N);
    
    for (int i=0; i < M; ++i) {
        lista_vicini[X[i]].push_back(make_pair(Y[i], P[i]));
    }
    
    int start = 0;
    
  priority_queue<pair<int, pair<int, int> > > coda;

  coda.push(make_pair(0, make_pair(start, -1)));

  while(!coda.empty()) {
    const pair<int, pair<int, int> >& e(coda.top());
    int dist = -e.first;
    int nodo = e.second.first;
    int from = e.second.second;
    if (distanza[nodo] != -1) {
      coda.pop();
      continue;
    }

    distanza[nodo] = dist;
    padre[nodo] = from;

    const vector<pair<int, int> >& vicini(lista_vicini[nodo]);
    for (vector<pair<int, int> >::const_iterator i(vicini.begin()); i != vicini.end(); ++i) {
      int vicino = i->first;
      int peso = i->second;
      if (vicino != from) // per grafi non diretti, ma fa cmq comodo
        if(distanza[vicino] == -1)
    	  coda.push(make_pair(-(dist + peso), make_pair(vicino, nodo)));
    }

    coda.pop();
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
