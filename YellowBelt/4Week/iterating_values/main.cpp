#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void Print (const vector<int>& for_print) {
    for(int i = for_print.size() - 1; i >= 0; i--) {
        cout << for_print[i] << " ";
    }
    cout << endl;
}

int main () {
    int a;
    cin >> a;
    vector<int> L;
    for (int i = 1; i < a + 1; i++) {
        L.push_back(i);
    }
    do {
        Print (L);
    }
    while (prev_permutation(rbegin(L), rend(L)));
    return 0;
}