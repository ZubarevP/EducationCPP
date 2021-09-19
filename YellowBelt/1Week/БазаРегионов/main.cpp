#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

// enum class Lang {
//   DE, FR, IT
// };

// struct Region {
//   string std_name;
//   string parent_std_name;
//   map<Lang, string> names;
//   int64_t population;
// };
bool operator== (const Region& lhs, const Region& rhs) {
	if (lhs.names.size() != rhs.names.size()) {
	        return false;
	    }
	for (const auto& LL : lhs.names) {
		if (rhs.names.count(LL.first)) {
			if (LL.second != rhs.names.at(LL.first)) {
				return false;
			}
		}
		else {
			return false;
		}
	}
	return tie(lhs.std_name, lhs.parent_std_name, lhs.population) ==
		   tie(rhs.std_name, rhs.parent_std_name, rhs.population);
}
bool operator< (const Region& lhs, const Region& rhs) {
	return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
		   tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}
int FindMaxRepetitionCount (const vector<Region>& region) {
	int Max = 0;
	if (region.size() == 0) {
		return 0;
	} else {
		map<Region, int> MaxNum;
		for (auto LL : region) {
			++MaxNum[LL];
		}
		for (auto LL : MaxNum) {
			if (LL.second > Max) {
				Max = LL.second;
			}
		}
		return Max;
	}
}

int main(){
	vector<Region> reggi;
	cout << FindMaxRepetitionCount(reggi) << endl;

	cout << FindMaxRepetitionCount({
	      {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      },
		  {
		  	          "Moscow",
		  	          "Russia",
		  	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  	          89
		  	      }
	}) << endl;
cout << "-------------------------" << endl;
	cout << FindMaxRepetitionCount({
	      {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Russia",
	          "Eurasia",
	          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Russia",
	          "Eurasia",
	          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
	          89
	      },
	  }) << endl;

	  cout << FindMaxRepetitionCount({
	      {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Russia",
	          "Eurasia",
	          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Moscow",
	          "Toulouse",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          31
	      },
	  }) << endl;
	return 0;
}

