# Parser

A parser is a software component that processes input data, typically text, and builds a data structure, such as a parse tree or abstract syntax tree, which represents the syntactic structure of the input. The parser is often preceded by a lexer, which converts the input text into a sequence of tokens.

In our context the parser transform the nodes obtained after our lexical analysis. This nodes will be use to create another list of nodes that will gather the needed informations for the command execution.

## Code

```mermaid
graph TB

classDef word fill:#f9f, color:#000;
classDef dquote fill:#fcf, color:#000;
classDef dollar fill:#f4f, color:#000;
classDef redir fill:#0c5, color:#000;
classDef pipe fill:#f00, color:#000;

  subgraph Lexer
    direction LR
    subgraph Node1
      A[<<]
      A -.- DLESS:::redir
    end
    Node1 --> Node2
    subgraph Node2
      B[LIMITER]
      B -.- WORD1["WORD"]:::word
    end
    Node2 --> Node3
    subgraph Node3
      C[cmd]
      C -.- WORD2["WORD"]:::word
    end
    Node3 --> Node4
    subgraph Node4
      D["|"]
      D -.- PIPE:::pipe
    end
    Node4 --> Node5
    subgraph Node5
      E[cmd2]
      E -.- WORD3["WORD"]:::word
    end
    Node5 --> Node6
    subgraph Node6
      F["argument1"]
      F -.- DQUOTE:::dquote
    end
    Node6 --> Node7
    subgraph Node7
      G["arg_as_variable"]
      G -.- DOLLAR:::dollar
    end
    Node7 --> Node8
    subgraph Node8
      H[>]
      H -.- GREATER:::redir
    end
    Node8 --> Node9
    subgraph Node9
      I["outfile"]
      I -.- WORD4["WORD"]:::word
    end
  end

  Lexer --> Parser
  subgraph Parser
    direction TB
    subgraph Cmd1
      subgraph Args
        Args_0["arg0 = cmd"]
      end
      subgraph Inf
        Inf_0["inf0 = here_doc"]
      end
    end
    subgraph Cmd2
      subgraph Cmd2_Args
        Cmd2_Args_0["arg0 = cmd2"]
        Cmd2_Args_1["arg1 = argument1"]
        Cmd2_Args_2["arg2 = arg_as_variable"]
      end
      subgraph Cmd2_Out
        Cmd2_outf_0["outf0 = outfile"]
      end
    end
  end


```

### Case:

If element is `WORD` , `DQUOTE` or `DOLLAR` and they are not separated by a space or special character, they are part of the same argument.

Example:
```sh
echo Hello$USER
```

```shell
Hellorcutte
```

and not:

```shell
Hello rcutte
```
## Notions

:bookmark_tabs: [Parser - Definition and Types](https://www.techtarget.com/searchapparchitecture/definition/parser)
