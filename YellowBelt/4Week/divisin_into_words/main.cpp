#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
  vector<string> words;
  auto start = s.begin();
  auto finish = s.begin();
  while(finish < s.end()) {
    finish = find( start, s.end(), ' ');
    words.push_back({start, finish});
    ++finish;
    start = finish;
  }
  return words;
}0

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}