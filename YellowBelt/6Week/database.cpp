#include "database.h"

    void Database::Add (const Date& date, const string& event) {
      int a;
       a = count(begin(db.at(date)), end(db.at(date)), event);
        /*-------------------------------------------
        возможный вариант замены
        int a = 0;
        fot(auto co : db.at(date)) {
          if ( co == event) {
              a = 1;
              break;
          }  
        }
        ----------------------------------------------*/
        if (a == 0) { 
            db[date].push_back(event);
        }
    }

    void Database::Print(ostream& stream) {
      for( auto ev : db) {
        for( auto evo : ev.second) {
          stream << ev.first << " " << evo << endl;
        }
      }
    }

    string Database::Last(const Date& date) {
      string str;
      auto iter = lower_bound(begin(db), end(db), date);
      if (iter == begin(db)) {
        throw invalid_argument("No entries");
      } else {
        Date temp;
        temp = prev(iter)->first;
        str = temp.GetDate() + " ";
        str += db.at(prev(iter)->first).back();
      }
      return str;
    }

    int Database::RemoveIf(auto);
    void Database::FindIf();

string ParseEvent(istream& is) {
  string event;
  getline(is >> ws, event);
  return event;
}