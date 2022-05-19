#pragma once 

#include "../project/storage.h"
#include "test_runner.h"

void Test_Storage() {
    {
        Storage storage;
        std::ostringstream output;
        {
            std::string line = "Bubabu";
            storage.Stop_Get_Ptr(line);
        }
        storage.Stops_Print(output);
        ASSERT_EQUAL(output.str(), "Bubabu: Bubabu, 0 - 0\n");

        Coordinates coo {45.345, 78.345};
        storage.Stop_Add_Coord("Bubabu", coo);
        std::stringstream out;
        storage.Stops_Print(out);
        ASSERT_EQUAL(storage.Stops_Size(), 1u);
        ASSERT_EQUAL(out.str(), "Bubabu: Bubabu, 45.345 - 78.345\n")
    }
    {
        Storage storage;
        auto n_bus = std::make_unique<Bus>();
        n_bus->name = "750";
        n_bus->unique = {"one", "two", "three"};
        storage.Bus_Add_New(move(n_bus));
        auto n_bus2 = std::make_unique<Bus>();
        n_bus2->name = "259";
        storage.Bus_Add_New(move(n_bus2));
        ASSERT_EQUAL(storage.Buses_Size(), 2u);
        auto bus750 = storage.Bus_Get_Ptr("750");
        ASSERT_EQUAL(bus750->unique.size(), 3u);
        ASSERT(storage.Bus_Has_Bus("259"));
    }
}