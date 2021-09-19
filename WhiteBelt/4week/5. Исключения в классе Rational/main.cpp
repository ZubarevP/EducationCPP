#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <stdexcept>

using namespace std;

class Rational {
public:
	Rational() {
		up = 0;
		down = 1;
	}
	Rational(int numerator, int denominator) {
		if (!denominator) {
			throw invalid_argument ("Sorry, denominator is invalid argument");
		}
		int NOD = 0;
		int A = max(numerator, denominator);
		int B = min(denominator,numerator);
		while (B != 0)  {
			int t = B;
			B = A % B;
			A = t;
			NOD = A;
		}
		if(numerator) {
			if (numerator < 0 && denominator < 0) {
				up = abs(numerator / NOD);
				down = abs(denominator / NOD);
			}
			else if (denominator < 0) {
				up = -numerator / abs(NOD);
				down = abs(denominator / NOD);
			}
			else {
				up = numerator / abs(NOD);
				down = denominator / abs(NOD);
			}
		}
		else {
			up = 0;
			down = 1;
		}

	}
	int Numerator() const {
		return up;
	}
	int Denominator() const {
		return down;
	}

private:
	int up;
	int down;
};

Rational operator+ (const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() == rhs.Denominator()) {
		return Rational(lhs.Numerator() + rhs.Numerator(), lhs.Denominator());
	}
	return Rational (lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}
Rational operator- (const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() == rhs.Denominator()) {
		return Rational(lhs.Numerator() - rhs.Numerator(), lhs.Denominator());
	}
	return Rational (lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}
Rational operator* (const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}
Rational operator/ (const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) {
		throw domain_error ("domain_error");
	}
	return Rational(lhs.Numerator() * rhs.Denominator(), rhs.Numerator() * lhs.Denominator());
}
bool operator< (const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() == rhs.Denominator())
		return lhs.Numerator() < rhs.Numerator();
	else {
		return lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator();
	}

}
bool operator> (const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() == rhs.Denominator())
		return lhs.Numerator() > rhs.Numerator();
	else {
		return lhs.Numerator() * rhs.Denominator() > rhs.Numerator() * lhs.Denominator();
	}

}
bool operator== (const Rational& lhs, const Rational& rhs) {
	if (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator()) {
		return true;
	}
	return false;
}
istream& operator>> (istream& stream, Rational& val) {
	int a, b;
	char c;
	if (stream >> a && stream >> c && stream >> b) {
		if (c == '/'){
			val = {a, b};
		}
	}
	return stream;
}

ostream& operator<< (ostream& stream, const Rational& val) {
	stream << val.Numerator() << "/" << val.Denominator();
	return stream;
}
int main () {
	try {
	        Rational r(1, 0);
	        cout << "Doesn't throw in case of zero denominator" << endl;
	        return 1;
	    } catch (invalid_argument&) {
	    }

	    try {
	        auto x = Rational(1, 2) / Rational(0, 1);
	        cout << "Doesn't throw in case of division by zero" << endl;
	        return 2;
	    } catch (domain_error&) {
	    }

	    cout << "OK" << endl;

	return 0;
}
