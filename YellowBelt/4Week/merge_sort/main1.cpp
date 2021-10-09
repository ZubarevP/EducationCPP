#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    } 
    vector<typename RandomIt::value_type> old_vector(range_begin, range_end);
    auto it = begin(old_vector) + old_vector.size() / 2;
    MergeSort(begin(old_vector), it);
    MergeSort(it, end(old_vector));
    merge(begin(old_vector), it, it, end(old_vector), range_begin);
}
int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
