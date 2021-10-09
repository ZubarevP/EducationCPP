#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 3) {
        return;
    } 
    vector<typename RandomIt::value_type> old_vector(range_begin, range_end);
    auto it1 = begin(old_vector) + old_vector.size() / 3;
    auto it2 = it1 + old_vector.size() / 3;
    MergeSort(begin(old_vector), it1);
    MergeSort(it1, it2);
    MergeSort(it2, end(old_vector));
    vector<typename RandomIt::value_type> temporary;
    merge(begin(old_vector), it1, it1, it2, back_inserter(temporary));
    merge(begin(temporary), end(temporary), it2, end(old_vector), range_begin);
}
int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
