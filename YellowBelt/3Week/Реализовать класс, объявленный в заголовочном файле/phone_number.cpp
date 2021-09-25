#include "phone_number.h"
#include <stdexcept>


  PhoneNumber::PhoneNumber(const string &international_number) {
        size_t F, S;
        string one, two, tree;
        string number;
        number = international_number;
        if (number[0] == '+') {
            F = number.find('-');
            if (F > 1 || F < number.size()) {
                one = number.substr(1, F - 1);
                S = number.find('-', F + 1);
                if (S < number.size()) {
                    two = number.substr(F + 1, S - F - 1);
                        tree = number.substr(S + 1);
                        if (!tree.empty()) {
                            country_code_ = one;
                            city_code_ = two;
                            local_number_ = tree;
                        }
                        else {
                        throw invalid_argument("This is not phone number! #3");
                        }
                }
                else {
                throw invalid_argument("This is not phone number! #2");
                }
            }
            else {
                throw invalid_argument("This is not phone number! #1");
            }
        }
        else {
            throw invalid_argument("This is not phone number! First character is not plus.");
        }
//first option if first and second argument is number
/*        stringstream ss;
        ss << number;
        char Plus, Fmin, Smin;
        int one, two;
        if (ss >> Plus) {
            if (Plus == '+') {
                ss >> one;
                if (ss >> Fmin) {
                    if (Fmin == '-') {
                        ss >> two;
                        if (ss >> Smin) {
                            if (Smin == '-') {
                            string timly;
                            if (ss >> timly) {
                                country_code_ = to_string(one);
                                city_code_ = to_string(two);
                                local_number_ = timly;
                            }
                            }
                        }
                    }
                }
            }

        }*/
        

    }

  string PhoneNumber::GetCountryCode() const {
      return country_code_;
  }
  string PhoneNumber::GetCityCode() const {
      return city_code_;
  }
  string PhoneNumber::GetLocalNumber() const {
      return local_number_;
  }
  string PhoneNumber::GetInternationalNumber() const {
      string all;
      all = "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
      return all;
  }

/*class PhoneNumber {
public:
//second option: all arguments are string
    PhoneNumber(string& number){
        size_t F, S;
        string one, two, tree;
        if (number[0] == '+') {
            F = number.find('-');
            if (F > 1 || F < number.size()) {
                one = number.substr(1, F - 1);
                S = number.find('-', F + 1);
                if (S < number.size()) {
                    two = number.substr(F + 1, S - F - 1);
                        tree = number.substr(S + 1);
                        if (!tree.empty()) {
                            country_code_ = one;
                            city_code_ = two;
                            local_number_ = tree;
                        }
                        else {
                        throw invalid_argument("This is not phone number! #3");
                        }
                }
                else {
                throw invalid_argument("This is not phone number! #2");
                }
            }
            else {
                throw invalid_argument("This is not phone number! #1");
            }
        }
        else {
            throw invalid_argument("This is not phone number! First character is not plus.");
        }
//first option if first and second argument is number
        

    }
 
  explicit PhoneNumber(const string &international_number);

  string GetCountryCode() const {
      return country_code_;
  }
  string GetCityCode() const {
      return city_code_;
  }
  string GetLocalNumber() const {
      return local_number_;
  }
  string GetInternationalNumber() const{
      string all;
      all = "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
      return all;
  }
private:
  string country_code_;
  string city_code_;
  string local_number_;
};
*/