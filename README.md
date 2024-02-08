# MiniShell

```mermaid
graph TD
  classDef exit fill:#77b,stroke:#333,stroke-width:2px,color:#fff;
  classDef cmd fill:#9f9,color:#000;
  classDef msg fill:#bcd,color:#000;
  classDef file fill:#f9f,color:#000;
    A[MiniShell] --> B[Main]
    B --> readline[Readline]
    readline --> readline
    readline --> parser["Parsing\n '' '' : allow $var\n' '\n |\n <  > \n<<  >> "]
    readline -.- |"if empty line with Ctrl-D"|exit_shell
    readline -.- |"if text on line with Ctrl-D"|nothing
    parser -.- lexer[Lexing]
    parser -.-x |Error:\nif quotes doesnt end| parse_error[Parse Error\nmessage]:::msg
    parse_error -->|1| Exit:::exit
    parser <--> list[Listing]
    parser --> |"<< EOF"|here_doc[Here Doc]
    here_doc --> readline2[Readline]
    readline2 --> here_doc_file[Here Doc File]:::file
    here_doc_file --> list
    parser --> command{Commands}
    command -->|1| single[Single Command]:::cmd
    command -->|> 1| multi[Multi Commands]
    multi --> loop((Loop))
    loop -->|- 1| loop
    loop --> single
    single --> exec{Execution}
    single --> builtin[Builtin]:::cmd
    exec -.- direction[Direction]
    direction -.- file[File]:::file
    file -.- access[Access]
    direction -.- pipe[Pipe]:::file
    exec -.- env[Env]
    env -.- path[Path]
    path -.- access
    exec -.- execve:::cmd
    builtin --> Exit
    execve --> Exit

    signal[Signal]
    signal --> SIGQUIT[Ctrl-\] -.- nothing[Do Nothing]
    signal --> SIGEOF[Ctrl-D] -.- exit_shell[Exit Shell]
    signal --> SIGINT[Ctrl-C] -.- kill[Send SIGKILL]
```

## Listing

- types:
  - pipe `|`
  - redirection
    - input `<`
    - output `>`
    - append `>>`
    - here_doc `<<` followed LIMITER
  - file
    - infile
    - outfile
  - command
    - list of args[0];
  - args
    - list of args

### Redirection

```mermaid
graph LR;
    redir_in[<] --- in_file[File] --> cmd --- args --> redir_out[>] --- out_file[File]
```
- input
  - link to stdin of the command before the next pipe
  - in case multiple `<` input with the same command, dup2 in order of appearance:
    - dup2(fd, 0)
    - dup2(fd2, 0)
- output
- append
- here_doc

Example of redir << here_doc and input:
```shell
$> << EOF cat > test | << EOF cat | wc
> jf
> jf
> EOF
> df
> df
> df
> EOF
      3       3       9
$> cat test
jf
jf
```

Example of redir > output:
```shell
<< EOF cat | cat > test_output | < test cat > test_output2
> test1
> test1
> test1
> EOF
$> cat test_output
test1
test1
test1
$> cat test_output2
jf
jf
```

### Parser

### Here Doc

Search for `<<` and `LIMITER` and replace the line with the content until `LIMITER` is found.

Launch readline but do not save the line in the history.

```c
line = readline("here_doc> ");
```

Store content in a heredoc file. This heredo file will be stored as an infile and also stored in a list of heredoc files to be deleted at the end of the program.
