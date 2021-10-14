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
    bool Log = false;
    for(int i = 0; i < Q; i++) {
        cin >> first;
        if (first[0] == '*' && Log == true || first[0] == '/' && Log == true) {
            expression.push_front("(");
            expression.push_back(") ");
            first += " ";
            expression.push_back(first);
            cin >> first;
            expression.push_back(first);
            Log = false;
        } else {
            if(first[0] == '*' || first[0] == '/') {
                Log == false;
            } else {
                Log = true;
            }
            expression.push_back(" ");
            first += " ";
            expression.push_back(first);
            cin >> first;
            expression.push_back(first);
            
        }
    }
    
    for (auto LL : expression) {
        cout << LL;
    }
    cout << endl;
   return 0;
}
/*
8
11
* 2
* 2
+ -2
* 3
* 3
+ 2
 + 2 
 + 3
 * 3 
 + 3
 * 2

(((((8 * 2) * 2 + -2) * 3) * 3 + 2 + 2 + 3) * 3 + 3) * 2    #6/14
 ((((8 * 2) * 2 + -2) * 3 * 3 + 2 + 2 + 3) * 3 + 3) * 2     #9/14
((((8 * 2 * 2 + -2) * 3) * 3 + 2 + 2 + 3) * 3 + 3) * 2      #4/14
*/