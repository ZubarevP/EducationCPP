#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <string_view>
#include <future>
#include <mutex>

using namespace std;

class InvertedIndex {
public:
    InvertedIndex() {_docs.reserve(50000);}
    void Add(string& document);
    vector<pair<size_t,int>> Lookup(string_view word) const;
    size_t GetMaxDocId() {return _docs.size();}
    const string& GetDocument(size_t id) const {return _docs[id];}

private:
    map<string_view, vector<pair<size_t, int>>> _index;
    vector<string> _docs;
}; 


class SearchServer {
public:
    SearchServer() = default;
    ~SearchServer() {
        for(auto& l : fut) {
            l.get();
        }
    }
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void UDB(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);
    void AQS(istream& query_input, ostream& search_results_output);

private:
    mutex mut;
    InvertedIndex index;
    vector<future<void>> fut;
};