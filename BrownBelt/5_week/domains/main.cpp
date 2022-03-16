#include "test_runner.h"

#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <string_view>

using namespace std;

void Print (vector<bool> result, ostream& output = cout) {
    for(const auto& boo : result) {
        switch(boo) {
            case true  : output << "Good\n"; break;
            case false : output << "Bad\n" ; break;
        }
    }
}

vector<string> ReadStream (istream& input = cin) {
    size_t num;
    input >> num;

    vector<string> result;
    result.reserve(num);

    string domain;
    for(size_t i = 0; i < num; ++i) {
        input >> domain;
        reverse(begin(domain), end(domain));
        result.push_back(move(domain));
    }

    return move(result);
}

bool IsSubdomain(const string& bad, const string_view line) {
    if(bad.size() <= line.size()) {
        size_t min_size = min(bad.size(), line.size());
        size_t i = 0;

        for( ; i < min_size; i++) {
            if(bad[i] != line[i]) return false;
        }
        if(bad.size() == line.size()) return true;
        if(line[i] != '.') return false;
     
        return true;
    }
    return false;
}

template <typename Iter>
bool CheckLine (pair<Iter, Iter> dist, const string_view line) {
    for(Iter start = dist.first ; start != dist.second; start++ ) {

        if(IsSubdomain(*start, line)) return false;

    }
    return true;
}

vector<bool> GetList (const vector<string>& banned, const vector<string>& domains) {
    vector<bool> result;

    for(const string_view domain : domains) {
        auto start  = lower_bound(
            banned.begin(), banned.end(), 
            domain.substr(0, domain.find('.'))
        );
        auto finish = upper_bound(
            banned.begin(), banned.end(),  
            domain
        );

        auto iters = make_pair(start, finish);
        result.push_back(CheckLine(iters, domain));
    }

    return move(result);
}

int main() {

    vector<string> banned = [] {
        vector<string> temp(ReadStream());
        sort(begin(temp), end(temp));
        return move(temp);
    }();
    
    vector<string> domain_to_check(ReadStream());

    Print(GetList(banned, domain_to_check));

    return 0;
}