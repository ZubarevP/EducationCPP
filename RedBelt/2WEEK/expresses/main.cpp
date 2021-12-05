#include <iostream> 
#include <set>
#include <utility>
#include <string>
#include <map>
#include <iterator>

class Pair_of_start_and_finish {
public:
    void Add (const int &first, const int &second) {
        RouteList[first].insert(second);
        RouteList[second].insert(first);
    }
    void Go (const int &first, const int &second) {
        if (RouteList.count(first) && RouteList.at(first).count(second)) {
            std::cout << 0 << '\n';
        } else {
            int a, b;
            std::cout << std::min(minsum(first,second), abs(first - second)) << '\n';
            //std::cout << std::min(minsum(first,second),minsum(second,first)) << '\n';
        }
    }
    int minsum (const int& start, const int &finish) {
        if (!RouteList.count(start)) {
            return abs(finish - start);
        }
        auto point = RouteList.at(start).lower_bound(finish);
        if (point == RouteList.at(start).end()) {
            return abs(finish - *prev(point));
        } else if (point == RouteList.at(start).begin()) {
            return abs(finish - *point);
        } else {
            return std::min(abs(finish - *point), abs(finish - *prev(point)));
        }
    }
private:
    std::map<int, std::set<int>> RouteList;
};

int main () {
    std::cin.tie();
    std::ios_base::sync_with_stdio();

    uint Q;
    Pair_of_start_and_finish List;
    std::cin >> Q;
    for(uint i = 0; i < Q; i++) {
        std::string code;
        std::cin >> code;
        if (code == "ADD") {
            int start, finish;
            std::cin >> start >> finish;
            List.Add(start, finish);
        } else {
            std::cin.ignore();
            int start, finish;
            std::cin >> start >> finish;
            List.Go(start, finish);
        }
    }
    return 0;
}