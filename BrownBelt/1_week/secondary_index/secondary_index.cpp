#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
  
  multimap<string, Record*>::iterator Iter_u;
  multimap<int, Record*>::iterator Iter_t;
  multimap<int, Record*>::iterator Iter_k;
};

// Реализуйте этот класс
class Database {
private:

  unordered_map<string, Record> storage;
  multimap<string, Record*> user_st;
  multimap<int, Record*> time_st;
  multimap<int, Record*> karma_st;

public:
  bool Put(const Record& record) {
    auto [Iter, success] = 
          storage.insert({record.id, record});
    if(success) {
      Iter->second.Iter_u = 
            user_st.insert({record.user, &Iter->second});

      Iter->second.Iter_t = 
            time_st.insert({record.timestamp, &Iter->second});

      Iter->second.Iter_k = 
            karma_st.insert({record.karma, &Iter->second});
      return success;
    }
    return success;
  }

  const Record* GetById(const string& id) const {
    auto Iter = storage.find(id);
    return Iter == storage.end() ? nullptr : &Iter->second;
  }

  bool Erase(const string& id) {
    auto Find = storage.find(id);
    if(Find != storage.end()) {
      karma_st.erase(Find->second.Iter_k);
      user_st.erase(Find->second.Iter_u);
      time_st.erase(Find->second.Iter_t);
      storage.erase(Find);
      return true;
    }
    return false;
  }

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const {
    auto first = time_st.lower_bound(low);
    auto last = time_st.upper_bound(high);
    for( ; first != last; first++) {
      if(!callback(*first->second)) break;
    }
  }

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const {
    auto first = karma_st.lower_bound(low);
    auto last = karma_st.upper_bound(high);
    for( ; first != last; first++) {
      if(!callback(*first->second)) break;
    }
  }

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const {
    auto [first, last] = user_st.equal_range(user);
    for( ;first != last; first++) {
      if(!callback(*first->second)) break;
    }
  }
};

void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}
