#pragma once

#include <string>

// Parser output types.
// Current design: stop at the first syntax error (no recovery, no AST yet).
// The group can extend ParseResult later if an AST or multiple errors are needed.

struct ParseError {
    int line;
    int column;
    std::string message;
};

struct ParseResult {
    bool success;
    ParseError error;   // only meaningful when success == false
};
