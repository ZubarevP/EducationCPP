#include "stats.h"
 
    Stats::Stats(){Build();}

    void Stats::AddMethod(string_view method) {
      if(method == "GET") {
        ++*_points[0];
      } else if (method == "PUT") {
        ++*_points[1];
      } else if (method == "POST") {
        ++*_points[2];
      } else if (method == "DELETE") {
        ++*_points[3];
      } else {
        ++*_points[4];
      }
    }

    void Stats::AddUri(string_view uri) {
      if (uri == "/") {
        ++*_points[5];
      } else if (uri ==  "/order") {
        ++*_points[6];
      } else if (uri == "/product") {
        ++*_points[7];
      } else if (uri == "/basket") { 
        ++*_points[8];
      } else if (uri == "/help") {
        ++*_points[9];
      } else {
        ++*_points[10];
      }
    }
    const map<string_view, int>& Stats::GetMethodStats() const {
      return _method;
    }
    const map<string_view, int>& Stats::GetUriStats() const {
      return _uri;
    }
    void Stats::Build () {
      size_t i = 0; 
      for ( ; i < 5; i++) {
        auto [iter, bo]  = _method.insert({_data[i], 0});
        _points[i] = &iter->second;
      }
      for ( ; i < 11; i++) {
        auto [iter, bo]  = _uri.insert({_data[i], 0});
        _points[i] = &(iter->second);
      }
    }

HttpRequest ParseRequest(string_view line) {
    HttpRequest pars;
    
    size_t R = 0;
    while(line[R] == ' ') {R++;}
    size_t pos = line.find(' ', R);
    pars.method = line.substr(R, pos - R);
    R = pos + 1;
    while(line[R] == ' ') {R++;}
    pos = line.find(' ', R);
    pars.uri = line.substr(R, pos - R);
    line.remove_prefix(line.rfind(' ') + 1);
    pars.protocol = line.substr();
    return pars;
}
