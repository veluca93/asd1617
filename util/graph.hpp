#ifndef _Graph_HPP_
#define _Graph_HPP_
#include <vector>
#include <string>
#include <stdint.h>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <iostream>
using namespace std;

namespace Random {

    uint64_t x = 8867512362436069LL;
    uint64_t w;

    /**
     *  Simple 64-bit variant of the XorShift random number algorithm.
     */
    inline uint64_t xor128() {
        uint64_t t;
        t = x ^ (x << 11);
        x = w;
        return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
    }


    /**
     *  Random functions seed.
     *
     *  @param S seed
     */
    void srand(int S) {
        w = S;
    }

    /**
     *  Returns a random integer in the range [0, N).
     *
     *  @param N the maximum number to return
     */
    inline uint64_t randint(uint64_t N) {
        return xor128() % N;
    }

    /**
     *  Returns K distinct random integers in the range [0, N).
     *  Assumes K <= N
     *
     *  @param K the number of integers to return.
     *  @param N the maxium number to return
     */
    vector<uint64_t> randints(uint64_t K, uint64_t N){
        vector<uint64_t> r;
        for(unsigned i=0; i<K; i++) r.push_back(randint(N-K+1));
        sort(r.begin(), r.end());
        for(unsigned i=0; i<K; i++) r[i] += i;
        return r;
    }
}

namespace SpeedHacks {
    const char digit_pairs[201] = {
      "00010203040506070809"
      "10111213141516171819"
      "20212223242526272829"
      "30313233343536373839"
      "40414243444546474849"
      "50515253545556575859"
      "60616263646566676869"
      "70717273747576777879"
      "80818283848586878889"
      "90919293949596979899"
    };

    /**
     *  Dirty (but fast!) way to write a integer in a string. It cuts the time
     *  to print ~4 million integers from ~0.3s (with stringstream) to 0.1s.
     *
     *  Note: it probably won't work on ARM systems.
     *
     *  @param n the integer to write
     *  @param c pointer to the beginning of the string
     */
    char* itos(int n, char* c) {
        if(n==0) {
            *c = '0';
            return c+1;
        }

        int sign = -(n<0);
        unsigned int val = (n^sign)-sign;

        int size;
        if(val>=10000) {
            if(val>=10000000) {
                if(val>=1000000000) size=10;
                else if(val>=100000000) size=9;
                else size=8;
            } else {
                if(val>=1000000) size=7;
                else if(val>=100000) size=6;
                else size=5;
            }
        }
        else {
            if(val>=100) {
                if(val>=1000) size=4;
                else size=3;
            } else {
                if(val>=10) size=2;
                else size=1;
            }
        }
        size -= sign;
        if(sign) *c='-';
        c += size-1;
        while(val>=100) {
           int pos = val % 100;
           val /= 100;
           *(short*)(c-1)=*(short*)(digit_pairs+2*pos); 
           c-=2;
        }
        while(val>0) {
            *c--='0' + (val % 10);
            val /= 10;
        }
        return c + size + 1;
    }
}

namespace Graph {

    /**
     *  Class that implements a Disjoint Set Union data structure.
     */
    class DSU {
    public:

        vector<int> dad;
        vector<int> rank;

        /**
         *  Creates N disjoint sets.
         *
         *  @param N the number of sets to create
         */
        DSU(int N) {
            dad.resize(N);
            rank.resize(N);
            for(int i=0; i<N; i++) dad[i] = i;
        }

        /**
         *  Finds the representative of x.
         *
         *  @param x what to find the representative of
         */
        inline int find(int x) {
            if (x == dad[x]) return x;
            return dad[x] = find(dad[x]);
        }

        /**
         *  Merges the set that contains x with the one that contains y
         *
         *  @param x an element in one of the sets to merge
         *  @param y an element in one of the sets to merge
         */
        inline void join(int x, int y) {
            int rx = find(x);
            int ry = find(y);
            if (rx == ry) return;
            if (rank[rx] < rank[ry]) {
                dad[rx] = ry;
                rank[ry] += rank[rx];
            } else {
                dad[ry] = rx;
                rank[rx] += rank[ry];
            }
        }
    };


