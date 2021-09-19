#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

int main () {
	double a;
	ifstream new_file ("input.txt");
	if(new_file.is_open()) {
		while (new_file >> a) {
			cout << setprecision(3) << fixed << a << endl;
		}
	}
	else cerr << "fail!";


	return 0;
}
//
