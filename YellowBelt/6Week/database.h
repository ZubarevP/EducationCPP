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
    void Print(ostream& stream);
    string Last(const Date& date);
    
    template<typename T> 
      int RemoveIf(T& kui) {
        int num = 0;
       auto iter = dateb.begin();
       for (iter; iter != dateb.end(); ++iter) {
          int temp = iter->second.size();
          auto pos =  stable_partition(iter->second.rbegin(), iter->second.rend(),
                      [iter, kui](string& event){
                        return kui(iter->first, event);
                      });
          int temp2 = iter->second.rend() - pos;
          dateb.at(iter->first).resize(temp2);
          num += (temp - temp2);
       }
       return num;
      }
     
    template<typename T> 
    vector<pair<Date, string>> FindIf(T& kui){
      vector<pair<Date, string>> date_event;
      auto iter = dateb.begin();
      for (iter; iter != dateb.end(); ++iter) {
        auto pos =  stable_partition(iter->second.begin(), iter->second.end(),
                      [iter, kui](string& event){
                        return kui(iter->first, event);
                      });
        auto iter_v = iter->second.begin();
        for (iter_v; iter_v != pos + 1; ++iter_v) {
          date_event.push_back(make_pair(iter->first, *iter_v));
        }
      }
      return date_event;
    }
   
private:
    map<Date, vector<string>> dateb; 
};

string ParseEvent(istream& is);

 void TestAll();

ostream& operator<< (ostream& stream,  pair<Date, string> rhs);