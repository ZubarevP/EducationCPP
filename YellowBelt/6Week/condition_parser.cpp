#include "condition_parser.h"
#include "token.h"
#include "node.h"

#include <map>
using namespace std;

template <class It> 
shared_ptr<Node> ParseComparison(It& current, It end) {
  if (current == end) {
    throw logic_error("Expected column name: date or event");
  }

  Token& column = *current;
  if (column.type != TokenType::COLUMN) {
    throw logic_error("Expected column name: date or event");
  }
  ++current;

  if (current == end) {
    throw logic_error("Expected comparison operation");
  }

  Token& op = *current;
  if (op.type != TokenType::COMPARE_OP) {
    throw logic_error("Expected comparison operation");
  }
  ++current;

  if (current == end) {
    throw logic_error("Expected right value of comparison");
  }

  Comparison cmp;
  if (op.value == "<") {
    cmp = Comparison::Less;
  } else if (op.value == "<=") {
    cmp = Comparison::LessOrEqual;
  } else if (op.value == ">") {
    cmp = Comparison::Greater;
  } else if (op.value == ">=") {
    cmp = Comparison::GreaterOrEqual;
  } else if (op.value == "==") {
    cmp = Comparison::Equal;
  } else if (op.value == "!=") {
    cmp = Comparison::NotEqual;
  } else {
    throw logic_error("Unknown comparison token: " + op.value);
  }

  const string& value = current->value;
  ++current;

  if (column.value == "date") {
    istringstream is(value);
    return make_shared<DateComparisonNode>(cmp, ParseDate(is));
  } else { 
    return make_shared<EventComparisonNode>(cmp, value);
  }
}

template <class It>
shared_ptr<Node> ParseExpression(It& current, It end, unsigned precedence) {
  if (current == end) {
    return shared_ptr<Node>();
  }

  shared_ptr<Node> left;

  if (current->type == TokenType::PAREN_LEFT) {
    ++current; // consume '('
    left = ParseExpression(current, end, 0u);
    if (current == end || current->type != TokenType::PAREN_RIGHT) {
      throw logic_error("Missing right paren");
    }
    ++current; // consume ')'
  } else {
    //left = после разбора string из вектора токенов
    //возвращает DateComparisonNode или EventComparisonNode
    //разобранные на дату/собыетие и на код оператора перед ним
    left = ParseComparison(current, end);
  }

  const map<LogicalOperation, unsigned> precedences = {
      {LogicalOperation::Or, 1}, {LogicalOperation::And, 2}
  };
    //далее цикл работает до момента достижения конца или правой скобки
    //если это конец или правая скобка то возвращает дата/событие с котдом оператора
  while (current != end && current->type != TokenType::PAREN_RIGHT) {
    if (current->type != TokenType::LOGICAL_OP) {
      throw logic_error("Expected logic operation");
    }
    //значение типа enum class LogicalOperation  принимает 1(и) или 2(или)
    const auto logical_operation = current->value == "AND" ? LogicalOperation::And
                                                           : LogicalOperation::Or;
    const auto current_precedence = precedences.at(logical_operation);

    /*------------------------------------------------------
      при начале разбора выражения или при попадании в скобки приоритет == 0
      любая текущая логическая операция после входа в выражение выполняется и 
      присходит переход к правому операнду логической операции 
      если прошлая операция 1(или) а текущая 0(вход в скобки) = завершение цикла 
      если прошлая операция 1(или) а текущая 1(или) = завершение цикла
      если прошлая операция 1(или) а текущая 2(вход в скобки) = продложение цикла 
      если прошлая операция 2(и)  - завершение цикла в любре случае 
    ------------------------------------------------------*/
    
    if (current_precedence <= precedence) {
      break;
    }

    ++current; // consume op

    left = make_shared<LogicalOperationNode>(
        logical_operation, left, ParseExpression(current, end, current_precedence)
    );
  }

  return left;
}

shared_ptr<Node> ParseCondition(istream& is) {
  auto tokens = Tokenize(is);
  auto current = tokens.begin();
  auto top_node = ParseExpression(current, tokens.end(), 0u);

  if (!top_node) {
    top_node = make_shared<EmptyNode>();
  }

  if (current != tokens.end()) {
    throw logic_error("Unexpected tokens after condition");
  }

  return top_node;
}