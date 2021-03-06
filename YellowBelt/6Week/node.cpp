#include "node.h"

using namespace std;

bool DateComparisonNode::Evaluate(const Date& date_lhs, const string& event_lhs) const {
        switch(cmp_){
            case Comparison::Less : return date_lhs < date_rhs ? true : false;
            case Comparison::LessOrEqual : return date_lhs <= date_rhs ? true : false;
            case Comparison::Greater : return date_lhs > date_rhs ? true : false;
            case Comparison::GreaterOrEqual : return date_lhs >= date_rhs ? true : false;
            case Comparison::Equal : return date_lhs == date_rhs ? true : false;
            case Comparison::NotEqual : return date_lhs != date_rhs ? true : false;
        }
        string l = event_lhs;
        return true;
    }

int DateComparisonNode::GetNum() const  {
        return Num;
    }

bool EventComparisonNode::Evaluate(const Date& date_lhs, const string& event_lhs) const {
        switch(cmp_){
            case Comparison::Less : return event_lhs < event_rhs ? true : false;
            case Comparison::LessOrEqual : return event_lhs <= event_rhs ? true : false;
            case Comparison::Greater : return event_lhs > event_rhs ? true : false;
            case Comparison::GreaterOrEqual : return event_lhs >= event_rhs ? true : false;
            case Comparison::Equal : return event_lhs == event_rhs ? true : false;
            case Comparison::NotEqual : return event_lhs != event_rhs ? true : false;
        }
        Date k = date_lhs;
        return true;
    }

int EventComparisonNode::GetNum() const  {
        return Num;
    }

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
        switch(op_) {
            case LogicalOperation::Or : return left_->Evaluate(date, event) || right_->Evaluate(date, event) ? true : false;
            case LogicalOperation::And : return left_->Evaluate(date, event) && right_->Evaluate(date, event) ? true : false;
        }
        return true;
    }

int LogicalOperationNode::GetNum() const {
        return Num;
    }

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    string l = event;
    Date k = date;
       return true;
    }

int EmptyNode::GetNum() const  {
        return Num;
    }