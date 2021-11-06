#include "date.h"

Date::Date(int Y, int M, int D) {
        string Ye, Mo, Da;
        Ye = to_string(Y);
        Mo = to_string(M);
        Da = to_string(D);
        Date::AddYear(Ye);
        Date::AddMounth(Mo);
        Date::AddDay(Da);
    }

string Date::GetDate() const {
        return date;
}

void Date::AddYear (const string& year) {
        if (year.size() == 1) {
            date = "000" + year + "-";
        } else if (year.size() ==  2) {
            date = "00" + year + "-";
        } else if (year.size() == 3) {
            date = "0" + year + "-";
        } else {
            date = year + "-";
        }
}

void Date::AddMounth (const string& mounth) {
        if (mounth.size() == 1) {
            date += "0" + mounth + "-";
        } else {
            date += mounth + "-";
        }
}

void Date::AddDay (const string& day) {
        if (day.size() == 1) {
            date += "0" + day;
        } else {
            date += day;
        }
}


Date ParseDate (istringstream& stream){
    Date date;
    string line, temp;
    stream >> line;
    auto Begin = begin(line);
    uint8_t num = 0; 
    for(uint8_t l = 0; l < 3; l++) {
        auto End = find(Begin, end(line), '-'); 
        string temp1(Begin, End);
        Begin = End + 1;
        if ( num == 0) {
            date.AddYear(temp1);
            ++num;
        } else if (num == 1) {
            date.AddMounth(temp1);
            ++num;
        } else {
            date.AddDay(temp1);
        }

    }
    return date;
}

ostream& operator<< (ostream& stream, Date date) {
    stream << date.GetDate();
    return stream;
}
bool operator== (const Date& lhs, const  Date& rhs) {
    return lhs.GetDate() == rhs.GetDate();
}
bool operator< (const  Date& lhs, const  Date& rhs) {
    return lhs.GetDate() < rhs.GetDate();
}
bool operator> (const  Date& lhs, const  Date& rhs) {
    return lhs.GetDate() > rhs.GetDate();
}
bool operator>= (const  Date& lhs, const  Date& rhs){
    return lhs.GetDate() >= rhs.GetDate();
}
bool operator<= (const  Date& lhs, const  Date& rhs) {
    return lhs.GetDate() <= rhs.GetDate();
}
bool operator!= (const Date& lhs, const  Date& rhs) {
    return lhs.GetDate() != rhs.GetDate();
}