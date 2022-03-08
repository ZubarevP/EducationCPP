#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

using namespace std;


struct Email {
  string from;
  string to;
  string body;

};

// ----------------------------- Worker --------------------------
class Worker {
public:
    virtual ~Worker() = default;
    virtual void Process(unique_ptr<Email> email) = 0;
    virtual void Run() {
        throw logic_error("Unimplemented");
    }

protected:
    void PassOn(unique_ptr<Email> email) const {
        if(next_link) {
            next_link->Process(move(email));
        }
    }

public:
    void SetNext(unique_ptr<Worker> next) {
        next_link = move(next);
    }
private: 
    unique_ptr<Worker> next_link;
};


// ----------------------------- Reader --------------------------
class Reader : public Worker {
public:
    explicit Reader(istream& input_) 
        : input(input_)
    {}

    void Process(unique_ptr<Email>) override {}

    void Run() override {
        while( 1 ) {
            if(input.eof()) break;
                auto email = make_unique<Email>();
                getline(input, email->from);
            if(input.eof()) break;
                getline(input, email->to);
            if(input.eof()) break;
                getline(input, email->body);
                
                PassOn(move(email));
        }
    }

private:
    istream& input;
};


// ----------------------------- Filter --------------------------
class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;

public:
    explicit Filter(Function func_)
        : func(move(func_))
    {}

    void Process(unique_ptr<Email> email) override {
        if(func(*email)) {
            PassOn(move(email));
        }
    }

private:
    Function func;
};


// ----------------------------- Copier --------------------------
class Copier : public Worker {
public:
    explicit Copier(string new_adress_)
        : new_adress(move(new_adress_))
    {}

    void Process(unique_ptr<Email> email) override {
        if(email->to != new_adress) {
            auto second_mail = make_unique<Email>(*email);
            // move
            second_mail->to = move(new_adress);
            
            PassOn(move(email));
            PassOn(move(second_mail));
        } else {
            PassOn(move(email));
        }
    }
private:
    string new_adress;
};


// ----------------------------- Sender --------------------------
class Sender : public Worker {
public:
    explicit Sender(ostream& output_)
        : output(output_)
    {}
    void Process(unique_ptr<Email> email) override {
        output  << email->from << endl
                << email->to << endl
                << email->body << endl;
        
        PassOn(move(email));
    }

private:
    ostream& output;
};


class PipelineBuilder {
public:
    explicit PipelineBuilder(istream& in) {
        result.push_back(make_unique<Reader>(in));
    }

    PipelineBuilder& FilterBy(Filter::Function filter) {
        result.push_back(make_unique<Filter>(move(filter)));
        return *this;
    }

    PipelineBuilder& CopyTo(string recipient) {
        result.push_back(make_unique<Copier>(move(recipient)));
        return *this;
    }

    PipelineBuilder& Send(ostream& out) {
        result.push_back(make_unique<Sender>(out));
        return *this;
    }

    unique_ptr<Worker> Build() {
        for(size_t i = result.size() - 1 ; i > 0; --i) {
            result[i - 1]->SetNext(move(result[i]));
        }
        return move(result[0]);
    }

private:
    vector<unique_ptr<Worker>> result;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );

  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}
