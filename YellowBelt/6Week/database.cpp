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
void Database::Print(ostream& stream) const {
  for( auto ev : dateb) {
    for( auto evo : ev.second) {
      stream << ev.first << " " << evo << endl;
    }
  }
}
string Database::Last(const Date& date) const {
  string str;
 auto iter = dateb.upper_bound(date);
  if (iter == dateb.begin()) {
    throw invalid_argument("No entries");
  } else {
    Date temp;
    temp = prev(iter)->first;
    str = temp.GetDate() + " " + dateb.at(temp).back();
  }
  return str;
}

int Database::RemoveIf(const function<bool(const Date&, const string&)> &kui) {
       int num = 0;
       for (auto& for_date : dateb) {
         int first_size = for_date.second.size();
         auto pos = stable_partition(for_date.second.begin(), for_date.second.end(),
                  [for_date, kui] (string &event) {
                    return !kui(for_date.first, event);
                  });
          int tempo = pos - for_date.second.begin();
          for_date.second.erase(pos, for_date.second.end());
          num += first_size - tempo;
        }
        vector<Date> key_to_del;
        for(auto& [date, events] : dateb) {
          if (events.empty()) {
            key_to_del.push_back(date);
          }
        }
        for (auto& key_er : key_to_del) {
          dateb.erase(key_er);
        }
       return num;
    }

vector<pair<Date, string>> Database::FindIf(const function<bool(const Date&, const string&)> &kui) const {
      vector<pair<Date, string>> date_event;
      for (auto for_date : dateb) {
        string l;
        auto pos = stable_partition(for_date.second.begin(), for_date.second.end(),
                  [for_date, kui] (string &event) {
                    return kui(for_date.first, event);
                  }
        );
        for_each(for_date.second.begin(), pos, [&for_date, &date_event] 
                (string& event) {
                  date_event.push_back(make_pair(for_date.first, event)); 
                } );
      }
      return date_event;
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
