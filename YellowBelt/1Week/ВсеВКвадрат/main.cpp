#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <sstream>
#include <algorithm>

using namespace std;
//-------------------заголовки-------------------
template <typename Key, typename Value>  map<Key, Value> operator* (const map<Key, Value>& lhs, const map<Key, Value>& rhs);
template <typename Value> vector<Value> operator* (const vector<Value>& lhs, const vector<Value>& rhs);
template <typename First, typename Second> pair<First, Second> operator* (const pair<First, Second>& lhs, const pair<First, Second>& rhs);
template <typename Value> Value Sqr(Value a);
//--------------------шаблоны--------------------
// умножение словарей
template <typename Key, typename Value>  
map<Key, Value> operator* (const map<Key, Value>& lhs, const map<Key, Value>& rhs) {
	map<Key, Value> mhs;
	for (const auto& LL : lhs) {
		mhs.insert({LL.first, LL.second * LL.second});
	}
	return mhs;
}
// умножение вектора
template <typename Value> 
vector<Value> operator* (const vector<Value>& lhs, const vector<Value>& rhs) {
	size_t MinSize = min(lhs.size(), rhs.size());
	size_t MaxSize = max(lhs.size(), rhs.size());
	vector<Value> mhs;
	for (size_t i = 0; i < MinSize; i++) {
		mhs.push_back(lhs[i] * rhs[i]);
	}
	if (lhs.size() > rhs.size()) {
		for (size_t i = MinSize; i < MaxSize; i++) {
			mhs.push_back(lhs[i] * lhs[i]);
		}
	} else {
		for (size_t i = MinSize; i < MaxSize; i++) {
			mhs.push_back(rhs[i] * rhs[i]);
		}
	}
	return mhs;
}
// умножение пары
template <typename First, typename Second> 
pair<First, Second> operator* (const pair<First, Second>& lhs, const pair<First, Second>& rhs) {
	First n1 = lhs.first * rhs.first;
	Second n2 = lhs.second * rhs.second;
	return make_pair(n1, n2);
}
// в квадрат
template <typename Value> 
Value Sqr(Value a) {
	return a * a;
}
//--------------------тело--------------------
int main() {
	vector<int> v = {1, 2, 3};
cout << "vector:";
for (int x : Sqr(v)) {
  cout << ' ' << x;
}
cout << endl;

map<int, pair<int, int>> map_of_pairs = {
  {4, {2, 2}},
  {7, {4, 3}}
};
cout << "map of pairs:" << endl;
for (const auto& x : Sqr(map_of_pairs)) {
  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
}
	return 0;
}
