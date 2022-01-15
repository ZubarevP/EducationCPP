#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  if(range_end - range_begin < 2) {return;}
  vector<typename RandomIt::value_type> store
      (make_move_iterator(range_begin), make_move_iterator(range_end));
  
  size_t step = (range_end - range_begin) / 3;
  auto start = store.begin();
  auto middle1 = start + step;
  auto middle2 = middle1 + step;
  auto finish = store.end();

  MergeSort(start, middle1);
  MergeSort(middle1, middle2);
  MergeSort(middle2, finish);

  vector<typename RandomIt::value_type> temp;
  merge(make_move_iterator(start), make_move_iterator(middle1), 
      make_move_iterator(middle1), make_move_iterator(middle2), 
      back_inserter(temp));
  merge(make_move_iterator(temp.begin()), make_move_iterator(temp.end()), 
      make_move_iterator(middle2), make_move_iterator(finish), 
      range_begin);
}
void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
