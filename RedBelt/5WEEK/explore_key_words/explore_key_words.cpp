#include "test_runner.h"
#include "profile.h"

#include <map>
#include <set>
#include <utility>
#include <future>
#include <functional>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
    , size_(distance(first, last))
  {}

  Iterator begin() const {return first;}
  Iterator end() const {return last;}
  size_t size() const {return size_;}

private:
  Iterator first, last;
  size_t size_;
};

struct Stats {
  map<string, int> word_frequences;
  Stats& operator += (const Stats& other) {
    for(const auto& [key, value] : other.word_frequences) {
      word_frequences[key] += value;
    }
    return *this;
  }
};

//Stats Counter(vector<string> strings_storage, const  set<string>& key_words) {
//  Stats result; 
//  IteratorRange range (strings_storage.begin(), strings_storage.end());
//  for (auto& line : range) {
//    size_t pos = 0;
//    string temp;
//    while(pos != line.npos) {
//      size_t epos = line.find(' ', pos);
//      if(epos != line.npos) { 
//        temp = line.substr(pos, epos - pos);
//        if(key_words.count(temp)) result.word_frequences[temp]++;
//      } else {
//        temp = line.substr(pos);
//        if(key_words.count(temp)) result.word_frequences[temp]++;
//        break;
//      }
//      pos = ++epos;
//    }
//  }
//  return result;
//}

Stats Counter(vector<string> strings_storage, const  set<string>& key_words) {
  Stats result; 
  IteratorRange range (strings_storage.begin(), strings_storage.end());
  for (auto& line : range) {
    string::const_iterator start = line.begin();
    string::const_iterator finish = line.end();
    auto iter = start;
    while ((iter = find(start, finish, ' ')) <= finish) {
      string word(start, iter);
      if (*key_words.lower_bound(word) == word) {
        result.word_frequences[word]++;
      }
      if(iter != finish) start = ++iter;
      else break;
    }
  }
  
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  LOG_DURATION("Total time");
  const size_t chunk_size = 5000;

  vector<string> strings_storage;
  strings_storage.reserve(chunk_size);
  vector<future<Stats>> futures_storage;

  while(input) {
    string line;
    getline(input, line);
    strings_storage.emplace_back( move(line));
    if(strings_storage.size() == chunk_size || !input) {
      futures_storage.push_back(async(Counter, move(strings_storage), ref(key_words)));
      strings_storage.reserve(chunk_size);
    }
  }

  Stats result;
  for(auto& fut : futures_storage) {
    result += fut.get();
  }
  return result; 
}

//void TestLong() {
//  ifstream stream ("articl.txt");
//  const set<string> key_words = {"Watson", "tool", "she", "murder", "death", "blood"};
//  const map<string, int> key_test = {{"Watson", 96}, {"she", 656}, {"murder", 80}, {"death", 16}, {"blood", 48}};
//  auto temp = ExploreKeyWords(key_words, stream);
//  ASSERT_EQUAL(temp.word_frequences, key_test);
//}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
  //RUN_TEST(tr, TestLong);
}
