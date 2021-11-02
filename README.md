
<a id="orgd4f0f0d"></a>

# cpplox

This is my implementation of the programming language lox, of the book [Crafting interpreters](https://craftinginterpreters.com/). In the original work, he works first with Java, and then with C. This project seeks to remplace the Java part with an C++ one.


<a id="org024bb81"></a>

## Current version - 0.1.0

This version represents the version of the language after the first chapter of the book. At this point, the program is simple a scanner. It scans the code, which can be provenient both of a file or an interactive prompt, saving the tokens in a vector and printing them for the user to see.
To compile, simply run the makefile on the home folder. It will produce an executable called cpplox. This file can be ran with a an argument, for example, `./cpplox test.txt` to run a file, or without any arguments to open a interactive shell.

