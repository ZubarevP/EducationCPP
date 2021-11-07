#pragma once 
#include "date.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class Database {
public:
    void Add (const Date& date, const string& event);
    void Print(ostream& stream) const;
    string Last(const Date& date) const;
    int RemoveIf(const function<bool(const Date&, const string&)> &kui);
    vector<pair<Date, string>> FindIf(const function<bool(const Date&, const string&)> &kui) const;
   
private:
    map<Date, vector<string>> dateb; 
};

string ParseEvent(istream& is);

 void TestAll();

ostream& operator<< (ostream& stream,  pair<Date, string> rhs);