\# Parser Interface



Parser input: `std::vector<Token>` produced by the lexer.



The parser checks both token type and lexeme because lexer tokens are generic.



Examples:



\- `KEYWORD` + `int`

\- `KEYWORD` + `if`

\- `OPERATOR` + `=`

\- `PUNCTUATION` + `;`

\- `PUNCTUATION` + `{`



Parser output:

\- success; or

\- syntax error with line, column, and message.

