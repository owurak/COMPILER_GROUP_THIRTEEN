// AI disclosure: AI was used for conceptual debugging guidance.
// The member reviewed and implemented the interface changes.

#pragma once
#include <cstddef>
#include <string>
#include "token.h"

// MEMBER 1 - Lexer interface

class Lexer {
public:
    explicit Lexer(const std::string& source);
    Token getNextToken();
    bool isAtEnd() const;
private:
    std::string src;
    size_t pos;
    int line;
    int column;
    bool unterminatedComment;   // set when /* has no closing */
    int commentStartLine;       // where the unfinished /* began
    int commentStartColumn;
    char peek() const;
    char advance();
    void skipWhitespaceAndComments();
    Token readIdentifierOrKeyword();
    Token readNumber();
};