#include "ini.h"

#include <istream>

using namespace std;

namespace Ini {
    
    Section& Document::AddSection(string name) {
        return sections[name];
    }

    const Section& Document::GetSection(const string& name) const {
        return sections.at(name);
    }

    size_t Document::SectionCount() const {
        return sections.size();
    }
    
    void ParseValues(Section* section, istream& input) {
        char ch;
        string key, value;
        while(input >> ch) {
            if(ch != '[' && !isspace(ch)) {
                input.putback(ch);
                getline(input, key, '=');
                getline(input, value);
                section->insert({key, value});
            } else if(ch == '[') {
                input.putback(ch);
                break;
            }
        }
    }

    string ParseFWord(istream& input){
        string line, temp;
        getline(input, line, ']');
        return line; 
    }

    Document ParseArray(istream& input) {
        Document result;
        char ch;
        while(input >> ch ) {
            if(ch == '[' && !isspace(ch)) {
                Section* section = &result.AddSection(ParseFWord(input));
                ParseValues(section, input);
            }
        }
        return result;
    }

    Document Load(istream& input) {
       return ParseArray(input);
   }
}   