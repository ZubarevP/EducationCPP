#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};
struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};
istream& operator >> (istream& is, Query& q) {
  string code;
  is >> code;
  if (code == "NEW_BUS") {
    int num;
    string st;
    q.type = QueryType::NewBus;
    is >> q.bus;
    is >> num;
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

struct BusesForStopResponse {
  vector<string> tobuses;
  string output;
};
ostream& operator << (ostream& os, const BusesForStopResponse& r) {
   if (r.output.empty()) {
     for (const string& bus : r.tobuses) {
        os << bus << " ";
        }
   } else {
      os << r.output;
   }
  return os;
}
struct StopsForBusResponse { 
  string output;
  string bus;
  vector<string> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
};
ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.output.empty()) {
      for (const string& stop : r.buses_to_stops) {
          os << "Stop " << stop << ": ";
          if (r.stops_to_buses.at(stop).size() == 1) {
            os << "no interchange";
          } else {
            for (const string& other_bus : r.stops_to_buses.at(stop)) {
              if (r.bus != other_bus) {
                os << other_bus << " ";
              }
            }
          }
        os << endl;
      }
    } else {
      os << "No bus";
    }
  return os;
}
struct AllBusesResponse {
  string output;
  map<string, vector<string>> buses_to_stops;
};
ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.output.empty()) {
          for (const auto& bus_item : r.buses_to_stops) {
          os << "Bus " << bus_item.first << ": ";
          for (const string& stop : bus_item.second) {
            os << stop << " ";
          }
          os << endl;
        }
  } else {
          os << "No buses";
  }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, vector<string>& stops) {
    Bus.insert({bus, stops});
    for (auto LL : stops) {
      Stop[LL].push_back(bus);
    }
    stops.clear();
  }
  BusesForStopResponse GetBusesForStop(const string& stop) const {
      BusesForStopResponse Ok;
      if (Stop.count(stop) == 0) {
        Ok.output = "No stop";
      } else {
        Ok.tobuses = Stop.at(stop);
        }
     return Ok;
  }
  StopsForBusResponse GetStopsForBus(const string& bus) const {
      StopsForBusResponse Ok;
      if (Bus.count(bus) == 0) {
        Ok.output = "No bus";
      } else {
        Ok.bus = bus;
        Ok.buses_to_stops = Bus.at(bus);
        Ok.stops_to_buses = Stop;
      }
      return Ok;
  }
  AllBusesResponse GetAllBuses() const {
      AllBusesResponse Ok;
      if (Bus.empty()) {
        Ok.output ="No buses";
      } else {
        Ok.buses_to_stops = Bus;
      }
      return Ok;
  }
private:
map<string, vector<string>> Bus;
map<string, vector<string>> Stop;
};


int main() {
  int query_count;
  Query q;
  cin >> query_count;
  BusManager bm;

  for (int i = 0; i < query_count; ++i) {
    cin >> q; 
    switch (q.type) {
    case QueryType::NewBus: 
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }
  return 0;
}
