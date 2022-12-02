# Dungeon Escape

------------------------
**HOW TO COMPILE AND RUN**
------------------------
Compile: g++ -std=c++17 project3.cpp Game.cpp Merchant.cpp Inventory.cpp Party.cpp Member.cpp Dungeon.cpp Map.cpp Monster.cpp Riddles.cpp

Run: ./a.out
------------------------
**DEPENDENCIES**
------------------------
Game.h, Merchant.h, Inventory.h, Party.h, Member.h, Dungeon.h, Map.h, Monster.h, Riddles.h, must be in the same directory as the cpp 
files in order to compile.
------------------------
**ABOUT THIS PROJECT**
------------------------
This project is developing a single player Dungeon Escape game where the user is prompted to enter their player name
and the names of four NPC party members. The player must then find a way to escape the dungeon and kill an
evil sorcerer. Along the way they will be able to fight monsters, speak to merchants, find treasure, and solve puzzles.
The game ends when either a loss condition is met or the player leaves through the dungeon exit after defeating the sorcerer.