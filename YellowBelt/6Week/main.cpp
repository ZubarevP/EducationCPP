#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"
#include "test_db.h"

#include <iostream>
#include <stdexcept>
#include <map>
#include <vector>
#include <string>
#include <utility>

using namespace std;

int g_num_of_var = 0;

void TestAll(); 

int main() {
  TestAll();

  Database db;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") { 
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;

    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }
  return 0;
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestEmptyNode, "???????? 1");
  tr.RunTest(TestDbAdd, "???????? 2");
  tr.RunTest(TestDbFind, "???????? 3");
  tr.RunTest(TestDbLast, "???????? 4");
  tr.RunTest(TestDbRemoveIf, "???????? 5");
  tr.RunTest(TestInsertionOrder, "???????? 6");
  tr.RunTest(TestsMyCustom, "???????? 7");
  tr.RunTest(TestDatabase, "???????? 8");
  tr.RunTest(TestDateComparisonNode, "???????? 9");
  tr.RunTest(TestEventComparisonNode, "???????? 10");
  tr.RunTest(TestEmptyNode, "???????? 11");
  tr.RunTest(TestParseEvent, "T?????? 12");
  tr.RunTest(TestParseCondition, "T?????? 13");
 }
