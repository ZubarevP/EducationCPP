#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <tuple>

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
  return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}
bool operator== (const Date &lhs, const Date &rhs) {
  return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}
ostream& operator<< (ostream& stream, const Date& date) {
  stream << date.year << "-" << date.month << "-" << date.day;
  return stream;
}
istream& operator>> (istream& stream, Date& date) {
  char l;
  stream >> date.year >> l >> date.month >> l >> date.day;
  return stream;
}
bool operator< (const Time& lhs, const Time& rhs) {
  return tie(lhs.hours, lhs.minutes) < tie(rhs.hours, rhs.minutes);
}
bool operator== (const Time &lhs, const Time &rhs) {
  return tie(lhs.minutes, lhs.hours) == tie(rhs.minutes, rhs.hours);
}
ostream& operator<< (ostream& stream, const Time &time) {
  stream << time.hours << ":" << time.minutes;
  return stream;
}
istream& operator>> (istream& stream, Time &time) {
  char l;
  stream >> time.hours >> l >> time.minutes;
  return stream;
}