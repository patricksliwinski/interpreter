#include "scanner.h"
#include "lox-interpreter.h"

Scanner::Scanner(std::string source)
  : source(source) {}

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    lexeme_start_character = current_character;
    scanToken();
  }

  tokens.push_back(Token(TokenType::EOF_TOKEN, "", NullValue {}, current_line));
  return tokens;
}

bool Scanner::isAtEnd() {
  return current_character >= source.length();
}

char Scanner::advance() {
  return source[current_character++];
}

void Scanner::scanToken() {
  char c = advance();
  switch (c) {
    case '(': addToken(TokenType::LEFT_PAREN); break;
    case ')': addToken(TokenType::RIGHT_PAREN); break;
    case '{': addToken(TokenType::LEFT_BRACE); break;
    case '}': addToken(TokenType::RIGHT_BRACE); break;
    case ',': addToken(TokenType::COMMA); break;
    case '.': addToken(TokenType::DOT); break;
    case '-': addToken(TokenType::MINUS); break;
    case '+': addToken(TokenType::PLUS); break;
    case ';': addToken(TokenType::SEMICOLON); break;
    case '*': addToken(TokenType::STAR); break;
    case '!':
      addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
      break;
    case '=':
      addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
      break;
    case '<':
      addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
      break;
    case '>':
      addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
      break;
    case '/':
      if (match('/')) {
        while (peek() != '\n' && !isAtEnd()) advance();
      } else {
        addToken(TokenType::SLASH);
      }
      break;
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n':
      current_line++;
      break;
    case '"':
      scanString();
      break;
    default:
      if (std::isdigit(c)) {
        scanNumber();
      } else if (std::isalpha(c)) {
        scanIdentifier();
      } else {
        LoxInterpreter::error(current_line, "Unexpected character.");
      }
      break;
  }
}

void Scanner::addToken(TokenType type) {
  std::string lexeme = source.substr(lexeme_start_character, current_character - lexeme_start_character);
  tokens.push_back(Token(type, lexeme, NullValue {}, current_line));
}

void Scanner::addToken(TokenType type, Value literal) {
  std::string text = source.substr(lexeme_start_character, current_character - lexeme_start_character);
  tokens.push_back(Token(type, text, literal, current_line));
}

bool Scanner::match(char expected) {
  if (isAtEnd()) return false;
  if (source[current_character] != expected) return false;

  current_character++;
  return true;
}

char Scanner::peek() {
  if (isAtEnd()) return '\0';
  return source[current_character];
}

char Scanner::peekNext() {
  if (current_character + 1 >= source.length()) return '\0';
  return source[current_character + 1];
}
void Scanner::scanString() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') current_line++;
    advance();
  }

  if (isAtEnd()) {
    LoxInterpreter::error(current_line, "Unterminated string.");
    return;
  }

  std::string value = source.substr(lexeme_start_character + 1, current_character - lexeme_start_character - 1);
  addToken(TokenType::STRING, value);
  advance();

}

void Scanner::scanNumber() {
  while (std::isdigit(peek())) {
    advance();
  }

  if (peek() == '.' && std::isdigit(peekNext())) {
    advance();

    while (std::isdigit(peek())) {
      advance();
    } 
  }

  addToken(TokenType::NUMBER, std::stod(source.substr(lexeme_start_character, current_character - lexeme_start_character)));
}

void Scanner::scanIdentifier() {
  while (std::isalnum(peek())) advance();
  std::string text = source.substr(lexeme_start_character, current_character - lexeme_start_character);
  if (keywords.find(text) != keywords.end()) {
    addToken(keywords[text]);
  } else {
    addToken(TokenType::IDENTIFIER);
  }
}