#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class ReversibleString {
public:
	ReversibleString() {
	word.resize(0);
	};
	ReversibleString(const string& new_word) {
		word = new_word;
	}
void Reverse() {
		reverse(word.begin(), word.end());
	}
string ToString() const {
	return word;
	}
private:
string word;
};

int main() {
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;

  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;

  ReversibleString empty;
  cout << '"' << empty.ToString() << '"' << endl;

  return 0;
}
