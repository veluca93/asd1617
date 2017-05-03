#include "graph.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " N M [S]" << endl;
        return -1;
    }
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int S = argc < 4 ? 0 : atoi(argv[3]); 
    Random::srand(S);

    Graph::Graph<Graph::Directed> g(N);
    g.add_edges(M, "rnd");
    g.shuffle();
    std::cout << N << " " << M << std::endl;
    for (auto edg: g) {
        std::cout << edg << " " << Random::randint(999)+1 << std::endl;
    }
}
