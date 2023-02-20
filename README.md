# General Nim
General Nim is a variation of the game of Nim in which two players take turns
removing tokens from a set of piles until there are no more tokens left to remove. 
(For more information, see here https://en.wikipedia.org/wiki/Nim.)

When limited to two players, one of the players will always have a winning strategy. To make things more interesting, this version allows any number of players to join and try to outsmart their friends. The winner is the last player to remove a token.

# Installation/Usage
Begin by cloning this repository onto your computer by **git** and `cd` into it.
```bash
git clone https://github.com/calvintran1478/Nim.git
cd Nim
```
Now compile nim.cpp as follows and run the executable.
```bash
gcc -o nim nim.cpp -lstdc++
./nim
```