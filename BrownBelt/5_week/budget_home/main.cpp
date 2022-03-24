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
    double value = 0.0;
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

    void ComputeIncome(istream& input = cin, ostream& output = cout) {
        Range range;
        input >> range;
        double result = 0.0;

        Date second(range.second._time + ONE_DAY);
        AddTimePoint(range.first);
        AddTimePoint(second);

        auto start = storage.find(range.first);
        auto finish = storage.find(second);

        for( ; start != finish; start++) {
            auto dist = difftime(next(start)->first._time, start->first._time) / 
                        ONE_DAY;
            result += start->second.value * dist;
        }

        output << result << '\n';
    }

    void Earn(istream& input = cin){
        Range range;
        double value;
        input >> range >> value;

        Date second(range.second._time + ONE_DAY);
        AddTimePoint(range.first);
        AddTimePoint(second);

        value = value * ONE_DAY / difftime(second._time, range.first._time);

        for(auto& period : MakeRange(range.first, second)) {
            period.second.value += value;
        }
    }

    void PayTax(istream& input = cin) {
        Range range;
        input >> range;
        
        Date second(range.second._time + ONE_DAY);
        AddTimePoint(range.first);
        AddTimePoint(second);
        
        for(auto& period : MakeRange(range.first, second)) {
            period.second.value *= 0.87;
        }
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
//void TestDate();
//void TestRange();
//void TestBudget();

int main () {
    //TestRunner tr;
    //RUN_TEST(tr, TestDate);
    //RUN_TEST(tr, TestRange);
    //RUN_TEST(tr, TestBudget);
    cout.precision(25);
    Budget budget;
    int num;
    cin >> num;
    
    for(int i = 0; i < num; ++i) {
        string command;
        cin >> command;
        if(command == "ComputeIncome") {
            budget.ComputeIncome();
        }
        else if (command == "Earn") {
            budget.Earn();
        }
        else if (command == "PayTax") {
            budget.PayTax();
        }
    }
    
    return 0;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

//void TestDate() {
//    Date one(2022, 01, 31);
//    Date two(2022, 02, 01);
//    ASSERT(one < two);
//    Date three;
//    three.Add(2022, 02, 01);
//    one._time += ONE_DAY;
//    ASSERT(one == two);
//    ASSERT(three == two);
//
//    istringstream input {"2022-02-01"};
//    Date four;
//    input >> four;
//    ASSERT(two == four);
//}
//
//void TestRange() {
//    istringstream input {"2022-02-01 2022-02-03 2022-02-01 2022-02-03"};
//    Range range;
//    Date first, last;
//    input >> range >> first >> last;
//    ASSERT(range.first == first);
//    ASSERT(range.second == last);
//}
//
//void TestBudget() {
//    ostringstream output;
//    istringstream input {
//        "2020-06-01 2020-06-30 300\n"
//        "2020-06-30 2020-06-30 10\n"
//        "2000-01-01 2099-12-31\n"
//        "2020-06-29 2020-06-30\n"
//        "2000-01-01 2099-12-31\n"
//        "2000-01-01 2099-12-31\n"
//        "2019-06-01 2019-06-30\n"
//        "2019-06-01 2019-06-30\n"
//        "2000-01-01 2099-12-31\n"
//    };
//    Budget budget;
//    budget.Earn(input);
//    budget.Earn(input);
//    ASSERT_EQUAL(budget.Get()[Date(2020, 06, 01)].value, 10);
//    ASSERT_EQUAL(budget.Get()[Date(2020, 06, 30)].value, 20);
//    ASSERT_EQUAL(budget.Get().size(), 5);
//
//    budget.ComputeIncome(input, output);
//    budget.ComputeIncome(input, output);
//    budget.PayTax(input);
//    budget.ComputeIncome(input, output);
//    budget.PayTax(input);
//    budget.ComputeIncome(input, output);
//    budget.ComputeIncome(input, output);
//    ASSERT_EQUAL(output.str(), "310\n30\n269.7\n0\n269.7\n");
//}
//
//
///*
//
//20
//18.96
//28.96
//27.2076
//
//*/