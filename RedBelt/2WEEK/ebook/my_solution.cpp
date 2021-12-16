#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <iterator>
#include "profile.h"

using namespace std;
template<typename Iterator>
class HAF {
public:
  HAF (Iterator a, Iterator b)
  : first(a)
  , second(b)
   {}
  Iterator begin () {
    return first;
  }
  Iterator end () {
    return second;
  }
private:
  Iterator first;
  Iterator second;
};

class ReadingManager {
public:
  void Read(const int &user_id, const int &page_count) {
    if(USERS.count(user_id)) {
      PAGES.at( USERS.at(user_id))--;
      if (PAGES.at( USERS.at(user_id)) <= 0) {
        PAGES.erase( USERS.at(user_id));
      }
    } 
      USERS[user_id] = page_count;
      PAGES[page_count]++;
  }

  double Cheer(const int &user_id) const {
    if (!USERS.count(user_id)) {
      return 0;
    } else if (USERS.size() == 1) {
      return 1;
    }
    auto pos = PAGES.lower_bound(USERS.at(user_id));
    int size_of_reader = 0;
    HAF haf = {PAGES.begin(), pos};
    for (auto LL : haf) {
      size_of_reader += LL.second;
    }
    return 1.0 * size_of_reader / (USERS.size() - 1);
  }
private:
  map<int, int> USERS;
  map<int, int> PAGES;
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }
  return 0;
}