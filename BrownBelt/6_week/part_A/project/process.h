#pragma once 

#include "storage.h"

#include <cmath>

double
ConvertDgrToRad(double degree) {
    return degree * 3.1415926535 / 180.0;
}

double
DistBtwPoints(const Coordinates lhs, const Coordinates rhs) 
{
    return (acos(sin(lhs.latitude) * sin(rhs.latitude) +
                cos(lhs.latitude) * cos(rhs.latitude) *
                cos(fabs(lhs.longitude - rhs.longitude))
                ) * 6371000);
}

std::unique_ptr<Bus>
SplitRoute(Storage& storage, std::string_view line, std::string_view delimiter) {
    auto bus = std::make_unique<Bus>();
    while(!line.empty()) {
        auto [stop, tail] = SplitStrOpt(line, delimiter);

        bus->route.reserve(100);
        bus->route.push_back(storage.Stop_Get_Ptr(stop));
        bus->unique.insert(bus->route.back()->name);
        line = tail.value_or("");
    }
    //return move(bus);
    return bus;
}

std::unique_ptr<Bus>
CompleteLinerRoute(std::unique_ptr<Bus> bus) {
    if(bus->route.size() > 1) {
        for(int i = bus->route.size() - 2; i >= 0; --i) {
            bus->route.push_back(bus->route[i]);
        }
    }
    //return move(bus);
    return bus;
}

std::unique_ptr<Bus>
MakeRoute(Storage& storage, std::string_view line) {
    auto pos = line.find(">");
    if(pos == line.npos) {
        return move(CompleteLinerRoute(SplitRoute(storage, line, "-")));
    } else {
        return move(SplitRoute(storage, line, ">"));
    }
    return nullptr;
}