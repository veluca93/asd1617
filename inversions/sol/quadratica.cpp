#include <iostream>
#include <vector>
using namespace std;

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

void insertionsort(int *arr, int begin, int end) {
  int i, j;
  for (i = begin + 1; i < end; i++) {
    for (j = i - 1; j >= begin; j--) {
      if (arr[j] > arr[j + 1])
        swap(&arr[j], &arr[j + 1]);
      else
        break;
    }
  }
}

void quicksort(int *arr, int begin, int end) {
  if (end - begin <= 1)
    return;
  if (end - begin <= 16)
    return insertionsort(arr, begin, end);
  int pivot_position = partition(arr, begin, end);
  quicksort(arr, begin, pivot_position);
  quicksort(arr, pivot_position + 1, end);
}

int main() {
  int num;
  std::vector<int> data;
  cin >> num;
  data.reserve(num);
  for (int i = 0; i < num; i++) {
    int a;
    cin >> a;
    data.push_back(a);
  }
  for (int i = 0; i < num; i++) {
    int a;
    cin >> a;
    data.push_back(a);
  }
  long long count = 0;
  for (int i = 0; i < num; i++) {
    for (int j = i + 1; j < num; j++) {
      if (data[i] > data[j])
        count++;
    }
  }
  cout << count << std::endl;
  return 0;
}
