#pragma once

#include "../project/process.h"
#include "test_runner.h"

void Test_Process() {
    {
        std::vector<Coordinates> route = {
            {55.611087, 37.20829},
            {55.595884, 37.209755},
            {55.632761, 37.333324},
            {55.595884, 37.209755}, 
            {55.611087, 37.20829}
        };

        for(auto& co : route) {
            co.latitude = ConvertDgrToRad(co.latitude);
            co.longitude = ConvertDgrToRad(co.longitude);
        };

        double result = 0.0;

        for(size_t i = 1; i < route.size(); ++i) {
            result += DistBtwPoints(route[i - 1], route[i]);
        }
        ASSERT(result < 20939.6 && result > 20939.4);
    }
    {
        Storage storage;
        std::string line = "Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya";
        auto bus = SplitRoute(storage, line, ">");
        ASSERT_EQUAL(bus->route.size(), 5u);
        ASSERT_EQUAL(bus->unique.size(), 5u);
        ASSERT_EQUAL(bus->route.front()->name, "Biryulyovo Zapadnoye");
        ASSERT_EQUAL(bus->route.back()->name, "Biryulyovo Passazhirskaya");

        auto bus2 = CompleteLinerRoute(move(bus));
        ASSERT_EQUAL(bus2->route.size(), 9u);
        ASSERT_EQUAL(bus2->route[6]->name, "Universam");

        std::string line2 = "Biryusinka > Universam";
        auto bus3 = SplitRoute(storage, line2, ">");
        auto bus30 = CompleteLinerRoute(move(bus3));
        ASSERT_EQUAL(bus30->route.size(), 3u);

        std::string line3 = "Biryusinka";
        auto bus4 = SplitRoute(storage, line3, ">");
        auto bus40 = CompleteLinerRoute(move(bus4));
        ASSERT_EQUAL(bus40->route.size(), 1u);
    }
    {
        Storage storage;
        std::string line = "Tolstopaltsevo - Marushkino - Rasskazovka";
        std::string line2 = "Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye";
        auto bus1 = MakeRoute(storage, line);
        auto bus2 = MakeRoute(storage, line2);
        ASSERT_EQUAL(bus1->route.size(), 5u);
        ASSERT_EQUAL(bus2->route.size(), 6u);
    }
}