    /**
     *  Template class for a graph. It takes a class that represents an edge
     *  type as a template parameter. See EdgeType, Undirected, Directed and 
     *  DAG.
     *
     *  @tparam T type of the graph.
     */
    template<class Edge>
    class Graph {
        unordered_set<Edge> edges;
        vector<int> labels;
        int vertices;

    public:

        /**
         *  Builds a graph with N nodes, labeled from 0 to N-1, and no edges.
         *
         *  @param N number of edges
         */
        Graph<Edge>(int N): vertices(N) {
            for(unsigned i=0; i<N; i++) labels.push_back(i);
        }

        /**
         *  Builds a graph from a given number of vertices and a given vector
         *  of edges.
         *
         *  @param V number of vertices
         *  @param E vector that contains the edges
         */
        Graph<Edge>(const int& V, const vector<Edge>& E) {
            vertices = V;
            insert_edges(E);
        }

        /**
         *  Builds a graph from a given number of vertices and given labels.
         *
         *  @param lbl the labels of the vertices
         *  @param E vector that contains the edges
         */
        Graph<Edge>(const vector<int>& lbl, const vector<Edge>& E) {
            vertices = lbl.size();
            labels = lbl;
            insert_edges(E);
        }

        /**
         *  Disjoint union with another graph.
         *
         *  @param other
         */
        Graph<Edge>& operator+=(const Graph<Edge>& other) {
            vector<Edge> tmp;
            for(auto e: other.edges) {
                pair<int, int> p = e;
                p.first = other.labels[p.first] + vertices;
                p.second = other.labels[p.second] + vertices;
                tmp.push_back(Edge(p));
            }
            vertices += other.vertices;
            for(unsigned i=0; i<other.vertices; i++) {
                labels.push_back(other.labels[i]);
            }
            insert_edges(tmp);
            return *this;
        }

        /**
         *  Cartesian product with another graph. Not yet implemented.
         *
         *  @param other
         */
        Graph<Edge>& operator*=(const Graph<Edge>& other) {
            return *this;
        }

        /**
         *  Union with another graph. Assumes that the graphs have the same
         *  number of vertices.
         *
         *  @param other
         */
        Graph<Edge>& operator|=(const Graph<Edge>& other) {
            vector<Edge> tmp;
            tmp.resize(other.edges.size() + edges.size());
            auto it = set_union(edges.begin(), edges.end(),
                                other.edges.begin(), other.edges.end(),
                                tmp.begin());
            replace_edges(tmp.begin(), it);
            return *this;
        }

        /**
         *  Intersection with another graph. Assumes that the graphs have the
         *  same number of vertices.
         *
         *  @param other
         */
        Graph<Edge>& operator&=(const Graph<Edge>& other) {
            vector<Edge> tmp;
            tmp.resize(other.edges.size() + edges.size());
            auto it = set_intersection(edges.begin(), edges.end(),
                                       other.edges.begin(), other.edges.end(),
                                       tmp.begin());
            replace_edges(tmp.begin(), it);
            return *this;
        }

        /**
         *  Subtraction of another graph. Assumes that the graphs have the same
         *  number of vertices.
         *
         *  @param other
         */
        Graph<Edge>& operator-=(const Graph<Edge>& other) {
            vector<Edge> tmp;
            tmp.resize(other.edges.size() + edges.size());
            auto it = set_difference(edges.begin(), edges.end(),
                                     other.edges.begin(), other.edges.end(),
                                     tmp.begin());
            replace_edges(tmp.begin(), it);
            return *this;
        }

        /**
         *  Symmetric difference with another graph. Assumes that the graphs
         *  have the same number of vertices.
         *
         *  @param other
         */
        Graph<Edge>& operator^=(const Graph<Edge>& other) {
            vector<Edge> tmp;
            tmp.resize(other.edges.size() + edges.size());
            auto it = set_symmetric_difference(edges.begin(),
                                               edges.end(),
                                               other.edges.begin(),
                                               other.edges.end(),
                                               tmp.begin());
            replace_edges(tmp.begin(), it);
            return *this;
        }

