#pragma once
#include <stdexcept>
#include <utility>

namespace RAII {

    template <typename T>
    class Booking {
    public:
        Booking() = default;
        Booking(T* prov_, int count_) 
            : prov (prov_)
            , count (count_)
        {
        }

        Booking(const Booking&) = delete;
        Booking(Booking&& other) 
            : prov(std::move(other.prov))
            , count (other.count)
        {
            prov->counter++;
        }

        Booking& operator= (const Booking&) = delete;
        Booking& operator= (Booking&& other) = default;

        ~Booking() {
            if(prov) {
                prov->CancelOrComplete(*this);
            }
        }

    private:
        T* prov;
        int count;
    };

}