#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:

    PriorityCollection():current_num(0) {Reserve();}

    using Id = size_t;
    using Priority =  typename set<pair<int, Id>>::iterator;

    Id Add(T object) {
      auto [Iterator, Bool] = priority_range.insert(make_pair(0, current_num));
      database.push_back(make_pair(move(object), Iterator));
      return current_num++;
    }

    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin) {
      for (auto itera = make_move_iterator(range_begin); itera != make_move_iterator(range_end); ++itera) {
        *(ids_begin++) = Add(*itera);
      }
    }   

    bool IsValid(Id id) const {
      if(id > database.size() - 1)  {return false;}
      return database[id].second != priority_range.end() ;
     
    }

    const T& Get(Id id) const {
      return database[id].first;
    }

    void Promote(Id id) {
      auto temp_priority = database[id].second->first;
      auto temp_id = database[id].second->second;
      priority_range.erase(database[id].second);
      auto [Iterator, Bool] = priority_range.insert(make_pair(++temp_priority, temp_id));
      database[id].second = Iterator;
    }
      //
    pair<const T&, int> GetMax() const {
        auto id_last = prev(priority_range.end());
        return {database[id_last->second].first, id_last->first};
    }

    pair<T, int> PopMax() {
        auto id = prev(priority_range.end())->second;
        auto temp_priority = database[id].second->first;
        auto temp_id = database[id].second->second;
        priority_range.erase(database[id].second);
        database[id].second = priority_range.end();
        return {move(database[id].first), temp_priority};
    }

private:
    Id current_num;
    vector<pair<T, Priority>> database;
    set<pair<int, Id>> priority_range;
    void Reserve() {
      database.reserve(1000000);
    }

};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");
  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
    
  {
    ASSERT(strings.IsValid(yellow_id));
    ASSERT(strings.IsValid(white_id));
    ASSERT(strings.IsValid(red_id));
    ASSERT_EQUAL(strings.IsValid(16), false);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
 {
   const auto item = strings.PopMax();
   ASSERT_EQUAL(item.first, "yellow");
   ASSERT_EQUAL(item.second, 2);
 }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}