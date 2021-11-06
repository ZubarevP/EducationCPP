#include "database.h"

void Database::Add (const Date& date, const string& event) {
    int a = 0;
    if (dateb.count(date)) {
      for(auto co : dateb[date]) {
        if ( co == event) {
            a = 1;
            break;
        }  
      }
    }
    if (a == 0) { 
        dateb[date].push_back(event);
    }
}
void Database::Print(ostream& stream) {
  for( auto ev : dateb) {
    for( auto evo : ev.second) {
      stream << ev.first << " " << evo << endl;
    }
  }
}
string Database::Last(const Date& date) {
  string str;
 auto iter = dateb.lower_bound(date);
  if (iter == dateb.begin()) {
    throw invalid_argument("No entries");
  } else {
    Date temp;
    temp = prev(iter)->first;
    str = temp.GetDate() + " ";
    str += dateb.at(prev(iter)->first).back();
  }
  return str;
}
string ParseEvent(istream& is) {
  string event;
  getline(is >> ws, event);
  return event;
}

ostream& operator<< (ostream& stream,  pair<Date, string> rhs) {
  stream << rhs.first << " " << rhs.second;
  return stream;
} 
