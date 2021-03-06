#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
  vector<T> for_all; 
  auto IT = find_if(elements.begin(), elements.end(), [&, border] (const T& num) {return (border < num); });
  for (auto it = IT; it != elements.end(); ++it) {
    for_all.push_back(*it);
  }
  return for_all;
}

int main() {
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
    cout << x << " ";
  }
  cout << endl;
  
  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
  return 0;
}