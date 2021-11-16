#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y)  (out)  << (x) << endl << (y) << endl

int main() {
  TestRunner tr;
  tr.RunTest([] {
    ostringstream a;
    PRINT_VALUES(a, 5 + 1, "  red belt");
    ASSERT_EQUAL(a.str(), "6\n  red belt\n");
   
  }, "PRINT_VALUES usage example");
  return 0;
}