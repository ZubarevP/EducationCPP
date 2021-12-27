#include "test_runner.h"
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <map>

using namespace std;

class Translator {
public:
  Translator() = default;
  void Add(string_view source, string_view target) {
    auto a = Search(source);
    auto b = Search(target);
    data_forward[a] = b;
    data_backward[b] = a;
  }
  string_view TranslateForward(string_view source) const {
    return data_forward.count(source) ? data_forward.at(source): string_view ();
  }
  string_view TranslateBackward(string_view target) const {
    return data_backward.count(target) ? data_backward.at(target): string_view ();
  }
private:
  list<string> data;
  map<string_view, string_view> data_forward;
  map<string_view, string_view> data_backward;

  string_view Search (string_view value) {
    if(data_forward.count(value)) {
      return data_forward.find(value)->first;
    } else if (data_forward.count(value)) {
      return data_backward.find(value)->first;
    }
    return data.emplace_back(value);
  }
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));
  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}