#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <exception>

using namespace std;

struct Date {
	int year;
	int month;
	int day;
};


void EnsureNextSimbolAndSkip(stringstream& stream) {
	if (stream.peek() != '/') {
		stringstream ss;
		ss << "expected / , but has: " << char(stream.peek());
				throw runtime_error(ss.str());
		}
	stream.ignore(1);
}
Date ParseDate (const string& s){
	stringstream stream(s);
	Date date;
	stream >> date.year;
	EnsureNextSimbolAndSkip(stream);
	stream >> date.month;
	EnsureNextSimbolAndSkip(stream);
	stream >> date.day;
	return date;
}

int main () {
	string date_str = "2021a08/28";
try {
	Date date = ParseDate(date_str);
	cout << setw(4) << setfill('0') << date.year << "."
			<< setw(2) << setfill('0') << date.month << "."
			<< setw(2) << setfill('0') << date.day;
} catch (exception& ex) {
	cout << "exception happens: " << ex.what();
}

	return 0;
}
