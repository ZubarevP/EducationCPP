#include "search_server.h"
#include "parse.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <set>
#include <utility>
#include <functional>

//========================= Update =============================
vector<string_view> SplitIntoWords(string_view line) {
  return SplitBy2(Strip(line), ' ');
}

InvertedIndex::InvertedIndex(istream& document_input) {
  for (string current_document; getline(document_input, current_document); ) {

    _docs.push_back(move(current_document));
    const size_t docid = _docs.size() - 1;
  
    for (const auto& word : SplitIntoWords(_docs[docid])) {

      if(!_index[word].empty() && _index[word].back().second == static_cast<int>(docid)) {
          _index[word].back().first++;
      } else {
          _index[word].push_back({1, docid});
      }
    }
  }
}

void SearchServer::UDB(istream& document_input) {
  InvertedIndex new_index (document_input);
  {
    swap(index.GetAccess().ref_to_value, new_index);
  }
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  fut.push_back(async([&]{UDB(document_input);}));
}

//========================= Add =============================
IteratorRange<vector<pair<size_t, int>>::const_iterator> 
InvertedIndex::Lookup(string_view word) const {

  if (auto it = _index.find(word); it != _index.end()) {
    return {(it->second).begin(), (it->second).end()};
  } else {
    vector<pair<size_t, int>>::const_iterator Iter;
    return {Iter, Iter};
  }
}

void  SearchServer::AQS(istream& query_input, ostream& search_results_output) {

  vector<size_t> docid_count;

  for (string current_query; getline(query_input, current_query); ) {
    const auto words = SplitIntoWords(current_query);
    size_t MaxDocId;
    {
      auto& temp = index.GetAccess().ref_to_value;
      MaxDocId = temp.GetMaxDocId();
      docid_count.assign(MaxDocId, 0);

      for (const auto& word : words) {
        for(const auto& [f, s] : temp.Lookup(word)){
          docid_count[s] += f;
        }
      }
    }
    
    set<pair<size_t, int>> search_results;
    size_t j = 0;
    for( ; search_results.size() < 5 && j < MaxDocId; j++) {
      if(docid_count[j] > 0) {
        search_results.insert({docid_count[j], -j});
      }
    }
    for( ; j < MaxDocId; j++) {
      if(docid_count[j] > search_results.begin()->first) {
        search_results.erase(search_results.begin());
        search_results.insert({docid_count[j], -j});
      }
    }

    search_results_output << current_query << ':';
    for (auto T = search_results.rbegin(); T != search_results.rend(); T++) {
      search_results_output << " {"
        << "docid: " << -(T->second) << ", "
        << "hitcount: " << T->first << '}';
    }
    search_results_output << "\n";
  }
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) { 
    fut.push_back(async([&] {AQS(query_input, search_results_output);}));
}



size_t InvertedIndex::GetMaxDocId() {
    return _docs.size();
}
