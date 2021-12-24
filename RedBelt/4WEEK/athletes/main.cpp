#include "profile.h"
#include <iostream>
#include <list>
#include <vector>

int main() {
    size_t sum;
    std::cin >> sum;

    std::list<int> lister;
    std::vector<std::list<int>::iterator> ptr (100001, lister.end());
    for (size_t i = 0; i < sum; ++i) {
        int player1, player2; 
        std::cin >> player1 >> player2;
        ptr[player1] = lister.insert(ptr[player2], player1);
    }

    for ( auto & ll : lister) {
        std::cout << ll << "\n";

    return 0;
}