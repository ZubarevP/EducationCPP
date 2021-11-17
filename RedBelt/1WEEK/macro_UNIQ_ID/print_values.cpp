#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define UNIQ_ID_THIRD(liter) name##liter
#define UNIQ_ID_SECOND(temp) UNIQ_ID_THIRD (temp) 
#define UNIQ_ID UNIQ_ID_SECOND(__LINE__)

int main() {
  int UNIQ_ID = 0; 
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
  return 0;
}