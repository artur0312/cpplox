# cpplox

This is my implementation of the programming language lox, of the book [Crafting interpreters](https://craftinginterpreters.com/). In the original work, he works first with Java, and then with C. This project seeks to remplace the Java part with an C++ one.

## Current version - 0.3.0

This version represents the version of the language after chapter 6 of the book. The program can read input from a file or in an interactive prompt. Then, it parser this expression and prints it in polish notation. For example, if the input is `-123 * 45.67`, the output will be `(* (-123) (45.67)`.

The only possible inputs are floating point numbers, string literals and operators. The possible operators are `*`, `/`, `+`, `-`,`==`,`!=`, `>`, `>=`, `<`, `<=`, and `!`. It is important to notice that `-` can be both an unary or a binary operator, depending if it is at the beggining of the expression or not.

To compile, simply run `make` on the home folder. It will produce an executable called `cpplox`. This file can be ran with a an argument, for example, `./cpplox test.txt` to run a file, or without any arguments to open a interactive shell.

## Previous versions
Here are the links for the previous versions of the project:
- [Version 0.1.0](https://github.com/artur0312/cpplox/tree/8d248c15629bec356a08944b4431604f3cdf83a8)

- [Version 0.2.0](https://github.com/artur0312/cpplox/tree/be2cbf555a08bcf48b6221399496e7964e36bdfa)
