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


int Line (const int& b, const int& c) {
    if (b != 0) {
        return 1;
    } else {
        return 0;
    }     
}
int Quadro (const int& a, const int& b, const int& c) {
    int D;
    D = b * b - 4 * a * c;
    if (D == 0) {
        return 1;
    } else if (D > 0) {
        return 2;
    } else {
        return 0;
    }
}
int GetDistinctRealRootCount(double a, double b, double c) {
    if (a == 0) {
        return Line(b, c);
    } else {
        return Quadro (a, b, c);
    }
 
}

void ZeroA (){
   AssertEqual(GetDistinctRealRootCount(0, 1, 1), 1, "A  = 0");
   AssertEqual(GetDistinctRealRootCount(0, 1, -1), 1, "A  = 0");
   AssertEqual(GetDistinctRealRootCount(0, 2, -6), 1, "A  = 0");
   AssertEqual(GetDistinctRealRootCount(0, 7, -7), 1, "A  = 0");
   AssertEqual(GetDistinctRealRootCount(0, 48, 256), 1, "A  = 0");
}

void ZeroAC () {
   AssertEqual(GetDistinctRealRootCount(0, -101, 0), 1, "A and C = 0");
   AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1, "A and C = 0");
   AssertEqual(GetDistinctRealRootCount(0, -2, 0), 1, "A and C = 0");
   AssertEqual(GetDistinctRealRootCount(0, 48, 0), 1, "A and C = 0");
}

void ABC () {    
   AssertEqual(GetDistinctRealRootCount(9, 1, 1), 0, "ABC1");
   AssertEqual(GetDistinctRealRootCount(-9, 1, -1), 0, "ABC2");
   AssertEqual(GetDistinctRealRootCount(13, 2, -6), 2, "ABC3");
   AssertEqual(GetDistinctRealRootCount(13, -7, -7), 2, "ABC4");
   AssertEqual(GetDistinctRealRootCount(2, 4, 2), 1, "ABC6");
}



int main() {
  TestRunner runner;
  runner.RunTest(ZeroA, "ZeroA");
  runner.RunTest(ZeroAC, "ZeroAC");
  runner.RunTest(ABC, "ABC");

  
  return 0;
}