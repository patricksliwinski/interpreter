#pragma once

#include <vector>
#include <stdexcept>
#include "token.h"
#include "expression/expression.h"
#include "statement/statement.h"

class Parser {
public:
  Parser(std::vector<Token> tokens);
  std::vector<std::unique_ptr<Statement>> parse();

private:
  class ParseError : public std::runtime_error {
    public:
      ParseError() : std::runtime_error("") {};
  };

  std::unique_ptr<Statement> parseDeclaration();
  std::unique_ptr<Statement> parseFunctionDeclaration(std::string kind);
  std::unique_ptr<Statement> parseVarDeclaration();

  std::unique_ptr<Statement> parseStatement();
  std::unique_ptr<Statement> parseWhileStatement();
  std::unique_ptr<Statement> parseIfStatement();
  std::unique_ptr<Statement> parsePrintStatement();
  std::unique_ptr<Statement> parseBlockStatement();
  std::unique_ptr<Statement> parseExpressionStatement();
  std::unique_ptr<Statement> parseForStatement();

  std::unique_ptr<Expression> parseExpression();
  std::unique_ptr<Expression> parseAssignment();
  std::unique_ptr<Expression> parseOr();
  std::unique_ptr<Expression> parseAnd();
  std::unique_ptr<Expression> parseEquality();
  std::unique_ptr<Expression> parseComparison();
  std::unique_ptr<Expression> parseTerm();
  std::unique_ptr<Expression> parseFactor();
  std::unique_ptr<Expression> parseUnary();
  std::unique_ptr<Expression> parseCall();
  std::unique_ptr<Expression> parsePrimary();

  std::unique_ptr<Expression> finishCall(std::unique_ptr<Expression> callee);

  template<typename... Args>
  bool match(Args... args);

  Token consume(TokenType type, const std::string& message);
  bool check(TokenType type) const;
  Token advance();
  bool isAtEnd() const;
  Token peek() const;
  Token previous() const;

  ParseError error(Token token, const std::string& message) const;
  void synchronize();

  std::vector<Token> tokens;
  int currentToken = 0;
};

template<typename... Args>
bool Parser::match(Args... args)
{
  std::initializer_list<bool> results{check(args)...};
  for (auto r : results) {
    if (r) {
      advance();
      return true;
    }
  }
  return false;
}