        /**
         *  Disjoint union of two graphs. Assumes that the first graph's labels
         *  are consecutive integers starting from 0, and the second graph's
         *   labels are non-negative integers.
         *
         *  @param other
         */
        Graph<Edge> operator+(const Graph<Edge>& other) {
            Graph<Edge> tmp = *this;
            tmp += other;
            return tmp;
        }

        /**
         *  Cartesian product of two graphs. Not yet implemented.
         *
         *  @param other
         */
        Graph<Edge> operator*(const Graph<Edge>& other) {
            Graph<Edge> tmp = *this;
            tmp *= other;
            return tmp;
        }

        /**
         *  Union of two graphs. Assumes that the graphs have the same number
         *  of vertices.
         *
         *  @param other
         */
        Graph<Edge> operator|(const Graph<Edge>& other) {
            Graph<Edge> tmp = *this;
            tmp |= other;
            return tmp;
        }

        /**
         *  Intersection of two graphs. Assumes that the graphs have the same
         *  number of vertices.
         *
         *  @param other
         */
        Graph<Edge> operator&(const Graph<Edge>& other) {
            Graph<Edge> tmp = *this;
            tmp &= other;
            return tmp;
        }

        /**
         *  Difference of two graphs. Assumes that the graphs have the same
         *  number of vertices.
         *
         *  @param other
         */
        Graph<Edge> operator-(const Graph<Edge>& other) {
            Graph<Edge> tmp = *this;
            tmp -= other;
            return tmp;
        }

        /**
         *  Symmetric difference of two graphs. Assumes that the graphs have
         *  the same number of vertices.
         *
         *  @param other
         */
        Graph<Edge> operator^(const Graph<Edge>& other) {
            Graph<Edge> tmp = *this;
            tmp ^= other;
            return tmp;
        }

        /**
         *  Complement of the graph.
         *
         *  @todo decide what should happen for directed graphs
         */
        Graph<Edge> operator-() {
            Graph<Edge> all(vertices);
            all.add_edges(0, "clique");
            all -= *this;
            return all;
        }

        /**
         *  Check if two graph are equal.
         *
         *  @param other
         */
        bool operator==(const Graph<Edge>& other) const {
            if(vertices != other.vertices) return false;
            auto me = edges.begin();
            auto ot = other.edges.begin();
            while (me != edges.end() && ot != other.edges.end()) {
                if (*me != *ot) return false;
                me++;
                ot++;
            }
            return true;
        }

        /**
         *  Check if two graph are different.
         *
         *  @param other
         */
        bool operator!=(const Graph<Edge>& other) const {
            return !(*this == other);
        }

        /**
         *  Check if this graph is a proper subset of the second one.
         *
         *  @param other
         */
        bool operator<(const Graph<Edge>& other) const {
            if(vertices != other.vertices) return false;
            return includes(other.edges.begin(), other.edges.end(),
                            edges.begin(), edges.end());
        }

        /**
         *  Check if this graph is a subset of the second one.
         *
         *  @param other
         */
        bool operator<=(const Graph<Edge>& other) const {
            return *this == other || *this < other;
        }

        /**
         *  Check if this graph is a proper superset of the second one.
         *
         *  @param other
         */
        bool operator>(const Graph<Edge>& other) const {
            return other < *this;
        }

        /**
         *  Check if this graph is a superset of the second one.
         *
         *  @param other
         */
        bool operator>=(const Graph<Edge>& other) const {
            return other <= *this;
        }

        /**
         *  Adds an edge, if it is not already present in the graph.
         *
         *  @param e the edge to add
         */
        void add_edge(Edge e) {
            edges.insert(e);
        }

        /**
         *  Removes an edge, if it is present in the graph.
         *
         *  @param e the edge to remove
         */
        void del_edge(Edge e) {
            edges.erase(e);
        }

        /**
         *  Check if an edge is present in the graph.
         *
         *  @param e the edge to check
         */
        bool has_edge(Edge e) {
            return edges.count(e);
        }

