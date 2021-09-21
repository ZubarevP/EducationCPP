#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const pair<K, V>& p) {
  os << "{" << p.first << ": " << p.second;
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

bool IsPalindrom(const string& str) {
    if (str.size() == 0 || str.size() == 1) {
        return true;
    } else {
        int t = str.size() / 2;
        for (int i = 0; i < t; i++) {
            if (str[i] != str[str.size() - 1 - i]) {
                return false;
            }
        }
    }
    return true;
}

const auto p = [] (string word, bool log) {
    return pair<string, bool>(word, log);
};

void TestPolindrom () {
    AssertEqual(IsPalindrom(""),true, "#1");
    AssertEqual(IsPalindrom("y"), true, "#2");
    AssertEqual(IsPalindrom("H"), true, "#3");
    AssertEqual(IsPalindrom("qq"), true, "#4");
    AssertEqual(IsPalindrom("jj"), true, "#5");
    AssertEqual(IsPalindrom("J"), true, "#6");
    AssertEqual(IsPalindrom("Jj"), false, "#7");
    AssertEqual(IsPalindrom("jJ"), false, "#8");
    AssertEqual(IsPalindrom("abc"), false, "#9");
    AssertEqual(IsPalindrom("aba"), true, "#10");
    AssertEqual(IsPalindrom("aaa"), true, "#11");
    AssertEqual(IsPalindrom("aaA"), false, "#12");
    AssertEqual(IsPalindrom("Aaa"), false, "#13");
    AssertEqual(IsPalindrom("AaA"), true, "#14");
    AssertEqual(IsPalindrom("AAA"), true, "#15");
    AssertEqual(IsPalindrom("AA A"), false, "#16");
    AssertEqual(IsPalindrom("A AA"), false, "#17");
    AssertEqual(IsPalindrom("A aa"), false, "#18");
    AssertEqual(IsPalindrom("a AA"), false, "#19");
    AssertEqual(IsPalindrom("pavelevap"), true, "#20");
    AssertEqual(IsPalindrom("pavelevaP"), false, "#21");
    AssertEqual(IsPalindrom("paveleva p"), false, "#22");
    AssertEqual(IsPalindrom("qavelevap"), false, "#23");
    AssertEqual(IsPalindrom("pave l evap"),true, "#24");
    AssertEqual(IsPalindrom("pavel evap"), false, "#25");
    AssertEqual(IsPalindrom("pavelavap"), false, "#26");
    AssertEqual(IsPalindrom("pavelavep"), false, "#27");
    AssertEqual(IsPalindrom("paveLevap"), true, "#28");
    AssertEqual(IsPalindrom("pavelev/p"), false, "#29");
    AssertEqual(IsPalindrom("p:avelevap"), false, "#30");
    AssertEqual(IsPalindrom("paveevap"), true, "#31");
    AssertEqual(IsPalindrom("paveavap"), false, "#32");
    AssertEqual(IsPalindrom("pavaevap"), false, "#33");
    AssertEqual(IsPalindrom("paveavaq"), false, "#34");
    AssertEqual(IsPalindrom("qaveavap"), false, "#35");
    AssertEqual(IsPalindrom("paveavap/paveavap"), false, "#36");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestPolindrom, "TestPolindrom");
  return 0;
}