#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <array>
using namespace std;
 
class Stats {
public:
    Stats();
    void AddMethod(string_view method);
    void AddUri(string_view uri);
    const map<string_view, int>& GetMethodStats() const;
    const map<string_view, int>& GetUriStats() const;
private:
    map<string_view, int> _method;
    map<string_view, int> _uri;
    array<string_view, 11> _data {"GET", "PUT", "POST", "DELETE", "UNKNOWN", "/", "/order", "/product", "/basket", "/help", "unknown"};
    array<int*, 11> _points;
    void Build ();
};

HttpRequest ParseRequest(string_view line);