#include "Parser.h"

// AI disclosure: starter boilerplate only.
// Core parsing logic must be implemented and understood by the member.

Parser::Parser(const std::vector<Token>& inputTokens)
    : tokens(inputTokens), current(0) {
}

bool Parser::isAtEnd() const {
    // TODO Member 3:
    // Decide how END_OF_FILE is represented and checked.
    return true;
}

const Token& Parser::peek() const {
    // TODO Member 3:
    // Return the current token safely.
    return tokens.at(current);
}

const Token& Parser::previous() const {
    // TODO Member 3:
    // Return the previously consumed token safely.
    return tokens.at(current - 1);
}

const Token& Parser::advance() {
    // TODO Member 3:
    // Move to the next token, then return the consumed token.
    return tokens.at(current);
}

bool Parser::check(TokenType type) const {
    // TODO Member 3: compare peek().type with type (handle end of input).
    return false;
}

bool Parser::check(TokenType type, const std::string& lexeme) const {
    // TODO Member 3: compare both peek().type and peek().lexeme.
    return false;
}

ParseResult Parser::parseProgram() {
    // TODO Member 3:
    // Implement the top-level grammar rule here.
    //
    // Suggested overall behavior:
    // 1. Read statements until END_OF_FILE.
    // 2. Return success when all input follows grammar.
    // 3. Return syntax error with line/column when parsing fails.

    return {
        false,
        {0, 0, "Parser not implemented"}
    };
}
