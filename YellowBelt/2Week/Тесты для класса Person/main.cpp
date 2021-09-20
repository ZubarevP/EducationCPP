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

string FindNameByYear(const map<int, string>& names, int year) {
  string name;
  for (const auto& item : names) {
    if (item.first <= year) {
      name = item.second;
    } else {
      break;
    }
  }
  return name;
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    if (first_names.count(year) == 0 && !first_name.empty()) {
    first_names[year] = first_name;
    }
  }
  //тест имени
  string GetName(int year) {
    return first_names.at(year);
  }
  //тест имени
  bool GetNameB(int year) {
    if (first_names.count(year)) {
      return false;
    }
    return true;
  }

  void ChangeLastName(int year, const string& last_name) {
    if (last_names.count(year) == 0 && !last_name.empty()) {
    last_names[year] = last_name;
    }
  }
 //тест имени
  string GetSuName(int year) {
    return last_names.at(year);
  }
  //тест имени
  bool GetSuNameB(int year) {
    if (last_names.count(year)) {
      return false;
    }
    return true;
  }

  string GetFullName(int year) {
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";
    } else {
      return first_name + " " + last_name;
    }
  }
private:
  map<int, string> first_names;
  map<int, string> last_names;
};

void TestAddName (){
  Person Test;
  Test.ChangeFirstName(2021, "Pavel");
  Test.ChangeFirstName(2021, "Oleg");
  AssertEqual(Test.GetName(2021), "Pavel", "Test two name on one year");
  Test.ChangeFirstName(2020, "");
  Assert(Test.GetNameB(2020), "Test empty");
  Test.ChangeFirstName(2024, "Ivan");
  AssertEqual(Test.GetName(2024), "Ivan", "Test name");
}
void TestAddSurName (){
  Person Test;
  Test.ChangeLastName(2021, "Pavlov");
  Test.ChangeLastName(2021, "Olegov");
  AssertEqual(Test.GetSuName(2021), "Pavlov", "Test two surname on one year");
  Test.ChangeLastName(2020, "");
  Assert(Test.GetSuNameB(2020), "Test empty");
  Test.ChangeLastName(2024, "Ivanov");
  AssertEqual(Test.GetSuName(2024), "Ivanov", "Test suname");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestAddName, "TestAddName");
  runner.RunTest(TestAddSurName, "TestAddSurName");


  return 0;
}