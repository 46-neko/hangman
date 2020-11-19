# hangman
A hangman text-based game made in C

# Build instructions
Build this with gcc doing the following: <br />
Unix: gcc -o hangman.out src/main.c src/libs/hangfunc.c <br />
Windows: gcc -o hangman.exe src/main.c src/libs/hangfunc.c <br />
You can change "hangman.out / .exe" for anything you like. <br />

# Wordlist instructions
You can change the wordlist, just make sure the first line of the file is the numeber of lines - 1.
For example:
The default 3words.hwl has a 50 lines, so the first line is the number 49.

# Wordlist folder
After you complied the game, make sure that the wordlist folder is in the same directory as the .out/.exe file.
