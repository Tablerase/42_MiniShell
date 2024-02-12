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

`\n` = NEWLINE

`\r` = CARRIAGE

`\v` = VERTICAL

`\f` = FORMFEED

### check for empty tokens

`|` no empty pipe

`>` no empty greater

`<` no empty less

`>>` no empty dgreater

`<<` no empty dless

## Metacharacters

Metacharacters are characters that have a special meaning in a programming language or command interpreter. They are used to control the flow of a program or to manipulate text. For example, in the C programming language, the `*` character is used to declare a pointer, and the `&` character is used to get the address of a variable. In the Unix shell, the `|` character is used to pipe the output of one command into the input of another command.

### $ (DOLLAR)

The dollar sign is a metacharacter in many programming languages and command interpreters. In the Unix shell, the dollar sign is used to indicate that a word is a variable name, and the value of the variable should be substituted in its place. For example, if the variable `foo` has the value `bar`, then the command `echo $foo` will print `bar`.

### Metacharacter Injection

Many systems, such as `SQL interpreters` and the `command line shell`, have metacharacters, that is, characters in their input that are not interpreted as data. Such characters might commands, or delimit data from commands or other data. If there’s a language specification for that system’s interface that you’re using, then it certainly has metacharacters. If your program invokes those other systems and allows attackers to insert such metacharacters, the usual result is that an attacker can completely control your program.

#### Shell Injection

Many metacharacter problems involve shell metacharacters. An attack that tries to exploit a vulnerabliity in shell metacharacter processing is called a shell injection attack. For example, the standard Unix-like command shell (typically stored in /bin/sh) interprets a number of characters specially. If these characters are sent to the shell, then their special interpretation will be used unless escaped; this fact can be used to break programs. 

<details>
<summary>Example of shell injection</summary>

For example, the following command line:

```sh
ls -l $HOME
```

will list the contents of the user's home directory. However, if the user's home directory is `/home/username; rm -rf /`, then the following command line:

```sh
ls -l $HOME
```

will list the contents of the user's home directory and then delete everything in the root directory. This is because the shell will interpret the $HOME variable and execute the command:

```sh
ls -l /home/username; rm -rf /
```

</details>
