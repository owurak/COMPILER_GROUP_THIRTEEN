// AI disclosure: AI was used for conceptual debugging guidance.
// The member reviewed, implemented, tested, and can explain this code.


#include "lexer.h"
#include <cctype>
#include <set>

static const std::set<std::string> KEYWORDS = {
    "if", "else", "while", "for", "do", "return", "break", "continue",
    "int", "float", "double", "char", "bool", "void", "string",
    "true", "false", "class", "struct", "const", "static"
};

static bool isAlpha(char c) { return std::isalpha(static_cast<unsigned char>(c)) || c == '_'; }
static bool isDigit(char c) { return std::isdigit(static_cast<unsigned char>(c)) != 0; }

// character `off` positions ahead of pos, or '\0' past the end
static char charAt(const std::string& s, size_t pos, size_t off) {
    return (pos + off < s.size()) ? s[pos + off] : '\0';
}

// 1. constructor, isAtEnd, peek, advance ---------------------------------
Lexer::Lexer(const std::string& source)
    : src(source), pos(0), line(1), column(1),
      unterminatedComment(false), commentStartLine(0), commentStartColumn(0) {
}

bool Lexer::isAtEnd() const {
    return pos >= src.size();
}

char Lexer::peek() const {
    return isAtEnd() ? '\0' : src[pos];
}

char Lexer::advance() {
    char c = src[pos++];
    if (c == '\n') { line++; column = 1; }
    else           { column++; }
    return c;
}

// 2. skipWhitespaceAndComments (tracks line via advance) -----------------
void Lexer::skipWhitespaceAndComments() {
    while (!isAtEnd()) {
        char c = peek();
        if (std::isspace(static_cast<unsigned char>(c))) {
            advance();
        } else if (c == '/' && charAt(src, pos, 1) == '/') {
            while (!isAtEnd() && peek() != '\n') advance();
        } else if (c == '/' && charAt(src, pos, 1) == '*') {
            commentStartLine = line;        // save BEFORE consuming "/*"
            commentStartColumn = column;
            advance(); advance();
            while (!isAtEnd() && !(peek() == '*' && charAt(src, pos, 1) == '/')) advance();
            if (!isAtEnd()) {
                advance(); advance();       // found */
            } else {
                unterminatedComment = true; // hit EOF first
            }
        } else {
            break;
        }
    }
}

// 3. readIdentifierOrKeyword ----------------------------------------------
Token Lexer::readIdentifierOrKeyword() {
    int startLine = line, startCol = column;
    std::string lex;
    while (isAlpha(peek()) || isDigit(peek())) lex += advance();
    TokenType type = KEYWORDS.count(lex) ? TokenType::KEYWORD : TokenType::IDENTIFIER;
    return {type, lex, startLine, startCol};
}

// 4. readNumber -------------------------------------------------------------
Token Lexer::readNumber() {
    int startLine = line, startCol = column;
    std::string lex;
    bool isFloat = false;

    while (isDigit(peek())) lex += advance();

    if (peek() == '.' && isDigit(charAt(src, pos, 1))) {
        isFloat = true;
        lex += advance();
        while (isDigit(peek())) lex += advance();
    }

    if (peek() == 'e' || peek() == 'E') {
        size_t off = 1;
        if (charAt(src, pos, off) == '+' || charAt(src, pos, off) == '-') off++;
        if (isDigit(charAt(src, pos, off))) {
            isFloat = true;
            for (size_t i = 0; i < off; i++) lex += advance();
            while (isDigit(peek())) lex += advance();
        }
    }

    // number glued to letters (12abc) -> INVALID
    if (isAlpha(peek())) {
        while (isAlpha(peek()) || isDigit(peek())) lex += advance();
        return {TokenType::INVALID, lex, startLine, startCol};
    }

    return {isFloat ? TokenType::FLOAT : TokenType::INTEGER, lex, startLine, startCol};
}

// 5. getNextToken + INVALID handling ---------------------------------------
Token Lexer::getNextToken() {
    skipWhitespaceAndComments();

    if (unterminatedComment) {              // must come before isAtEnd()
        unterminatedComment = false;        // report only once
        return {TokenType::INVALID, "/*", commentStartLine, commentStartColumn};
    }

    if (isAtEnd()) return {TokenType::END_OF_FILE, "", line, column};

    char c = peek();
    if (isAlpha(c)) return readIdentifierOrKeyword();
    if (isDigit(c)) return readNumber();

    int startLine = line, startCol = column;

    // string literal
    if (c == '"') {
        std::string lex;
        lex += advance();
        while (!isAtEnd() && peek() != '"' && peek() != '\n') {
            if (peek() == '\\' && charAt(src, pos, 1) != '\0' && charAt(src, pos, 1) != '\n')
                lex += advance();
            lex += advance();
        }
        if (peek() == '"') {
            lex += advance();
            return {TokenType::STRING, lex, startLine, startCol};
        }
        return {TokenType::INVALID, lex, startLine, startCol};  // unterminated
    }

    // two-character operators (longest match first)
    static const char* ops2[] = {"==", "!=", "<=", ">=", "&&", "||", "++", "--",
                                 "+=", "-=", "*=", "/=", "%=", "->"};
    for (const char* op : ops2) {
        if (c == op[0] && charAt(src, pos, 1) == op[1]) {
            advance(); advance();
            return {TokenType::OPERATOR, op, startLine, startCol};
        }
    }

    static const std::string ops1  = "+-*/%=<>!&|^~";
    static const std::string punct = "(){}[];,.:?";

    if (ops1.find(c) != std::string::npos) {
        advance();
        return {TokenType::OPERATOR, std::string(1, c), startLine, startCol};
    }
    if (punct.find(c) != std::string::npos) {
        advance();
        return {TokenType::PUNCTUATION, std::string(1, c), startLine, startCol};
    }

    // unknown character -> INVALID (always consume so we never loop forever)
    advance();
    return {TokenType::INVALID, std::string(1, c), startLine, startCol};
}

// 6. tokenTypeToString -----------------------------------------------------
std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::KEYWORD:     return "KEYWORD";
        case TokenType::IDENTIFIER:  return "IDENTIFIER";
        case TokenType::INTEGER:     return "INTEGER";
        case TokenType::FLOAT:       return "FLOAT";
        case TokenType::STRING:      return "STRING";
        case TokenType::OPERATOR:    return "OPERATOR";
        case TokenType::PUNCTUATION: return "PUNCTUATION";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        case TokenType::INVALID:     return "INVALID";
    }
    return "UNKNOWN";
}