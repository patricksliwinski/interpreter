#include <stdexcept>

#include "parser.h"

#include "statement/var-statement.h"
#include "statement/function-statement.h"
#include "statement/expression-statement.h"
#include "statement/if-statement.h"
#include "statement/print-statement.h"
#include "statement/block-statement.h"
#include "statement/while-statement.h"

#include "expression/binary-expression.h"
#include "expression/grouping-expression.h"
#include "expression/value-expression.h"
#include "expression/unary-expression.h"
#include "expression/variable-expression.h"
#include "expression/assignment-expression.h"
#include "expression/logical-expression.h"
#include "expression/call-expression.h"


Parser::Parser(std::vector<Token> tokens)
  : tokens(std::move(tokens)) {}

std::vector<std::unique_ptr<Statement>> Parser::parse() {
  std::vector<std::unique_ptr<Statement>> statements;
  while (!isAtEnd()) {
    statements.push_back(parseDeclaration());
  }
  return statements;
}

std::unique_ptr<Statement> Parser::parseDeclaration() {
  try {
    if (match(TokenType::FUN)) return parseFunctionDeclaration("function");
    if (match(TokenType::VAR)) return parseVarDeclaration();
    return parseStatement();
  } catch (const std::runtime_error& error) {
    synchronize();
    return nullptr;
  }
}

std::unique_ptr<Statement> Parser::parseFunctionDeclaration(std::string kind) {
  Token name = consume(TokenType::IDENTIFIER, "Expect " + kind + " name.");
  consume(TokenType::LEFT_PAREN, "Expect '(' after " + kind + " name.");
  std::vector<Token> params;
  if (!check(TokenType::RIGHT_PAREN)) {
    do {
      if (params.size() >= 255) {
        error(peek(), "Cannot have more than 255 parameters.");
      }
      params.push_back(consume(TokenType::IDENTIFIER, "Expect parameter name."));
    } while (match(TokenType::COMMA));
  }
  consume(TokenType::RIGHT_PAREN, "Expect ')' after parameters.");
  consume(TokenType::LEFT_BRACE, "Expect '{' before " + kind + " body.");
  // TODO: avoid the use of release, it is not exception safe
  auto block = dynamic_cast<BlockStatement*>(parseBlockStatement().release());
  std::vector<std::unique_ptr<Statement>> body = block->getStatements();
  //std::vector<std::unique_ptr<Statement>> body = dynamic_cast<BlockStatement*>(parseBlockStatement().release())->getStatements();
  return std::make_unique<FunctionStatement>(name, std::move(params), std::move(body));
}

std::unique_ptr<Statement> Parser::parseVarDeclaration() {
  Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");
  std::unique_ptr<Expression> initializer = nullptr;
  if (match(TokenType::EQUAL)) {
    initializer = parseExpression();
  }
  consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
  return std::make_unique<VarStatement>(name, std::move(initializer));
}

std::unique_ptr<Statement> Parser::parseStatement() {
  if (match(TokenType::FOR)) return parseForStatement();
  if (match(TokenType::IF)) return parseIfStatement();
  if (match(TokenType::PRINT)) return parsePrintStatement();
  if (match(TokenType::WHILE)) return parseWhileStatement();
  if (match(TokenType::LEFT_BRACE)) return parseBlockStatement();
  return parseExpressionStatement();
}

