#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <string_view>
using namespace std;

class InvertedIndex {
public:
  InvertedIndex() {
    docs.reserve(50000);
  }
  void Add(string& document);
  vector<pair<size_t,int>> Lookup(string_view word) const;

  size_t GetMaxDocId() {
    return docs.size();
  }

   const string& GetDocument(size_t id) const {
    return docs[id];
  }

private:
  map<string_view, vector<pair<size_t, int>>> index;
  vector<string> docs;
}; 

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
};
