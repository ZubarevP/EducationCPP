#include <iostream>
#include <map>
#include <exception>
#include <string>
#include <sstream>

using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict ( map<Key, Value>& Arr, const Key& K) {
	if (Arr.count(K)) { 
		return Arr[K];
	}
	else {
		throw runtime_error("Error");
	}
}

int main () {
map<int, string> m = {{0, "value"}};
string& item = GetRefStrict(m, 0);
item = "newvalue";
cout << m[0] << endl; // выведет newvalue

	return 0;
}