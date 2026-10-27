#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "../lexer/token.h"
#include "ParseResult.h"

// Parser setup only.
// Grammar rules, AST construction and error recovery are added after group agreement.

class Parser {
public:
    // Takes the token stream produced by the lexer.
    explicit Parser(const std::vector<Token>& inputTokens);

    // Top-level entry point. Grammar logic is TODO (group).
    ParseResult parseProgram();

private:
    std::vector<Token> tokens;
    std::size_t current = 0;

    // Token-navigation helpers (definitions are TODO in Parser.cpp).
    bool isAtEnd() const;                  // true when peek() is END_OF_FILE
    const Token& peek() const;             // token at 'current', no consumption
    const Token& previous() const;         // most recently consumed token
    const Token& advance();                // consume and return the current token

    // Because token types are generic, rules will need type AND lexeme.
    bool check(TokenType type) const;
    bool check(TokenType type, const std::string& lexeme) const;
    // e.g. check(TokenType::KEYWORD, "if"), check(TokenType::PUNCTUATION, ";")

    // TODO (group): match/expect, error reporting, and one method per grammar rule.
};
