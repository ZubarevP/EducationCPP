#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <ctime>
#include <iterator>
#include <sstream>

using namespace std;

static int ONE_DAY = (60 * 60 * 24);

////////////////////////////////////////////////////////////////////////
template <typename Iter>
class RBF{
public:
    explicit
    RBF(Iter first, Iter last) 
        : one(first)
        , two(last)
    {
    }

    auto begin() const {return one;}
    auto begin() {return one;}
    auto end() const {return two;}
    auto end() {return two;}

private:
    Iter one;
    Iter two;
};

////////////////////////////////////////////////////////////////////////
struct Date {
    time_t _time;

    Date() = default;
    Date(time_t _time_)
        : _time(_time_)
    {
    }

    Date(int year_, int mon_, int day_)
        : _time(AsTimeStamp(year_, mon_, day_))
    {
    }

    time_t AsTimeStamp(int year_, int mon_, int day_, int dst_ = 0) {
        tm t;
        t.tm_sec = 0;
        t.tm_min = 0;
        t.tm_hour = 0;
        t.tm_mday = day_;
        t.tm_mon = mon_ - 1;
        t.tm_year = year_ - 1900;
        t.tm_isdst = dst_;
        return mktime(&t);
    }

    Date& Add(int year_, int mon_, int day_) {
        _time = AsTimeStamp(year_, mon_, day_);
        return *this;
    }
    
    bool operator< (const Date& other) const {
        return _time < other._time;
    }

    bool operator== (const Date& other) const{
        return _time == other._time;
    }

    ~Date() = default;
};

istream& operator>> (istream& input, Date& date) {
    int year, mon, day;
    input >> year;
    input.ignore(1);
    input >> mon;
    input.ignore(1);
    input >> day;
    date.Add(year, mon, day);
    return input;
}


////////////////////////////////////////////////////////////////////////
struct Range{
    Date first;
    Date second;
};

istream& operator>> (istream& input, Range& range) {
    input >> range.first >> range.second;
    return input;
}


////////////////////////////////////////////////////////////////////////
struct Money {
    double earn = 0.0;
    double spend = 0.0;
};

////////////////////////////////////////////////////////////////////////
class Budget {
public:
    Budget()
        : first(2000, 01, 01)
        , last(2100, 01, 01)
    {
        storage[first];
        storage[last];
    }

    using Iterator = map<Date, Money>::iterator;

    Budget& Spend(Range range, istream& input = cin) {
        double spend_money;
        input >> spend_money;

        spend_money = spend_money * ONE_DAY / difftime(range.second._time, range.first._time);

        for(auto& period : MakeRange(range.first, range.second)) {
            period.second.spend += spend_money;
        }
        return *this;
    }

    Budget& ComputeIncome(Range range, ostream& output = cout) {
        double result = 0.0;

        auto start = storage.find(range.first);
        auto finish = storage.find(range.second);

        for( ; start != finish; start++) {
            auto dist = difftime(next(start)->first._time, start->first._time) / 
                        ONE_DAY;
            result += start->second.earn * dist;
            result -= start->second.spend * dist;
        }

        output << result << '\n';
        return *this;
    }

    Budget& Earn(Range range, istream& input = cin){
        double value;
        input >> value;

        value = value * ONE_DAY / difftime(range.second._time, range.first._time);

        for(auto& period : MakeRange(range.first, range.second)) {
            period.second.earn += value;
        }
        return *this;
    }

    Budget& PayTax(Range range, istream& input = cin) {
        int tax;
        input >> tax;
        
        for(auto& period : MakeRange(range.first, range.second)) {
            period.second.earn = period.second.earn * (100 - tax) / 100;
        }
        return *this;
    }

    Range MakePoints(istream& input = cin) {
        Range range;
        input >> range;
        range.second._time += + ONE_DAY;
        AddTimePoint(range.first);
        AddTimePoint(range.second);
        return range;
    }

    map<Date, Money>& Get() {
        return storage;
    }

private:
    Date first, last;
    map<Date, Money> storage;

    void AddTimePoint(const Date& date) {
        if(!storage.count(date)) {
            auto it = storage.lower_bound(date);
            Money money = prev(it)->second;
            storage[date] = money;
        } 
    }
    
    RBF<Iterator> MakeRange(const Date& lhs, const Date& rhs) {
        auto left  = storage.find(lhs);
        auto right = storage.find(rhs);
        return RBF<Iterator>(left, right);
    }

    
};

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


int main () {

    cout.precision(25);
    Budget budget;
    int num;
    cin >> num;
    
    for(int i = 0; i < num; ++i) {
        string command;
        cin >> command;

        if(command == "ComputeIncome") {
            budget.ComputeIncome(budget.MakePoints());
        }
        else if (command == "Earn") {
            budget.Earn(budget.MakePoints());
        }
        else if (command == "PayTax") {
            budget.PayTax(budget.MakePoints());
        } 
        else if (command == "Spend") {
            budget.Spend(budget.MakePoints());
        }
    }
    
    return 0;
}