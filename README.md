# cpplox

This is my implementation of the programming language lox, of the book [Crafting interpreters](https://craftinginterpreters.com/). In the original work, he works first with Java, and then with C. This project seeks to remplace the Java part with an C++ one.

## Current version - 0.2.0

This version represents the version of the language after the second chapter of the book. As I implemented, the program can realise two tasks: being a scanner or printing an expression in polish notation.
### Scanner
When using  this function, the programk scans the code, which can be provenient both of a file or an interactive prompt, saving the tokens in a vector and printing them for the user to see.

To compile, simply run the `make scanner` on the home folder. It will produce an executable called `cpplox`. This file can be ran with a an argument, for example, `./cpplox test.txt` to run a file, or without any arguments to open a interactive shell.

### Printing in polish notation
It is possible to print an expression in polish notation. However, the expression must be manually crafted on the main function of `/src/printer/AstPrinter.cpp`. The default expression that I used to test is  `-123*(45.67)`, which becomes `(* (-123) (45.67)` in polish notation. The expression can contain only literals,binary operators, unary operators and parenthes.

To run this program, just run `make astTree` and run the executable `printTree`.

The implement of this feature uses the Visitor Pattern to facilitate adding new behaviors for the classes. The declarations are done in the file `/include/astTree.h`, and any program that wants to utilise this header must implement the visitor functions.
This file is created by the script `./src/tools/astGenerator.py` to allow for an easier expansion when I implement the other classes, such as functions and variables. Running this python script will create the header file on the include folder.


## Previous versions
Here are the links for the previous versions of the project:
- [Version 0.1.0](https://github.com/artur0312/cpplox/tree/8d248c15629bec356a08944b4431604f3cdf83a8)
