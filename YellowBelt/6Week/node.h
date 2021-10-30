#pragma once
#include "date.h"
#include <memory>

using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And,
};


class Node {
public:
    virtual bool Evaluate(const Date& date_lhs, const string& event_lhs) const = 0;
};


class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp, Date date)
            : date_rhs(date)
            , cmp_(cmp) {
        }
    bool Evaluate(const Date& date_lhs, const string& event_lhs) const override;
private:
    const Date date_rhs;
    const Comparison cmp_;
};


class EventComparisonNode : public Node {
public:
    EventComparisonNode (Comparison cmp, string event) 
        : cmp_(cmp)
        , event_rhs(event) {
    }
    bool Evaluate(const Date& date_lhs, const string& event_lhs) const override;
private:
    const Comparison cmp_;
    const string event_rhs;
};


class LogicalOperationNode : public Node {
public:
    LogicalOperationNode (LogicalOperation op, shared_ptr<Node> left,shared_ptr<Node> right)
        : op_(op)
        , left_(left)
        , right_(right) {
    }
    bool Evaluate(const Date& date, const string& event) const override;
private:
    LogicalOperation op_;
    shared_ptr<Node> left_;
    shared_ptr<Node> right_;
};


class EmptyNode : public Node {
    bool Evaluate(const Date& date, const string& event) const override;
};

