#include <iostream>
#include <algorithm>
#include <set>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border) {
      auto iter = numbers.lower_bound(border);      
      
      if (numbers.empty()) {
        return iter;
      } else if (iter == begin(numbers)) {
        return iter;
      } else if (iter == end(numbers)) {
        return prev(iter);
      } else {
        int a, b;
        a = border - *prev(iter);
        b = *iter - border;
          if (a == b) {
            return prev(iter);
          } else if (a < b) {
            return prev(iter);
          } else {
            return iter;
          }
      }
    }

int main() {
 set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;
      
  set<int> empty_set;
  
  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;

  return 0;
}
//1 4 4 6 6
//1