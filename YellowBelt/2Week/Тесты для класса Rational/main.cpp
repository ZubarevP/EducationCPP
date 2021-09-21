#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

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
/*
class Rational {
public:
	Rational() {
		up = 0;
		down = 1;
	}
	Rational(int numerator, int denominator) {
		int NOD = 0;
		int A = max(numerator, denominator);
		int B = min(denominator,numerator);
		while (B != 0)  {
			int t = B;
			B = A % B;
			A = t;
			NOD = A;
		}
		if(numerator) {
			if (numerator < 0 && denominator < 0) {
				up = abs(numerator / NOD);
				down = abs(denominator / NOD);
			}
			else if (denominator < 0) {
				up = -numerator / abs(NOD);
				down = abs(denominator / NOD);
			}
			else {
				up = numerator / abs(NOD);
				down = denominator / abs(NOD);
			}
		}
		else {
			up = 0;
			down = 1;
		}
	}
	int Numerator() const {
		return up;
	}
	int Denominator() const {
		return down;
	}

private:
	int up;
	int down;
};
*/
void Test () {
    {
        Rational test;
        AssertEqual(test.Numerator(), 0, "#1.1 empty type");
        AssertEqual(test.Denominator(), 1, "#1.2 empty type");
    }
    {
        Rational test(1, 1);
        AssertEqual(test.Numerator(), 1, "2.1 numerator is 1/1");
        AssertEqual(test.Denominator(), 1, "2.2 denumerator is 1/1");
    }
    {
        Rational test(2, 2);
        AssertEqual(test.Numerator(), 1, "3.1 numerator is 2/2");
        AssertEqual(test.Denominator(), 1, "3.2 denumerator is 2/2");
    }
    {
        Rational test(1, 3);
        AssertEqual(test.Numerator(), 1, "4.1 numerator is 1/3");
        AssertEqual(test.Denominator(), 3, "4.2 denumerator is 1/3");
    }
    {
        Rational test(6, 6);
        AssertEqual(test.Numerator(), 1, "5.1 numerator is 6/6");
        AssertEqual(test.Denominator(), 1, "5.2 denumerator is 6/6");
    }
    {
        Rational test(8, 12);
        AssertEqual(test.Numerator(), 2, "6.1 numerator is 8/12");
        AssertEqual(test.Denominator(), 3, "6.2 denumerator is 8/12");
    }
    {
        Rational test(-8, 12);
        AssertEqual(test.Numerator(), -2, "7.1 numerator is -8/12");
        AssertEqual(test.Denominator(), 3, "7.2 denumerator is -8/12");
    }
    {
        Rational test(8, -12);
        AssertEqual(test.Numerator(), -2, "8.1 numerator is 8/-12");
        AssertEqual(test.Denominator(), 3, "8.2 denumerator is 8/-12");
    }
    {
        Rational test(-5, 7);
        AssertEqual(test.Numerator(), -5, "9.1 numerator is -5/7");
        AssertEqual(test.Denominator(), 7, "9.2 denumerator is -5/7");
    }
    {
        Rational test(-8, -12);
        AssertEqual(test.Numerator(), 2, "10.1 numerator is -8/-12");
        AssertEqual(test.Denominator(), 3, "10.2 denumerator is -8/-12");
    }
    {
        Rational test(-5, -7);
        AssertEqual(test.Numerator(), 5, "11.1 numerator is -5/-7");
        AssertEqual(test.Denominator(), 7, "11.2 denumerator is -5/-7");
    }
    {
        Rational test(0, 9);
        AssertEqual(test.Numerator(), 0, "12.1 numerator is 0/9");
        AssertEqual(test.Denominator(), 1, "12.2 denumerator is 0/9");
    }
    {
        Rational test(0, -7);
        AssertEqual(test.Numerator(), 0, "13.1 numerator is 0/-7");
        AssertEqual(test.Denominator(), 1, "13.2 denumerator is 0/-7");
    }
}

int main() {
  TestRunner runner;
  runner.RunTest(Test, "Test");
  return 0;
}