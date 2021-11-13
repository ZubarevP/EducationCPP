#include "database.h"

void Database::Add (const Date& date, const string& event) {
    if (!eventb.count(event) || !eventb[event].count(date)) {
    dateb[date].push_back(event);
    eventb[event].insert(date);
    }
}
void Database::Print(ostream& stream) const {
  for( auto& ev : dateb) {
    for( auto& evo : ev.second) {
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
    str = prev(iter)->first.GetDate() + " " + dateb.at(prev(iter)->first).back();
  }
  return str;
}

int Database::RemoveIf(const function<bool(const Date&, const string&)> &kui) {
       int num = 0;
       vector<Date> key_to_del;
       for (auto& for_date : dateb) {
         int first_size = for_date.second.size();
         auto pos = stable_partition(for_date.second.begin(), for_date.second.end(),
                  [for_date, kui] (string &event) {
                    return !kui(for_date.first, event);
                  });
          int tempo = pos - for_date.second.begin();

          for (auto iter = pos; iter < for_date.second.end(); ++iter) {
            eventb[*iter].erase(for_date.first);
          }

          for_date.second.erase(pos, for_date.second.end());
          num += first_size - tempo;
          if(for_date.second.empty()) {
            key_to_del.push_back(for_date.first);
          }
        }
        for (auto& key_er : key_to_del) {
          dateb.erase(key_er);
        }
       return num;
    }

vector<pair<Date, string>> Database::FindIf(const function<bool(const Date&, const string&)> &kui) const {
      vector<pair<Date, string>> date_event;
        for ( auto for_date : dateb) {
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
