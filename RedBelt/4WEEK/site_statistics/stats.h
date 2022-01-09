#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <array>
using namespace std;
 
class Stats {
public:
    void AddMethod(string_view method);
    void AddUri(string_view uri);
    const map<string_view, int>& GetMethodStats() const;
    const map<string_view, int>& GetUriStats() const;
private:
};

HttpRequest ParseRequest(string_view line) {
  HttpRequest pars;
  pars.method = line.substr(0, line.find(' '));
  line.remove_prefix(line.find('/'));
  pars.protocol = line.substr(0, line.find(' '));
  line.remove_prefix(line.rfind(' ') + 1);
  pars.uri = line.substr();
  return pars;
}
