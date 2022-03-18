#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

template <typename It>
class Range {
public:
  Range(It begin, It end) : begin_(begin), end_(end) {}
  It begin() const { return begin_; }
  It end() const { return end_; }

private:
  It begin_;
  It end_;
};

//split long string_view & return part and (tail or nullopt)
pair<string_view, optional<string_view>> SplitTwoStrict(string_view s, string_view delimiter = " ") {
  const size_t pos = s.find(delimiter);
  if (pos == s.npos) {
    return {s, nullopt};
  } else {
    return {s.substr(0, pos), s.substr(pos + delimiter.length())};
  }
}
//slipt long string_view in part from " " to " " or end
vector<string_view> Split(string_view s, string_view delimiter = " ") {
  vector<string_view> parts;
  if (s.empty()) {
    return parts;
  }
  while (true) {
    const auto [lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
    parts.push_back(lhs);
    if (!rhs_opt) {
      break;
    }
    s = *rhs_opt;
  }
  return parts;
}

//store string of all domains (default makes from reverse range)
class Domain {
public:
  explicit Domain(string_view text) {
    vector<string_view> parts = Split(text, ".");
    parts_reversed_.assign(rbegin(parts), rend(parts));
  }
  // return size of storage of domains
  size_t GetPartCount() const {
    return parts_reversed_.size();
  }

  // return reverse range of stored domains
  auto GetParts() const {
    return Range(rbegin(parts_reversed_), rend(parts_reversed_));
  }

  // retur range of stored domains
  auto GetReversedParts() const {
    return Range(begin(parts_reversed_), end(parts_reversed_));
  }

  bool operator==(const Domain& other) const {
    return parts_reversed_ == other.parts_reversed_;
  }

private:
  vector<string> parts_reversed_;
};

ostream& operator<<(ostream& stream, const Domain& domain) {
  bool first = true;
  for (const string_view part : domain.GetParts()) {
    if (!first) {
      stream << '.';
    } else {
      first = false;
    }
    stream << part;
  }
  return stream;
}

// domain is subdomain of itself
// check if domain is part of subdomain
bool IsSubdomain(const Domain& subdomain, const Domain& domain) {
  const auto subdomain_reversed_parts = subdomain.GetReversedParts();
  const auto domain_reversed_parts = domain.GetReversedParts();
  return
      subdomain.GetPartCount() >= domain.GetPartCount()
      && equal(begin(domain_reversed_parts), end(domain_reversed_parts),
               begin(subdomain_reversed_parts));
}
// check if domain is part of subdomain (both side)
bool IsSubOrSuperDomain(const Domain& lhs, const Domain& rhs) {
  return lhs.GetPartCount() >= rhs.GetPartCount()
         ? IsSubdomain(lhs, rhs)
         : IsSubdomain(rhs, lhs);
}

//sort & store banned domais
class DomainChecker {
public:
  // take range of banned domains, lexicographical sort
  template <typename InputIt>
  DomainChecker(InputIt domains_begin, InputIt domains_end) {
    sorted_domains_.reserve(distance(domains_begin, domains_end));
    for (const Domain& domain : Range(domains_begin, domains_end)) {
      sorted_domains_.push_back(&domain);
    }
    sort(begin(sorted_domains_), end(sorted_domains_), IsDomainLess);
    sorted_domains_ = AbsorbSubdomains(move(sorted_domains_));
  }

  // Check if candidate is subdomain of some domain
  bool IsSubdomain(const Domain& candidate) const {
    const auto it = upper_bound(
        begin(sorted_domains_), end(sorted_domains_),
        &candidate, IsDomainLess);
    if (it == begin(sorted_domains_)) {
      return false;
    }
    return ::IsSubdomain(candidate, **prev(it));
  }

private:
  vector<const Domain*> sorted_domains_;

  // lexicographical sort (less)
  static bool IsDomainLess(const Domain* lhs, const Domain* rhs) {
    const auto lhs_reversed_parts = lhs->GetReversedParts();
    const auto rhs_reversed_parts = rhs->GetReversedParts();
    return lexicographical_compare(
      begin(lhs_reversed_parts), end(lhs_reversed_parts),
      begin(rhs_reversed_parts), end(rhs_reversed_parts)
    );
  }
  // erase repiting elements
  static vector<const Domain*> AbsorbSubdomains(vector<const Domain*> domains) {
    domains.erase(
        unique(begin(domains), end(domains),
               [](const Domain* lhs, const Domain* rhs) {
                 return IsSubOrSuperDomain(*lhs, *rhs);
               }),
        end(domains)
    );
    return domains;
  }
};

//read stream & create new vector
vector<Domain> ReadDomains(istream& in_stream = cin) {
  vector<Domain> domains;

  size_t count;
  in_stream >> count;
  domains.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    string domain_text;
    in_stream >> domain_text;
    domains.emplace_back(domain_text);
  }
  return domains;
}

