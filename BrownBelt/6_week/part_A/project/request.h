#pragma once

#include "storage.h"
#include "parse.h"
#include "process.h"

#include <iostream>
#include <iomanip>
#include <memory>
#include <unordered_map>

struct Request;
using RequestHolder = std::unique_ptr<Request>;

struct Request {
    enum class Type {
        BUS_ADD,
        BUS_READ,
        STOP_ADD,
    };
    Request(Type type_) 
        : type(type_)
    {}
    
    static RequestHolder Create(Type type);
    virtual void ParseForm(std::string_view) = 0;
    virtual ~Request() = default;
    
    Type type;
};

static const std::unordered_map<std::string_view, Request::Type> STR_TO_TYPE_MODIFY = {
    {"Bus", Request::Type::BUS_ADD},
    {"Stop", Request::Type::STOP_ADD},
};

static const std::unordered_map<std::string_view, Request::Type> STR_TO_TYPE_READ = {
    {"Bus", Request::Type::BUS_READ},
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

struct ReadRequest : Request {
    using Request::Request;
    virtual void ParseForm(std::string_view) = 0;
    virtual void Process(Storage&, std::ostream& = std::cout) const = 0;
};

struct ModifyRequest : Request {
    using Request::Request;
    virtual void ParseForm(std::string_view) = 0;
    virtual void Process(Storage& storage) = 0;
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
struct Stop_Add : ModifyRequest {
    Stop_Add()
        : ModifyRequest(Request::Type::STOP_ADD)
    {}
    virtual void ParseForm(std::string_view line) override {
        auto [name_, coords_] = SplieStrStr(line, ":");
        auto [latitude, longitude] = SplieStrStr(line, ",");
        name = move(name_);
        coord = {
            ConvertDgrToRad(ConvertStrToDbl(latitude)), 
            ConvertDgrToRad(ConvertStrToDbl(longitude))
                };
    }
    virtual void Process(Storage& storage) override {
        storage.Stop_Add_Coord(name, coord);
    }
    
    std::string name;
    Coordinates coord;
};

struct Bus_Add : ModifyRequest {
    Bus_Add()
        : ModifyRequest(Request::Type::BUS_ADD) 
    {}

    virtual void ParseForm(std::string_view line) override {
        auto [head, tail] = SplieStrStr(line, ":");
        name = move(head);
        route = move(tail);
    }

    virtual void Process(Storage& storage) override {
        auto bus = MakeRoute(storage, route);
        bus->name = move(name);
    }

    std::string name;
    std::string route;
};

struct Bus_Read : ReadRequest {
    Bus_Read()
        : ReadRequest(Request::Type::BUS_READ)
    {}

    virtual void ParseForm(std::string_view line) override {
        name = move(line);
    }
    virtual void Process(Storage& storage, std::ostream& output = std::cout) const override {
        auto bus = storage.Bus_Get_Ptr(name);

        double route_length = 0.0;
        for(size_t i = 1; i < bus->route.size(); ++i) {
            route_length += DistBtwPoints(bus->route[i - 1]->coord, bus->route[i]->coord);
        }

        output  << std::setprecision(6)
                <<  "Bus " << name << ": "  
                << bus->route.size() <<" stops on route, " 
                << bus->unique.size() << " unique stops, "
                << route_length << " route length\n";
    }

    std::string name;
};

RequestHolder Request::Create(Request::Type type) {
    switch(type) {
        case Request::Type::BUS_ADD : 
            return std::make_unique<Bus_Add>(); break;
        case Request::Type::BUS_READ :
            return std::make_unique<Bus_Read>(); break;
        case Request::Type::STOP_ADD :
            return std::make_unique<Stop_Add>(); break;
        default :
            return nullptr;
    }
}