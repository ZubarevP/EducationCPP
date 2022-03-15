#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class ReadingManager {
public:
    ReadingManager()
        : users(MAX_USER_COUNT_ + 1, -1)
        , pages(MAX_BOOK_PAGE + 1, 0)
    {}

    void Read(int id, int page) {
        if(users[id] < 0) {
            counter++;
            Flag(1, page);
        } else {
            Flag(users[id] + 1, page);
        }
        users[id] = page;
    }

    double Cheer(int id) const {

        const int last_page = users[id];
        const int more = pages[last_page];

        if(counter == 1 && more == 1) return 1;
        if(counter == 0 || users[id] < 0 || more == counter) return 0;
        return ((counter - more) / (counter * 1.0 - 1) );
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_BOOK_PAGE = 1'000;

    vector<int> users;
    vector<int> pages;
    
    int counter = 0;

    void Flag(int start, int finish) {
        for( int i = start; i <= finish; ++i) {
            pages[i]++;
        }
    }
};


int main() {
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}