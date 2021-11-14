#pragma once

#include <string>
using namespace std;

struct Date {
  int year, month, day;
};

struct Time {
  int hours, minutes;
};

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  int price;
};

bool operator< (const Date& lhs, const Date& rhs) {
  if (lhs.year != rhs.year) { return lhs.year < rhs.year; }
  else if (lhs.month != rhs.month) { return lhs.month < rhs.month; }
  return lhs.day < rhs.day;
}

bool operator== (const Date &lhs, const Date &rhs) {
  return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

ostream& operator<< (ostream& stream, const Date& date) {
  stream << to_string(date.year) << to_string('-') << to_string(date.month) << to_string('-') << to_string(date.day);
  return stream;
}

bool operator< (const Time& lhs, const Time& rhs) {
  if (lhs.hours != rhs.hours) {return lhs.hours < rhs.hours; }
  return lhs.minutes < rhs.minutes;
}

bool operator== (const Time &lhs, const Time &rhs) {
  return lhs.minutes == rhs.minutes && lhs.hours == rhs.hours;
}

ostream& operator<< (ostream& stream, const Time &time) {
  stream << to_string(time.hours) << to_string(':') << to_string(time.minutes);
  return stream;
}
