#include "Common.h"
#include "test_runner.h" 

#include <sstream>
#include <utility>

using namespace std;

class Digit : public Expression {
public:
    explicit Digit(int digit_)
        : digit(digit_)
        , digit_str(move(to_string(digit_)))
    {}

    virtual int Evaluate() const override {
         return digit;
    }

    virtual string ToString() const override {
        return digit_str;;
    }

private:
    int digit;
    string digit_str;
};

class Expr : public Expression {
public:
    explicit Expr(ExpressionPtr lhs_, ExpressionPtr rhs_, char sign_)
        : lhs(move(lhs_))
        , rhs(move(rhs_))
        , sign(sign_)
    {}

    virtual int Evaluate() const override {
        if(sign == '+') {
            return lhs->Evaluate() + rhs->Evaluate();
        }
        return lhs->Evaluate() * rhs->Evaluate();
    }

    virtual string ToString() const override {
        stringstream input;
        input   << '(' << lhs->ToString() << ')'
                << sign
                << '(' << rhs->ToString() << ')';
        return input.str();
    }

private:
    ExpressionPtr lhs;
    ExpressionPtr rhs;
    char sign;
};

ExpressionPtr Value(int value) {
    return move(make_unique<Digit>(value));
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
    return move(make_unique<Expr>(move(left), move(right), '+'));
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
    return move(make_unique<Expr>(move(left), move(right), '*'));
}

string Print(const Expression* e) {
  if (!e) {
    return "Null expression provided";
  }
  stringstream output;
  output << e->ToString() << " = " << e->Evaluate();
  return output.str();
}

void Test() {
  ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
  ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

  ExpressionPtr e2 = Sum(move(e1), Value(5));
  ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

  ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, Test);
  return 0;
}