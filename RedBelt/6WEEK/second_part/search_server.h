#pragma once

#include "iterator_range.h"
#include "Msync.h"

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <string_view>
#include <deque>
#include <utility>

#include <mutex>
#include <future>

using namespace std;

class InvertedIndex {
public:
  InvertedIndex() = default;
  explicit InvertedIndex(istream& document_input);

  using it = vector<pair<size_t, int>>::const_iterator;
  IteratorRange<it> Lookup(string_view word) const;
  
  size_t GetMaxDocId();
  
private:
  map<string_view, vector<pair<size_t, int>>> _index;
  deque<string> _docs;
}; 

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input)
  : index(InvertedIndex(document_input))
  {}
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  void UDB(istream& document_input);
  void AQS(istream& query_input, ostream& search_results_output);

  Synchronized<InvertedIndex> index;
  vector<future<void>> fut;
};
