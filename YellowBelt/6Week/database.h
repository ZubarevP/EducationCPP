#pragma once 
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "date.h"
#include <iterator>

using namespace std;

class Database {
  public:
    void Add (const Date& date, const string& event);
    void Print(ostream& stream);
    string Last(const Date& date);
    int RemoveIf(auto);
    void FindIf();
   
  private:
map<Date, vector<string>> db;
};

string ParseEvent(istream& is);

 void TestAll();