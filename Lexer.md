# Lexer

A lexer, also known as a tokenizer, breaks a string down into smaller pieces, called tokens. These tokens can be words, numbers, symbols, or other meaningful elements. The lexer is the first step in the process of interpreting a string of characters, and it plays a crucial role in the process of parsing.

The lexer takes a string of characters as input and produces a sequence of tokens as output. Each token represents a single element of the input string, and the sequence of tokens represents the structure of the input string.

The output of the lexer is typically fed into a parser, which uses the tokens to build a more structured representation of the input string, such as an abstract syntax tree or a sequence of instructions.

## Tokens
`"printable"` or `text without other lexical type` = WORD

`<` = LESS

`>` = GREATER

`>>` = DGREATER

`<<` = DLESS

`|` = PIPE

`$` = DOLLAR

`'` = QUOTE

`"` = DQUOTE

### isspace

` ` = SPACE

`\t` = TAB

