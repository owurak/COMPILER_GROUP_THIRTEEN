# Lexer Bug Report — Member 2

> AI disclosure: AI was used for documentation formatting. Test results were run and verified by the member.

Run command:

```bash
sh test/scanner/run_tests.sh /path/to/compiler
```

| Test stage | Result |
|---|---|
| Before BUG-1 fix | passed 19, failed 1 |
| After BUG-1 fix | **passed 20, failed 0** |

## BUG-1: Unterminated block comment accepted silently

**Status: FIXED and verified.**

- Test file: `test/scanner/invalid/invalid07.txt` (a comment opens on line 2 and never closes)
- Expected: an `INVALID` token at the start of the comment (`2:1`) and exit code `2`
- Original behavior: the comment swallowed the rest of the file, no `INVALID` token was produced, and the exit code was `0`
- Where: `src/lexer/Lexer.cpp`, `skipWhitespaceAndComments()`, block-comment branch. The loop reached end of file without reporting an error.
- Resolution: The lexer was updated to detect an unterminated block comment and report it as an `INVALID` token at the opening comment location.

Verification after the fix:

| Input | Result |
|---|---|
| `invalid07.txt` | `INVALID(/*) 2:1`, exit code 2 |
| `/* ok */ int x;` | no `INVALID` token, exit code 0 |
| `/**/ int y;` | no `INVALID` token, exit code 0 |
| `/*` alone | `INVALID(/*) 1:1`, exit code 2 |

Full scanner test run: **passed 20, failed 0**.

## Draft specification decisions to confirm

These are not bugs. They are choices the lexer currently makes that the lecturer's
specification may change.

- `.5` is lexed as `.` followed by `5` (not a float).
- `1.` is lexed as `1` followed by `.`.
- `5..3` is lexed as `5`, `.`, `.`, `3`.
- Character literals such as `'a'` are not supported and are reported as `INVALID`.
- The keyword list and the two-character operator list are working assumptions (see `docs/token-spec.md`).
