#include "test_runner.h"
#include <sstream>
#include <string>
using namespace std;

class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }

  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file= value; }
  void Log(const string& message) {
    os << message;
  }
  pair<bool,bool> Get() {
    return make_pair(log_line, log_file);
  }

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
};

#define LOG(logger, message) {\
  ostringstream stream;\
  auto par = logger.Get();\
  if (par.first && par.second) {\
    stream << __FILE__ << ":" << __LINE__ << " " << message <<"\n";\
  } else if (par.first && !par.second) {\
    stream << "Line " << __LINE__ << " " << message << "\n";\
  } else if (!par.first && par.second) {\
    stream << __FILE__ << " " << message << "\n";\
  } else {\
    stream << message << "\n";\
  }\
  logger.Log(stream.str());\
}

void TestLog() {
#line 1 "logger.cpp"

  ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
}
