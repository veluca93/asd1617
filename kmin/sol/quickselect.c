#include <stdio.h>
#include <stdlib.h>

int K;

int nextInt() {
  int n = 0;
  int negative = 0;
  int c = getchar();
  while ((c < '0' || c > '9') && c != '-')
    c = getchar();
  if (c == '-') {
    negative = 1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    n = 10 * n + c - '0';
    c = getchar();
  }
  return negative ? -n : n;
}

void swap(int *a, int *b) {
  int t = *b;
  *b = *a;
  *a = t;
}

int partition(int *arr, int begin, int end) {
  int pivot_position = (end + begin) / 2;
  swap(&arr[begin], &arr[pivot_position]);
  pivot_position = begin;
  int i;
  for (i = begin + 1; i < end; i++) {
    if (arr[i] < arr[pivot_position]) {
      swap(&arr[i], &arr[pivot_position]);
      pivot_position++;
      swap(&arr[i], &arr[pivot_position]);
    }
  }
  return pivot_position;
}

void quickselect(int *arr, int begin, int end) {
  if (end - begin <= 1)
    return;
  if (begin > K)
    return;
  if (end <= K)
    return;
  int pivot_position = partition(arr, begin, end);
  quickselect(arr, begin, pivot_position);
  quickselect(arr, pivot_position + 1, end);
}

int main() {
  int num;
  int *data;
  num = nextInt();
  K = nextInt();
  data = malloc(sizeof(int) * num);
  int i;
  for (i = 0; i < num; i++) {
    data[i] = nextInt();
  }
  quickselect(data, 0, num);
  printf("%d\n", data[K]);
  return 0;
}
