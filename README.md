# Compiler Project (Group Thirteen)

> **DRAFT.** This README describes what the current lexer implementation recognizes.
> The class mini-language has not been confirmed by the lecturer yet. The keywords
> (`int`, `if`, `while`, ...), number formats, strings, and operators listed here are
> working assumptions, not the official language definition.

> AI disclosure: AI was used for documentation drafting/formatting. The member reviewed and verified the repository information.

A hand-written compiler front end in C++17. Phase 1 implements a lexer that turns
source text into tokens and reports invalid lexical input without stopping.

## Setup

You need a C++17 compiler (g++ 9+, Clang, or MSVC) and CMake 3.16+.
See [BUILD.md](BUILD.md) for complete build instructions.

```text
git clone <repo-url>
cd <repo-folder>
cmake -B build
cmake --build build
```

## Architecture

```text
source file --> main.cpp --> Lexer --> Token stream --> printed to stdout
                (reads file)  (src/lexer)  (token.h)
```

| Part | File | Job |
|---|---|---|
| Entry point | `src/main.cpp` | Reads the file, calls `getNextToken()` until `END_OF_FILE`, prints each token |
| Token types | `src/lexer/token.h` | `TokenType` enum, `Token {type, lexeme, line, column}`, `tokenTypeToString` |
| Lexer | `src/lexer/lexer.h` and `src/lexer/Lexer.cpp` | Skips whitespace/comments and reads identifiers, keywords, numbers, strings, operators and punctuation using draft rules; unknown input becomes `INVALID` |
| Token spec | `docs/token-spec.md` | Draft rules the lexer currently follows; items marked *confirm* await the lecturer |

The lexer does not stop at bad input: it emits an `INVALID` token, consumes the
offending text, and continues, so one run reports every lexical error.

## Folder Layout

```text
src/            Main program and lexer source files
test/scanner/   Scanner valid/invalid tests and test script
docs/           Token specification, bug reports, and project documentation
CMakeLists.txt  CMake build configuration
BUILD.md        Build and run instructions
```

## Testing

Scanner tests are located in:

```text
test/scanner/
```

Run them from Git Bash:

```bash
sh test/scanner/run_tests.sh /path/to/compiler
```

Example:

```bash
sh test/scanner/run_tests.sh /c/Users/your-name/Desktop/compiler.exe
```

Current Phase 1 scanner test result:

```text
passed 20, failed 0
```
