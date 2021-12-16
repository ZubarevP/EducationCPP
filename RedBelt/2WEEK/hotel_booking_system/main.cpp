#include <iostream>
#include <map>
#include <string>
#include <deque>

using namespace std;

struct All {
    long long time_;
    string hotel_name_;
    int client_id_;
    uint16_t room_count;
};

class Booking_manager {
public:
    int Num_of_booking_rooms (const string &hotel_name) const {
        if (hotel_to_room.count(hotel_name)) {
            return hotel_to_room.at(hotel_name);
        }
        return 0;
    }

    int Num_of_clients (const string &hotel_name) const {
       if(hotel_to_client.count(hotel_name)) {
           return hotel_to_client.at(hotel_name).size();
       }
       return 0;
    }

    void Add_booking(const long long &time, const string &hotel_name,const int &client_id, const uint16_t &room_count) {
        all_values.push_back({time, hotel_name, client_id, room_count});
        
        hotel_to_room[hotel_name] += room_count;
        hotel_to_client[hotel_name][client_id] += room_count;

        while(all_values.front().time_ <= all_values.back().time_ - 86400) {
            string *value_hotel_name = &all_values.front().hotel_name_;
            int *value_hotel_client = &all_values.front().client_id_;
            //удаление комнат
            hotel_to_room[*value_hotel_name] -= all_values.front().room_count;
            //удаление клиентов
            auto *iter = &hotel_to_client[*value_hotel_name][*value_hotel_client];
            *iter -= all_values.front().room_count;
            if (*iter == 0) {
                hotel_to_client[*value_hotel_name].erase(*value_hotel_client);
            }
            //удаление неактуального события
            all_values.pop_front();
        }
    }
private:
  deque<All> all_values;
  map<string, int> hotel_to_room;
  map<string, map<int, uint16_t>> hotel_to_client;
};



int main (){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_of_request;
    cin >> num_of_request;
    string code;
    Booking_manager manager;
    for (int i = 0; i < num_of_request; i++) {
        cin >> code;
        if (code == "BOOK") {
            long long time;
            string hotel_name;
            int client_id;
            uint16_t room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            manager.Add_booking(time, hotel_name, client_id, room_count);
        } else if (code == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Num_of_clients(hotel_name) << "\n";
        } else if (code == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Num_of_booking_rooms(hotel_name) << "\n";
        }
    }
    return 0;
}
