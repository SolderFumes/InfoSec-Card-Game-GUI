# InfoSec-Card-Game-GUI

GUI-based version of https://github.com/SolderFumes/InfoSec-Card-Game using SDL2!

# Install
There is no built release for this game, but feel free to try and compile the game from the source code! There are a few dependencies that you're going to have to figure out on your own until a release is made available. 

# How to Play
The game is played between two human players on the same device. On each turn, the current player chooses to either play a card or skip their turn. There are two types of cards, **exploit cards** and **defense cards**. 
<br><br>**Defense cards**, when played, move to the active area of the board. They act as a line of defense from the opposing player's **exploit cards**. Exploit cards must be clicked once to select them. Once selected, the target must be clicked. The target can be the opposing player or one of their defense cards, but a player with *any* active defense card cannot be directly attacked.
<br><br>Each player has **bandwidth**, which acts as a mana system. Each card has a bandwidth cost and may only be used if the player has sufficient bandwidth. Players gain bandwidth after every turn.
The game will continue forever until one player's HP hits zero! Good luck and have fun!
