#include <iostream>
#include <map>
#include <string>
#include <algorithm>
//#include <chrono>
#include <iomanip>

using namespace std;
//using namespace chrono;

string FindNameByYear(const map<int, string>& names, int year) {
  string name;
 
  auto iter = names.upper_bound(year);
  if (iter == names.begin()) {
      return name;
  } else {
      name = prev(iter)->second;
  }
  return name;
 }

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
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
/*
 int main() {
     system_clock::time_point start = system_clock::now();
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  system_clock::time_point end = system_clock::now();
  duration<double> sec = end - start;

  cout << fixed << setprecision(10) << sec.count() << endl;
  return 0;
}*/

//0.0000983580 - 0.0001030400 - 0.0000923900 - 0.0000919360
//0.0000627090 - 0.0001097090 - 0.0001093670 - 0.0019265700
//0.0001214070 - 0.0000937870 - 0.0000964230 - 0.0001610130
//0.0000750960 - 0.0000999260 - 0.0000666090 - 0.0001500190
//Incognito
//Polina with unknown last name
//Polina Sergeeva
//Polina Sergeeva
//Appolinaria Sergeeva
//Polina Volkova
//Appolinaria Volkova