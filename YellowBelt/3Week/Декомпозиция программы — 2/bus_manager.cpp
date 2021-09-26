#include "bus_manager.h"

using namespace std;

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops) {
    Bus.insert({bus, stops});
    for (auto LL : stops) {
      Stop[LL].push_back(bus);
    }
  }

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const {
      BusesForStopResponse Ok;
      if (Stop.count(stop) == 0) {
        Ok.output = "No stop";
      } else {
        Ok.tobuses = Stop.at(stop);
        }
     return Ok;
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
      AllBusesResponse Ok;
      if (Bus.empty()) {
        Ok.output ="No buses";
      } else {
        Ok.buses_to_stops = Bus;
      }
      return Ok;
}