// It would be better to have a separate for statement
// This follows the book example of "syntactic sugar", but ends up being a bit confusing
std::unique_ptr<Statement> Parser::parseForStatement() {
  consume(TokenType::LEFT_PAREN, "Expect '(' after 'for'.");
  std::unique_ptr<Statement> initializer = nullptr;
  if (match(TokenType::SEMICOLON)) {
    initializer = nullptr;
  } else if (match(TokenType::VAR)) {
    initializer = parseVarDeclaration();
  } else {
    initializer = parseExpressionStatement();
  }

  std::unique_ptr<Expression> condition = nullptr;
  if (!check(TokenType::SEMICOLON)) {
    condition = parseExpression();
  }
  consume(TokenType::SEMICOLON, "Expect ';' after loop condition.");

  std::unique_ptr<Expression> increment = nullptr;
  if (!check(TokenType::RIGHT_PAREN)) {
    increment = parseExpression();
  }
  consume(TokenType::RIGHT_PAREN, "Expect ')' after for clauses.");

  auto body = parseStatement();

  if (increment != nullptr) {
    auto incrementStatement = std::make_unique<ExpressionStatement>(std::move(increment));
    auto bodyVector = std::vector<std::unique_ptr<Statement>> {};
    bodyVector.push_back(std::move(body));
    bodyVector.push_back(std::move(incrementStatement));
    body = std::make_unique<BlockStatement>(std::move(bodyVector));
  }

  if (condition == nullptr) {
    condition = std::make_unique<ValueExpression>(true);
  }
  body = std::make_unique<WhileStatement>(std::move(condition), std::move(body));

  if (initializer != nullptr) {
    auto bodyVector = std::vector<std::unique_ptr<Statement>> {};
    bodyVector.push_back(std::move(initializer));
    bodyVector.push_back(std::move(body));
    body = std::make_unique<BlockStatement>(std::move(bodyVector));
  }

  return body;
}

std::unique_ptr<Statement> Parser::parseIfStatement() {
  consume(TokenType::LEFT_PAREN, "Expect '(' after 'if'.");
  auto condition = parseExpression();
  consume(TokenType::RIGHT_PAREN, "Expect ')' after if condition.");
  auto thenBranch = parseStatement();
  std::unique_ptr<Statement> elseBranch = nullptr;
  if (match(TokenType::ELSE)) {
    elseBranch = parseStatement();
  }

  return std::make_unique<IfStatement>(std::move(condition), std::move(thenBranch), std::move(elseBranch));
}

std::unique_ptr<Statement> Parser::parsePrintStatement() {
  auto expression = parseExpression();
  consume(TokenType::SEMICOLON, "Expect ';' after value.");
  return std::make_unique<PrintStatement>(std::move(expression));
}

std::unique_ptr<Statement> Parser::parseWhileStatement() {
  consume(TokenType::LEFT_PAREN, "Expect '(' after 'while'.");
  auto condition = parseExpression();
  consume(TokenType::RIGHT_PAREN, "Expect ')' after while condition.");
  auto body = parseStatement();
  return std::make_unique<WhileStatement>(std::move(condition), std::move(body));
}

std::unique_ptr<Statement> Parser::parseBlockStatement() {
  std::vector<std::unique_ptr<Statement>> statements;
  while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
    statements.push_back(parseDeclaration());
  }
  consume(TokenType::RIGHT_BRACE, "Expect '}' after block.");
  return std::make_unique<BlockStatement>(std::move(statements));
}

std::unique_ptr<Statement> Parser::parseExpressionStatement() {
  auto expression = parseExpression();
  consume(TokenType::SEMICOLON, "Expect ';' after expression.");
  return std::make_unique<ExpressionStatement>(std::move(expression));
}

std::unique_ptr<Expression> Parser::parseExpression() {
  return parseAssignment();
}

std::unique_ptr<Expression> Parser::parseAssignment() {
  auto expression = parseOr();

  if (match(TokenType::EQUAL)) {
    auto equals = previous();
    auto value = parseAssignment();

    if (auto variable = dynamic_cast<VariableExpression*>(expression.get())) {
      auto name = variable->getName();
      return std::make_unique<AssignmentExpression>(name, std::move(value));
    }

    throw error(equals, "Invalid assignment target.");
  }

  return expression;
}

std::unique_ptr<Expression> Parser::parseOr() {
  auto expression = parseAnd();

  while (match(TokenType::OR)) {
    auto operatorToken = previous();
    auto right = parseAnd();
    expression = std::make_unique<LogicalExpression>(std::move(expression), operatorToken, std::move(right));
  }

  return expression;
}

std::unique_ptr<Expression> Parser::parseAnd() {
  auto expression = parseEquality();

  while (match(TokenType::AND)) {
    auto operatorToken = previous();
    auto right = parseEquality();
    expression = std::make_unique<LogicalExpression>(std::move(expression), operatorToken, std::move(right));
  }

  return expression;
}

std::unique_ptr<Expression> Parser::parseEquality() {
  auto expression = parseComparison();

  while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
    auto operatorToken = previous();
    auto right = parseComparison();
    expression = std::make_unique<BinaryExpression>(std::move(expression), operatorToken, std::move(right));
  }

  return expression;
}

