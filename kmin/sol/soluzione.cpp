#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int nextInt() {
  int n = 0;
  bool negative = false;
  int c = getchar();
  while ((c < '0' || c > '9') && c != '-')
    c = getchar();
  if (c == '-') {
    negative = true;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    n = 10 * n + c - '0';
    c = getchar();
  }
  return negative ? -n : n;
}

int count;
vector<int> a;
int main() {
  int N, K;
  N = nextInt();
  K = nextInt();
  a.resize(N);
  for (int i = 0; i < N; i++) {
    a[i] = nextInt();
  }
  nth_element(a.begin(), a.begin() + K, a.end());
  cout << a[K] << endl;
}
