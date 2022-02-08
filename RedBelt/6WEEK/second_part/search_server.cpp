#include "search_server.h"
#include "iterator_range.h"
#include "parse.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <set> 
#include <utility>

vector<string_view> SplitIntoWords(string_view line) {
  return SplitBy2(Strip(line), ' ');
}

void InvertedIndex::Add(string& document) {
  docs.push_back(move(document));

  const size_t docid = docs.size() - 1;
  for (const auto& word : SplitIntoWords(docs[docid])) {
    if(index.count(word) && index[word].back().second == docid) {
        index[word].back().first++;
    } else {
        index[word].push_back({1, docid});
    }
  }
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;
  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(current_document);
  }
  index = move(new_index);
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {

  const size_t MaxDocId = index.GetMaxDocId();
  vector<size_t> docid_count;
  docid_count.reserve(MaxDocId);

  for (string current_query; getline(query_input, current_query); ) {

    for(size_t i = 0; i < MaxDocId; i++) {
      docid_count[i] = 0;
    }

    for (const auto& word : SplitIntoWords(current_query)) {
      for(const auto [f, s] : index.Lookup(word)){
        docid_count[s] += f;
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

vector<pair<size_t, int>> InvertedIndex::Lookup(string_view word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}