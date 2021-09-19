#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <stdexcept>
#include <exception>

using namespace std;

string AskTimeServer();

class TimeServer {
public:
	string GetCurrentTime(){
		try {
			last_fetched_time = AskTimeServer();
		}
		catch (system_error& error) {

			return last_fetched_time;
		}
		return last_fetched_time;
	}
private:
	string last_fetched_time = "00:00:00";
};