//check if the domain is in the stop-list
vector<bool> CheckDomains(const vector<Domain>& banned_domains, const vector<Domain>& domains_to_check) {
  const DomainChecker checker(begin(banned_domains), end(banned_domains));

  vector<bool> check_results;
  check_results.reserve(domains_to_check.size());
  for (const Domain& domain_to_check : domains_to_check) {
    check_results.push_back(!checker.IsSubdomain(domain_to_check));
  }

  return check_results;
}

void PrintCheckResults(const vector<bool>& check_results, ostream& out_stream = cout) {
  for (const bool check_result : check_results) {
    out_stream << (check_result ? "Good" : "Bad") << "\n";
  }
}

void TestSimple() {
    {
        string line {"one two.three four"};
        auto [start_line, finish_line] = SplitTwoStrict(line);
        ASSERT_EQUAL(start_line, "one");
        ASSERT_EQUAL(*finish_line, "two.three four");
        auto [start, finish] = SplitTwoStrict(*finish_line, ".");
        ASSERT_EQUAL(start, "two");
        ASSERT_EQUAL(*finish, "three four");
    }
    {
        string line {" one two.three four"};
        auto [start_line, finish_line] = SplitTwoStrict(line);
        ASSERT_EQUAL(start_line, "");
        ASSERT_EQUAL(*finish_line, "one two.three four");
    }
    {
        string line;
        auto [start_line, finish_line] = SplitTwoStrict(line);
        ASSERT_EQUAL(start_line, "");
        ASSERT_EQUAL((finish_line == nullopt ? true : false), true);
    }
    {
        string line;
        auto vect = Split(line);
        ASSERT_EQUAL(vect.empty(), true);
        line = "ya.ru next.com set.black";
        auto vect2 = Split(line);
        vector<string_view> test {
            "ya.ru",
            "next.com",
            "set.black"
        };
        ASSERT_EQUAL(vect2, test);
        ASSERT_EQUAL(Split("ya.ru", "."), vector<string_view>({"ya", "ru"}));
    }
    {
        istringstream input {"4\n" "ya.ru\n" "maps.me\n" "m.ya.ru\n" "com\n"};
        auto vect = ReadDomains(input);
        ASSERT_EQUAL(*(vect[0].GetReversedParts().begin()), "ru");
        ASSERT_EQUAL(*(vect[1].GetReversedParts().begin()), "me");
        ASSERT_EQUAL(*(vect[2].GetReversedParts().begin()), "ru");
        ASSERT_EQUAL(*(vect[3].GetReversedParts().begin()), "com");

        ASSERT_EQUAL(*next(vect[0].GetReversedParts().begin()), "ya");
        ASSERT_EQUAL(*next(vect[1].GetReversedParts().begin()), "maps");
        ASSERT_EQUAL(*next(vect[2].GetReversedParts().begin()), "ya");

        ASSERT_EQUAL(*prev(vect[2].GetReversedParts().end()), "m");

        ASSERT_EQUAL(*(vect[0].GetParts().begin()), "ya");
        ASSERT_EQUAL(*(vect[1].GetParts().begin()), "maps");
        ASSERT_EQUAL(*(vect[2].GetParts().begin()), "m");
        ASSERT_EQUAL(*(vect[3].GetParts().begin()), "com");

        ASSERT_EQUAL(vect[0].GetPartCount(), 2)
        ASSERT_EQUAL(vect[1].GetPartCount(), 2)
        ASSERT_EQUAL(vect[2].GetPartCount(), 3)
        ASSERT_EQUAL(vect[3].GetPartCount(), 1)

        const Domain dom("ya.ru");
        const auto temp = dom.GetReversedParts();
        const vector<string_view> rev(begin(temp), end(temp));
        ASSERT_EQUAL(rev, vector<string_view>({"ru", "ya"}));
    }
    {
        Domain rhs("ya.ru");

        Domain lhs1("ya.ru");               Domain lhs2("ya.com");
        Domain lhs3("m.maps.me");           Domain lhs4("moscow.m.ya.ru");
        Domain lhs5("maps.com");            Domain lhs6("maps.ru");
        Domain lhs7("ya.ya");
        ASSERT_EQUAL(IsSubdomain(lhs1, rhs), true);
        ASSERT_EQUAL(IsSubdomain(lhs2, rhs), false);
        ASSERT_EQUAL(IsSubdomain(lhs3, rhs), false);
        ASSERT_EQUAL(IsSubdomain(lhs4, rhs), true);
        ASSERT_EQUAL(IsSubdomain(lhs5, rhs), false);
        ASSERT_EQUAL(IsSubdomain(lhs6, rhs), false);

        ASSERT_EQUAL(IsSubdomain(rhs, lhs1), true);
        ASSERT_EQUAL(IsSubdomain(rhs, lhs2), false);
        ASSERT_EQUAL(IsSubdomain(rhs, lhs3), false);
        ASSERT_EQUAL(IsSubdomain(rhs, lhs4), false);
        ASSERT_EQUAL(IsSubdomain(rhs, lhs5), false);
        ASSERT_EQUAL(IsSubdomain(rhs, lhs6), false);
        ASSERT_EQUAL(IsSubdomain(Domain("ru"), Domain("ru")),true);
        ASSERT_EQUAL(IsSubdomain(Domain("m.ya.ru"), Domain("ya.ru")),true);
    }
    {
        Domain rhs("ya.ru");

        Domain lhs1("ya.ru");               Domain lhs2("ya.com");
        Domain lhs3("m.maps.me");           Domain lhs4("moscow.m.ya.ru");
        Domain lhs5("maps.com");            Domain lhs6("maps.ru");
        Domain lhs7("ya.ya");
        ASSERT_EQUAL(IsSubOrSuperDomain(lhs1, rhs), true);
        ASSERT_EQUAL(IsSubOrSuperDomain(lhs2, rhs), false);
        ASSERT_EQUAL(IsSubOrSuperDomain(lhs3, rhs), false);
        ASSERT_EQUAL(IsSubOrSuperDomain(lhs4, rhs), true);
        ASSERT_EQUAL(IsSubOrSuperDomain(lhs5, rhs), false);
        ASSERT_EQUAL(IsSubOrSuperDomain(lhs6, rhs), false);

        ASSERT_EQUAL(IsSubOrSuperDomain(rhs, lhs1), true);
        ASSERT_EQUAL(IsSubOrSuperDomain(rhs, lhs2), false);
        ASSERT_EQUAL(IsSubOrSuperDomain(rhs, lhs3), false);
        ASSERT_EQUAL(IsSubOrSuperDomain(rhs, lhs4), true);
        ASSERT_EQUAL(IsSubOrSuperDomain(rhs, lhs5), false);
        ASSERT_EQUAL(IsSubOrSuperDomain(rhs, lhs6), false);
    }
    {
        istringstream input {"4\n" "ya.ru\n" "maps.me\n" "m.ya.ru\n" "com\n"};
        auto vect = ReadDomains(input);\
        const DomainChecker checker(begin(vect), end(vect));

        Domain lhs1("ya.ru");               Domain lhs2("ya.com");
        Domain lhs3("m.maps.me");           Domain lhs4("moscow.m.ya.ru");
        Domain lhs5("maps.com");            Domain lhs6("maps.ru");
        Domain lhs7("ya.ya");

        ASSERT_EQUAL(checker.IsSubdomain(lhs1), true);
        ASSERT_EQUAL(checker.IsSubdomain(lhs2), true);
        ASSERT_EQUAL(checker.IsSubdomain(lhs3), true);
        ASSERT_EQUAL(checker.IsSubdomain(lhs4), true);
        ASSERT_EQUAL(checker.IsSubdomain(lhs5), true);
        ASSERT_EQUAL(checker.IsSubdomain(lhs6), false);
    }
    {
        const vector<Domain> dom = {Domain("ya.ru"),Domain("m.ya.ru")};
        ASSERT_EQUAL(DomainChecker(begin(dom), 
                    end(dom)).IsSubdomain(Domain("lier.ya.ru")),
                    true);
    }
    {
        ostringstream output;
        vector<bool> result {0, 0, 1, 1, 0, 1, };
        string test{
            "Bad\n" "Bad\n" "Good\n" "Good\n" "Bad\n" "Good\n"
        };
        PrintCheckResults(result, output);
        ASSERT_EQUAL(output.str(), test);

        ostringstream st;
        PrintCheckResults(vector({true, false}), st);
        ASSERT_EQUAL(st.str(), "Good\nBad\n");

        stringstream out;
        out << 1 << '\n' << "ya.ru";
        ASSERT_EQUAL(ReadDomains(out), vector({Domain("ya.ru")}));
    }
    {
        istringstream input {
            "7\n" "ya.ru\n" "ya.com\n" "m.maps.me\n" 
            "moscow.m.ya.ru\n" "maps.com\n" "maps.ru\n"
            "ya.ya\n"
        };
        auto vec = ReadDomains(input);
        ASSERT_EQUAL(vec.size(), 7);
    }
    {
        ASSERT_EQUAL(CheckDomains(
                vector({Domain("ya.ru")}), 
                vector({Domain("m.ya.ru")})
            ), vector({false}));  
    }
    {
        string line = "a b cd";
        auto result = Split(line, " ");
        vector<string_view> vec{ "a", "b", "cd" };
        ASSERT_EQUAL(result, vec);
    }
    {
        Domain dom = Domain("mail.ya.ru");
        auto res = dom.GetReversedParts();
        vector<string> vect = { res.begin(), res.end() };
        auto test = vector<string>{ "ru", "ya", "mail" };
        ASSERT_EQUAL(vect, test);
    }
    {
        vector<Domain> vect = { Domain("mail.ya.ru") };
        DomainChecker check(vect.begin(), vect.end());
        ASSERT(check.IsSubdomain(vect[0]));
        Domain dom = Domain("ya.ru");
        ASSERT(!check.IsSubdomain(dom));
        Domain dom2 = Domain("m2.mail.ya.ru");
        ASSERT(check.IsSubdomain(dom2));
    }
    {
        stringstream sstring;
        PrintCheckResults(vector<bool>{true, false, false}, sstring);
        vector<string> vect(3);
        for (size_t i = 0; i < 3; ++i) {
            sstring >> vect[i];
        }
        vector<string> test = { "Good", "Bad", "Bad" };
        ASSERT_EQUAL(test, vect);
    }
    {
        vector<Domain> ban = { Domain("ya.ru"), Domain("mail.ya.ru"), Domain("mail.ru") };
        vector<Domain> check = { 
            Domain("ya.ru"), Domain("mail.ya.ru"), Domain("mail.ru"),
            Domain("ru"), Domain(""), Domain("ba.ya.ru"), Domain("a.a.a.a.ya.ru")
        };
        auto result = CheckDomains(ban, check);
        vector<bool> test = { false, false, false, true, true, false, false };
        ASSERT_EQUAL(result, test);
    }
    {
        vector<Domain> ban = { Domain("ya.ru"), Domain("1.ya.ru"), Domain("3.ya.ru") };
        vector<Domain> check = { 
            Domain("ya.ru"), Domain("0.ya.ru"), Domain("2.ya.ru"),
            Domain("3.ya.ru"), Domain("4.ya.ru")
        };
        auto result = CheckDomains(ban, check);
        vector<bool> test = { false, false, false, false, false };
        ASSERT_EQUAL(result, test);
    }
    {
        stringstream sstream;
        sstream << "2 ya.ru mail.ru";
        auto result = ReadDomains(sstream);
        vector<Domain> test = { Domain("ya.ru"), Domain("mail.ru") };
        ASSERT_EQUAL(result, test);
    }
    {
        stringstream sstream;
        sstream << "2\nya.ru\nmail.ru";
        auto result = ReadDomains(sstream);
        vector<Domain> test = { Domain("ya.ru"), Domain("mail.ru") };
        ASSERT_EQUAL(test, result);
    }    
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);


  const vector<Domain> banned_domains = ReadDomains();
  const vector<Domain> domains_to_check = ReadDomains();
  PrintCheckResults(CheckDomains(banned_domains, domains_to_check));
  return 0;
}
