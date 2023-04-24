#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "token.h"

class Scanner {
public:
  Scanner(std::string source);
  std::vector<Token> scanTokens(); 

private:
  bool isAtEnd();
  char advance();
  void scanToken();
  void addToken(TokenType type);
  void addToken(TokenType type, Value literal);
  bool match(char expected);
  char peek();
  char peekNext();
  void scanString();
  void scanNumber();
  void scanIdentifier();

  std::string source;
  std::vector<Token> tokens;
  int lexeme_start_character = 0;
  int current_character = 0;
  int current_line = 1;

  std::unordered_map<std::string, TokenType> keywords {
    {"and", TokenType::AND},
    {"class", TokenType::CLASS},
    {"else", TokenType::ELSE},
    {"false", TokenType::FALSE},
    {"for", TokenType::FOR},
    {"fun", TokenType::FUN},
    {"if", TokenType::IF},
    {"nil", TokenType::NIL},
    {"or", TokenType::OR},
    {"print", TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"super", TokenType::SUPER},
    {"this", TokenType::THIS},
    {"true", TokenType::TRUE},
    {"var", TokenType::VAR},
    {"while", TokenType::WHILE}
  };
};