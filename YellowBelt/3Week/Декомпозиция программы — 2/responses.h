#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <map>

struct BusesForStopResponse {
  std::vector<std::string> tobuses;
  std::string output;
};
struct StopsForBusResponse { 
  std::string output;
  std::string bus;
  std::vector<std::string> buses_to_stops;
  std::map<std::string, std::vector<std::string>> stops_to_buses;
};
struct AllBusesResponse {
  std::string output;
  std::map<std::string, std::vector<std::string>> buses_to_stops;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);