        /**
         *  Performs a permutation of the nodes of the graphs.
         *
         *  @param first first node to shuffle (default 0)
         *  @param last last node to shuffle (default -1, meaning last)
         */
        void shuffle(int first = 0, int last = -1) {
            random_shuffle(labels.begin() + first,
                           labels.begin() + (last==-1 ? vertices : last),
                           Random::randint);
        }

        /**
         *  Replaces the current edges of the graph with the new range.
         *
         *  @param start iterator to the first edge
         *  @param end iterator to the next-after-last edge
         */
        void replace_edges(typename vector<Edge>::iterator start,
                           typename vector<Edge>::iterator end) {
            unordered_set<Edge> new_edges(start, end);
            edges.swap(new_edges);
        }

        /**
         *  Inserts the given range of edges in the graph.
         *
         *  @param start iterator to the first edge
         *  @param end iterator to the next-after-last edge
         */
         void insert_edges(typename vector<Edge>::const_iterator start,
                           typename vector<Edge>::const_iterator end) {
            vector<Edge> tmp;
            tmp.resize(end - start + edges.size());
            auto it = set_union(edges.begin(), edges.end(),
                                start, end,
                                tmp.begin());
            replace_edges(tmp.begin(), it);
         }

        /**
         *  Inserts the given edges in the graph, in linear time.
         *
         *  @param edg vector of the (encoded) edges to add
         */
        void insert_edges(const vector<Edge>& edg) {
            insert_edges(edg.begin(), edg.end());
        }

        /**
         *  Adds m edges to the graph. If type is 'rnd', it generates m edges
         *  that aren't already in the graph and adds them. Otherwise, it
         *  generates the desired structure of the graph and adds the edges
         *  if they aren't already in the graph.
         *
         *  @param m the number of edges to add
         *  @param type one of rnd, cycle, path, tree, forest, clique, star
         *  @todo add wheel, gearcaterpillar, lobster
         */
        void add_edges(int m, string type = "rnd") {
            edges.reserve(m);
            if(type == "cycle") {
                for(int i=1; i<vertices; i++) {
                    edges.emplace(i-1, i);
                }
                edges.emplace(vertices-1, 0);
            } else if (type == "path") {
                for(int i=1; i<vertices; i++) {
                    edges.emplace(i-1, i);
                }
            } else if (type == "tree") {
                for(int i=1; i<vertices; i++) {
                    edges.emplace(Random::randint(i), i);
                }
            } else if (type == "forest") {
                if (m > vertices-1) m = vertices-1;
                for(auto i: Random::randints(m, vertices-1)) {
                    edges.emplace(Random::randint(i+1), i+1);
                }
            } else if (type == "clique") {
                for(int i=0; i<vertices; i++) {
                    for(int j=i+1; j<vertices; j++) {
                        edges.emplace(i, j);
                    }
                }
            } else if (type == "star") {
                for(int i=1; i<vertices; i++)
                    edges.emplace(0, i);
            } else {
                uint64_t big = Edge(vertices-1, vertices-1)+1;
                if(Edge(big) == big-1) big++;
                vector<Edge> forbidden;
                for(int i=0; i<vertices; i++) {
                    if(edges.count(Edge(i, i))) continue;
                    uint64_t x = Edge(i, i);
                    forbidden.push_back(Edge(x));
                    if(Edge(x+1) == x) forbidden.push_back(Edge(x+1));
                }
                for(auto e: edges) {
                    forbidden.push_back(e);
                }
                sort(forbidden.begin(), forbidden.end());
                uint64_t nfree = big - forbidden.size();
                if(nfree < m) m = nfree;
                vector<uint64_t> t = Random::randints(m, nfree);
                int skipped = 0;
                int cur = 0;
                for(auto used: forbidden) {
                    while(cur != t.size() && t[cur] + skipped < used) {
                        t[cur++] += skipped;
                    }
                    if(cur == t.size()) break;
                    if(t[cur] + skipped == used) skipped++;
                }
                for(auto e: t) {
                    edges.emplace(e);
                }
            }
        }

