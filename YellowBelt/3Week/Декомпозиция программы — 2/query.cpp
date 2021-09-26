#include "query.h"

using namespace std;

std::istream& operator >> (std::istream& is, Query& q) {
  std::string code;
  is >> code;
  if (code == "NEW_BUS") {
    int num = 0;
    std::string st;
    q.type = QueryType::NewBus;
    is >> q.bus;
    is >> num;
    q.stops.resize(num);
    for(size_t i = 0; i < num; i++) {
      is >> st;
      q.stops.push_back(st);
    }    
  } else if (code == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  } else if (code ==  "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  } else if (code == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }
  return is;
}
