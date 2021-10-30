#pragma once
#include <iostream> 
#include <iomanip>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

class Date {
public:
    Date(){}
    Date(int Y, int M, int D);
    string GetDate();
    void AddYear (const string& year);
    void AddMounth (const string& mounth);
    void AddDay (const string& day);
private:
   string date;
};

Date ParseDate (istringstream& stream);

ostream& operator<< (ostream& stream, Date date);
bool operator== (const Date& lhs, const Date& rhs);
bool operator< (const Date& lhs, const Date& rhs);
bool operator> (const Date& lhs, const Date& rhs);
bool operator>= (const Date& lhs, const Date& rhs);
bool operator<= (const Date& lhs, const Date& rhs);
bool operator!= (const Date& lhs, const Date& rhs);