        /**
         *  Adds the minimum number of edges required to make the graph
         *  (weakly) connected.
         */
        void connect() {
            DSU u(vertices);
            for(auto e: edges) {
                pair<int, int> p = e;
                u.join(p.first, p.second);
            }
            int li = 0;
            for(int i=0; i<vertices; i++) {
                if(u.find(i) != u.find(li)) {
                    u.join(li, i);
                    edges.emplace(li, i);
                    li = i;
                }
            }
        }

        /**
         *  Generates a string representation of the graph, in the format that
         *  is most used at the Informatics Olympiads: first line contains the
         *  number of vertices and edges, and the following lines contain two
         *  integers a, b that represent an edge from a to b.
         *
         *  @param start the first number of a vertex
         */
        string to_string(int start = 0) const {
            // 22 is the maximum number of bytes that a pair of ints can take
            string s;
            s.resize(22 * (edges.size() + vertices + 1));
            char* c = &s[0];
            c = SpeedHacks::itos(vertices, c);
            *c++ = ' ';
            c = SpeedHacks::itos(edges.size(), c);
            *c++ = '\n';
            for(auto e: edges) {
                pair<int, int> p = e;
                c = SpeedHacks::itos(labels[p.first], c);
                *c++ = ' ';
                c = SpeedHacks::itos(labels[p.second], c);
                *c++ = '\n';
            }
            s.resize(c - &s[0] - 1);
            return s;
        }

        typedef typename unordered_set<Edge>::const_iterator iterator;

        /**
         *  Returns edges.begin()
         */
        iterator begin() const {
            return edges.begin();
        }

        /**
         *  Returns edges.end()
         */
        iterator end() const {
            return edges.end();
        }

        /**
         *  Returns the number of vertices.
         */
        int n_vertices() const {
            return vertices;
        }

        /**
         *  Returns the number of edges.
         */
        int n_edges() const {
            return edges.size();
        }

        /**
         *  Writes a graph to an ostream. Used by boost_python to implement
         *  __str__.
         *
         *  @param os the ostream
         *  @param g the graph
         */
        friend ostream& operator<<(ostream& os, const Graph<Edge>& g) {
            return os << g.to_string();
        }
    };

    /**
     *  Template for edges.
     */
    template <uint64_t       (_enc)(pair<int, int>),
              pair<int, int> (_dec)(uint64_t)>
    class Edge {
        uint64_t x;
    public:

        /**
         *  Construct an edge from its integer representation.
         */
        Edge<_enc, _dec>(uint64_t x): x(x) {}

        /**
         *  Returns the integer representation.
         */
        operator uint64_t() const {
            return x;
        }

        /**
         *  Returns the vertices that the edge connects.
         */
        operator pair<int, int>() {
            return _dec(x);
        }

        /**
         *  Creates an edge from the vertices it connects.
         *
         *  @param first starting edge
         *  @param second ending edge
         */
        Edge<_enc, _dec>(int first, int second) {
            x = _enc(make_pair(first, second));
        }

        /**
         *  Creates an edge from the vertices it connects.
         *
         *  @param first starting edge
         *  @param second ending edge
         */
        Edge<_enc, _dec>(pair<int, int> p) {
            x = _enc(p);
        }

        /**
         *  Default constructor.
         */
        Edge<_enc, _dec>() {}

        /**
         *  Writes an edge to an ostream. Used by boost_python to implement
         *  __str__.
         *
         *  @param os the ostream
         *  @param e the edge
         */
        friend ostream& operator<<(ostream& os, const Edge<_enc, _dec>& e) {
            pair<int, int> p = _dec(e);
            return os << p.first << " " << p.second;
        }

        /**
         *  Checks if the edge is equal to the other edge.
         *
         *  @param other
         */
        inline bool operator==(const Edge<_enc, _dec>& other) const {
            return x == other.x;
        }

        /**
         *  Checks if the edge is different from the other edge.
         *
         *  @param other
         */
        inline bool operator!=(const Edge<_enc, _dec>& other) const {
            return !(*this == other);
        }

        /**
         *  Checks if a certain representation corresponds to this edge.
         *
         *  @param other
         */
        inline bool operator==(const uint64_t& r) const {
            return _dec(x) == _dec(r);
        }

