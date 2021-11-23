#include "test_runner.h"
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template <typename T>
class Table {
private:
  vector<vector<T>> matrix;
public:
  Table (size_t x, size_t y) {
    Resize(x, y);
  }
  void Resize(size_t x, size_t y) {
     matrix.resize(x);
    for (auto& ll : matrix) {
      ll.resize(y);
    }
  }
  pair<size_t, size_t> Size() const {
   if (!matrix.empty() && !matrix[0].empty()) {
    return {matrix.size(), matrix[0].size()};
    } 
    return {0, 0};
  }
  vector<T>& operator[] (size_t a) {
    return matrix[a];
  }
  const vector<T>& operator[] (size_t a) const {
    return matrix[a];
  }
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}