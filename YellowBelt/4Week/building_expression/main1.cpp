#include <iostream>
#include <string>
#include <algorithm>
#include <deque>
#include <sstream>

using namespace std;

int main () {
    string first;
    int Q;
    cin >> first >> Q;
    if(Q == 0) {
        cout << first;
        return 0;
    }

    deque<string> expression;
    expression.push_back(first);
    for(int i = 0; i < Q; i++) {
        expression.push_front("(");
        expression.push_back(") ");
        cin >> first;
        first += " ";
        expression.push_back(first);
        cin >> first;
        expression.push_back(first);
    }
    
    for (auto LL : expression) {
        cout << LL;
    }
    cout << endl;
   return 0;
}