        /**
         *  Increments the edge representation.
         */
        Edge<_enc, _dec>& operator+=(const uint64_t& inc) {
            x += inc;
            return *this;
        }
    };

    /**
     *  Encodes an undirected edge (a, b), where we suppose a >= b, to 
     *  integer a*(a+1)/2 + b.
     *
     *  @param e the pair representing the edge
     */
    inline uint64_t undirected_enc(pair<int, int> e) {
        uint64_t a = e.first < e.second ? e.second : e.first;
        uint64_t b = e.first < e.second ? e.first : e.second;
        return a*(a+1)/2 + b;
    }

    /**
     *  Decodes an undirected edge. The first vertex will be
     *  round(sqrt(2*(x+1))-1) and the second one will be x - a*(a+1)/2,
     *  given in a random order.
     *
     *  @param x encoded value of the edge
     */
    inline pair<int, int> undirected_dec(uint64_t x) {
        uint64_t a = round(sqrt(2*(x+1)))-1;
        uint64_t b = x - a*(a+1)/2;
        if(Random::randint(2)) return make_pair(b, a);
        else return make_pair(a, b);
    }

    /**
     *  Encodes a directed edge (a, b), where we suppose a >= b, to integer
     *  a*(a+1) + 2*b (+1 if the edge goes from a lower vertex to a
     *  greater one).
     *
     *  @param e the pair representing the edge
     */
    inline uint64_t directed_enc(pair<int, int> e) {
        uint64_t a = e.first < e.second ? e.second : e.first;
        uint64_t b = e.first < e.second ? e.first : e.second;
        return a*(a+1) + 2*b + (e.first<e.second);
    }

    /**
     *  Decodes a directed edge. The firstvertex will be
     *  round(sqrt(2*(x/2+1))-1) and the second one will be (x - a*(a+1))/2,
     *  given in an order decided by the parity of x.
     *
     *  @param x encoded value of the edge
     */
    inline pair<int, int> directed_dec(uint64_t x) {
        uint64_t a = round(sqrt(2*(x/2+1)))-1;
        uint64_t b = (x - a*(a+1))/2;
        if(x%2) return make_pair(b, a);
        else return make_pair(a, b);
    }

    /**
     *  Encodes a DAG edge (a, b), where we suppose a >= b, to integer 
     *  a*(a+1)/2 + b.
     *
     *  @param e the pair representing the edge
     */
    inline uint64_t dag_enc(pair<int, int> e) {
        uint64_t a = e.first < e.second ? e.second : e.first;
        uint64_t b = e.first < e.second ? e.first : e.second;
        return a*(a+1)/2 + b;
    }

    /**
     *  Decodes a DAG edge. The first vertex will be round(sqrt(2*(x+1))-1) 
     *  and the second one will be x - a*(a+1)/2.
     *
     *  @param x encoded value of the edge
     */
    inline pair<int, int> dag_dec(uint64_t x) {
        uint64_t a = round(sqrt(2*(x+1)))-1;
        uint64_t b = x - a*(a+1)/2;
        return make_pair(b, a);
    }

    typedef Edge<undirected_enc, undirected_dec> Undirected;
    typedef Edge<directed_enc, directed_dec> Directed;
    typedef Edge<dag_enc, dag_dec> DAG;
}

namespace std {
    template <uint64_t       (_enc)(pair<int, int>),
              pair<int, int> (_dec)(uint64_t)>
    struct hash<Graph::Edge<_enc, _dec>> {
        inline uint64_t operator()(const Graph::Edge<_enc, _dec>& k) const {
            return k;
        }
    };
}

namespace Graph {
    /**
     *  Transposes a directed graph.
     *
     *  @param g the graph to transpose
     */

    Graph<Directed> transpose(const Graph<Directed>& g) {
        vector<Directed> tmp;
        for(auto e: g) {
            pair<int, int> p = e;
            swap(p.first, p.second);
            tmp.push_back(Directed(e));
        }
        return Graph<Directed>(g.n_vertices(), tmp);
    }
}
#endif
