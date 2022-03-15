#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;
  Gender gender;
  bool is_employed;
};

bool operator==(const Person& lhs, const Person& rhs) {
  return lhs.age == rhs.age
      && lhs.gender == rhs.gender
      && lhs.is_employed == rhs.is_employed;
}

ostream& operator<<(ostream& stream, const Person& person) {
  return stream << "Person(age=" << person.age 
      << ", gender=" << static_cast<int>(person.gender)
      << ", is_employed=" << boolalpha << person.is_employed << ")";
}

struct AgeStats {
  int total;
  int females;
  int males;
  int employed_females;
  int unemployed_females;
  int employed_males;
  int unemployed_males;
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename iterator_traits<InputIt>::value_type> range_copy(
      range_begin,
      range_end
  );
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}

vector<Person> ReadPersons(istream& in_stream = cin) {
  int person_count;
  in_stream >> person_count;
  vector<Person> persons;
  persons.reserve(person_count);
  for (int i = 0; i < person_count; ++i) {
    int age, gender, is_employed;
    in_stream >> age >> gender >> is_employed;
    Person person{
        age,
        static_cast<Gender>(gender),
        is_employed == 1
    };
    persons.push_back(person);
  }
  return persons;
}

AgeStats ComputeStats(vector<Person> persons) {
  //                 persons
  //                |       |
  //          females        males
  //         |       |      |     |
  //      empl.  unempl. empl.   unempl.

  auto females_end = partition(
      begin(persons), end(persons),
      [](const Person& p) {
        return p.gender == Gender::FEMALE;
      }
  );
  auto employed_females_end = partition(
      begin(persons), females_end,
      [](const Person& p) {
        return p.is_employed;
      }
  );
  auto employed_males_end = partition(
      females_end, end(persons),
      [](const Person& p) {
        return p.is_employed;
      }
  );

  return {
       ComputeMedianAge(begin(persons), end(persons)),
       ComputeMedianAge(begin(persons), females_end),
       ComputeMedianAge(females_end, end(persons)),
       ComputeMedianAge(begin(persons),  employed_females_end),
       ComputeMedianAge(employed_females_end, females_end),
       ComputeMedianAge(females_end, employed_males_end),
       ComputeMedianAge(employed_males_end, end(persons))
  };
}

void PrintStats(const AgeStats& stats,
                ostream& out_stream = cout) {
  out_stream << "Median age = "
             << stats.total              << endl
             << "Median age for females = "
             << stats.females            << endl
             << "Median age for males = "
             << stats.males              << endl
             << "Median age for employed females = "
             << stats.employed_females   << endl
             << "Median age for unemployed females = "
             << stats.unemployed_females << endl
             << "Median age for employed males = "
             << stats.employed_males     << endl
             << "Median age for unemployed males = "
             << stats.unemployed_males   << endl;
}



void TestComputeMedianAgeIter() {
    vector<Person> temp;
    int result = ComputeMedianAge(temp.begin(), temp.end());
    ASSERT_EQUAL(result, 0);
}

void TestComputeMedianAgeMiddle() {
    vector<Person> persons = {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };

    int result = ComputeMedianAge(
        persons.begin(), persons.end()
    );

    persons.push_back({});
    int result4 = ComputeMedianAge(
        persons.begin(), persons.end()
    );

    for(auto& l : persons) {
        l.age *= 2;
    }
    int result2 = ComputeMedianAge(
        persons.begin(), persons.end()
    );

    for(auto& l : persons) {
        l.age *= 0;
    }
    int result3 = ComputeMedianAge(
        persons.begin(), persons.end()
    );

    ASSERT_EQUAL(result, 40);
    ASSERT_EQUAL(result2, 62);
    ASSERT_EQUAL(result3, 0);
    ASSERT_EQUAL(result4, 31);
}

void TestReadPersons() {
    vector<Person> persons = {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };

    istringstream input
        ("8 31 1 0 40 0 1 24 1 1 20"
        " 0 1 80 0 0 78 1 0 10 0 0 55 1 1");
    ASSERT_EQUAL(ReadPersons(input), persons);

}

void TestComputeStats() {
    vector<Person> persons = {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };
    auto result = ComputeStats(persons);
    AgeStats temp{
        40, 40, 55, 40, 80, 55, 78
    };
    ASSERT_EQUAL(result.total,              temp.total);
    ASSERT_EQUAL(result.females,            temp.females);
    ASSERT_EQUAL(result.males,              temp.males);
    ASSERT_EQUAL(result.employed_females,   temp.employed_females);
    ASSERT_EQUAL(result.unemployed_females, temp.unemployed_females);
    ASSERT_EQUAL(result.employed_males,     temp.employed_males);
    ASSERT_EQUAL(result.unemployed_males,   temp.unemployed_males);
}

void TestOutputMessage() {
    AgeStats temp{
        40, 40, 55, 40, 80, 55, 78
    };
    ostringstream output;
    PrintStats(temp, output);
    string line (
        "Median age = 40\n"
        "Median age for females = 40\n"
        "Median age for males = 55\n"
        "Median age for employed females = 40\n"
        "Median age for unemployed females = 80\n"
        "Median age for employed males = 55\n"
        "Median age for unemployed males = 78\n"
    );
    ASSERT_EQUAL(output.str(), line);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestComputeMedianAgeIter);
    RUN_TEST(tr, TestComputeMedianAgeMiddle);
    RUN_TEST(tr, TestReadPersons);
    RUN_TEST(tr, TestComputeStats);
    RUN_TEST(tr, TestOutputMessage);

    PrintStats(ComputeStats(ReadPersons()));
    return 0;
}
