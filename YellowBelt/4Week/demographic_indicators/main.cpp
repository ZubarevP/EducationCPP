#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}*/

void PrintStats(vector<Person> persons) {
    int a, b, c, d, e, f, g;
    //all persons
    a = ComputeMedianAge(begin(persons), end(persons));

   // only women
    auto B = partition(begin(persons), end(persons), 
        [](const Person& pers)
        {
            return pers.gender == Gender::FEMALE;        
        }
    );
    b = ComputeMedianAge(begin(persons), B);

    // only man
    auto C = partition(begin(persons), end(persons), 
        [](const Person& pers)
        {
            return pers.gender == Gender::MALE;        
        }
    );
    c = ComputeMedianAge(begin(persons), C);

    // only women with job
    auto D = partition(begin(persons), end(persons), 
        [] (const Person& pers) 
        {
            return pers.gender == Gender::FEMALE && pers.is_employed == true;

        }
    );
    d = ComputeMedianAge(begin(persons), D);

    //only women without job
    auto E = partition(begin(persons), end(persons), 
        [] (const Person& pers) 
        {
            return pers.gender == Gender::FEMALE && pers.is_employed == false;
        }
    );
    e = ComputeMedianAge(begin(persons), E);

    // only men with job
    auto F = partition(begin(persons), end(persons), 
        [] (const Person& pers) 
        {
            return pers.gender == Gender::MALE && pers.is_employed == true;

        }
    );
    f = ComputeMedianAge(begin(persons), F);
    
    //only men without job
    auto G = partition(begin(persons), end(persons), 
        [] (const Person& pers) 
        {
            return pers.gender == Gender::MALE && pers.is_employed == false;
        }
    );
    g = ComputeMedianAge(begin(persons), G);

    cout << "Median age = " << a << endl;
    cout << "Median age for females = " << b << endl;
    cout << "Median age for males = " << c << endl;
    cout << "Median age for employed females = " << d << endl;
    cout << "Median age for unemployed females = " << e << endl;
    cout << "Median age for employed males = " << f << endl;
    cout << "Median age for unemployed males = " << g << endl;
}
/*
int main() {
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
  PrintStats(persons);
  return 0;
}*/