std::unique_ptr<Expression> Parser::parseComparison() {
  auto expression = parseTerm();

  while (match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL)) {
    auto operatorToken = previous();
    auto right = parseTerm();
    expression = std::make_unique<BinaryExpression>(std::move(expression), operatorToken, std::move(right));
  }

  return expression;
}

std::unique_ptr<Expression> Parser::parseTerm() {
  auto expression = parseFactor();

  while (match(TokenType::MINUS, TokenType::PLUS)) {
    auto operatorToken = previous();
    auto right = parseFactor();
    expression = std::make_unique<BinaryExpression>(std::move(expression), operatorToken, std::move(right));
  }

  return expression;
}

std::unique_ptr<Expression> Parser::parseFactor() {
  auto expression = parseUnary();

  while (match(TokenType::SLASH, TokenType::STAR)) {
    auto operatorToken = previous();
    auto right = parseUnary();
    expression = std::make_unique<BinaryExpression>(std::move(expression), operatorToken, std::move(right));
  }

  return expression;
}

std::unique_ptr<Expression> Parser::parseUnary() {
  if (match(TokenType::BANG, TokenType::MINUS)) {
    auto operatorToken = previous();
    auto right = parseUnary();
    return std::make_unique<UnaryExpression>(operatorToken, std::move(right));
  }

  return parseCall();
}

std::unique_ptr<Expression> Parser::parseCall() {
  auto expression = parsePrimary();

  while (true) {
    if (match(TokenType::LEFT_PAREN)) {
      expression = finishCall(std::move(expression));
    } else {
      break;
    }
  }

  return expression;
}

std::unique_ptr<Expression> Parser::parsePrimary() {
  if (match(TokenType::FALSE)) {
    return std::make_unique<ValueExpression>(false);
  }

  if (match(TokenType::TRUE)) {
    return std::make_unique<ValueExpression>(true);
  }

  if (match(TokenType::NIL)) {
    return std::make_unique<ValueExpression>(nullptr);
  }

  if (match(TokenType::NUMBER, TokenType::STRING)) {
    return std::make_unique<ValueExpression>(previous().getValue());
  }

  if (match(TokenType::LEFT_PAREN)) {
    auto expression = parseExpression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
    return std::make_unique<GroupingExpression>(std::move(expression));
  }

  if (match(TokenType::IDENTIFIER)) {
    return std::make_unique<VariableExpression>(previous());
  }

  throw error(peek(), "Expect expression.");
}

Token Parser::consume(TokenType type, const std::string& message) {
  if (check(type)) {
    return advance();
  }

  throw std::runtime_error(message);
}

bool Parser::check(TokenType type) const {
  if (isAtEnd()) {
    return false;
  }
  return peek().getType() == type;
}

Token Parser::advance() {
  if (!isAtEnd()) {
    ++currentToken;
  }
  return previous();
}

bool Parser::isAtEnd() const {
  return peek().getType() == TokenType::EOF_TOKEN;
}

Token Parser::peek() const {
  return tokens[currentToken];
}

Token Parser::previous() const {
  return tokens[currentToken - 1];
}

void Parser::synchronize() {
  advance();

  while (!isAtEnd()) {
    if (previous().getType() == TokenType::SEMICOLON) {
      return;
    }

    switch (peek().getType()) {
    case TokenType::CLASS:
    case TokenType::FUN:
    case TokenType::VAR:
    case TokenType::FOR:
    case TokenType::IF:
    case TokenType::WHILE:
    case TokenType::PRINT:
    case TokenType::RETURN:
      return;
    default:
      break;
    }

    advance();
  }
}

std::unique_ptr<Expression> Parser::finishCall(std::unique_ptr<Expression> callee) {
  std::vector<std::unique_ptr<Expression>> arguments;

  if (!check(TokenType::RIGHT_PAREN)) {
    do {
      if (arguments.size() >= 255) {
        error(peek(), "Can't have more than 255 arguments.");
      }
      arguments.push_back(parseExpression());
    } while (match(TokenType::COMMA));
  }

  auto paren = consume(TokenType::RIGHT_PAREN, "Expect ')' after arguments.");

  return std::make_unique<CallExpression>(std::move(callee), paren, std::move(arguments));
}