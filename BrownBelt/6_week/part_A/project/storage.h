#pragma once 

#include <string_view>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <utility>

struct Coordinates {
    double latitude;
    double longitude;
};

struct Stop {
    std::string name;
    Coordinates coord;
};

struct Bus {
    std::string name;
    std::vector<std::shared_ptr<Stop>> route;
    std::unordered_set<std::string_view> unique;
};

class Storage {
public:
    Storage() = default;
    ~Storage() = default;

    std::shared_ptr<Stop>
    Stop_Get_Ptr(std::string_view name) 
    {
        if(!stops.count(name)) {
            auto n_stop = std::make_unique<Stop>();
            n_stop->name =  move(name);
            stops[n_stop->name] = move(n_stop);
        }
        return stops.at(name);
    }

    void
    Stop_Add_Coord(std::string_view name, Coordinates coo) 
    {
        auto stop = Stop_Get_Ptr(name);
        stop->coord = coo;
    }

    bool
    Bus_Has_Bus(std::string_view name) const 
    {
        return buses.count(name);
    }
    
    void 
    Bus_Add_New(std::unique_ptr<Bus> n_bus)
    {
        buses[n_bus->name] = move(n_bus);
    }

    const std::shared_ptr<Bus>
    Bus_Get_Ptr(std::string_view name) const
    {
        if(Bus_Has_Bus(name)) {
            return buses.at(name);
        }
        return nullptr;
    }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
    void                                                                    ////
    Stops_Print(std::ostream& output = std::cout)                           //// 
    {                                                                       ////
        for(const auto& stop : stops) {                                     ////
            output  << stop.first << ": " << stop.second->name << ", "      //// 
                    << stop.second->coord.latitude << " - "                 ////
                    <<stop.second->coord.longitude << std::endl;            ////
        }                                                                   ////
                                                                            //// 
    }                                                                       ////
    size_t                                                                  ////
    Stops_Size() {return stops.size();}                                     ////

    void
    Buses_Print(std::ostream& output = std::cout)
    {
        for(const auto& bus : buses) {
            output  << bus.first << ": "
                    << bus.second->name << ", ";
            for(const auto& stop : bus.second->route) {
                output << stop->name << ", ";
            }
            output << "|| unique size - " << bus.second->unique.size() 
            << std::endl;
        }
    }
                                                                            ////
    size_t                                                                  //// 
    Buses_Size() {return buses.size();}                                     ////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
private:
    std::unordered_map<std::string_view, std::shared_ptr<Stop>> stops;
    std::unordered_map<std::string_view, std::shared_ptr<Bus>> buses;
};