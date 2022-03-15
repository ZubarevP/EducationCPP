#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

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
}

void PrintResult (const vector<int>& result) {
    for(size_t i = 0; i < result.size(); ++i) {
    cout << "Median age ";
        switch(i) {
            case 0 : cout << "= " ;                         break;
            case 1 : cout << "for females = " ;             break;
            case 2 : cout << "for males = " ;               break;
            case 3 : cout << "for employed females = " ;    break;
            case 4 : cout << "for unemployed females = " ;  break;
            case 5 : cout << "for employed males = " ;      break;
            case 6 : cout << "for unemployed males = " ;    break;
        }
        cout << result[i] << '\n';
    }

}

struct GenderResult {
    int all, work, no_work;
};

template <typename Iter>
GenderResult GetGenderStats (Iter begin, Iter end) {
    GenderResult result;
    result.all = ComputeMedianAge(begin, end);
    auto it = partition(begin, end, [](const Person& lhs) {return lhs.is_employed == true;});
    result.work = ComputeMedianAge(begin, it);
    result.no_work = ComputeMedianAge(it, end);
    return result;
}



void PrintStats (vector<Person> persons){
    vector<int> result;
    result.push_back(ComputeMedianAge(persons.begin(), persons.end()));
    auto it = partition(persons.begin(), persons.end(), 
            [](const Person& lhs) {return lhs.gender == Gender::FEMALE;});
    auto female = GetGenderStats(persons.begin(), it);
    auto male = GetGenderStats(it, persons.end());
    result.push_back(female.all);
    result.push_back(male.all);
    result.push_back(female.work);
    result.push_back(female.no_work);
    result.push_back(male.work);
    result.push_back(female.no_work);
    PrintResult(result);
}

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
}
