# Sokoban Game

This is a simple console-based Sokoban game written in C.

## How to Compile

To compile the game, navigate to the project directory in your terminal and run the following command:

```bash
gcc *.c -o sokoban
```

## How to Run

After successful compilation, you can run the game with:

```bash
./sokoban
```

## How to Play

Upon starting the game, you will be presented with a main menu:

```
[INFO] Menu options: 1. New game. 2. Save game. 3. Load game. 4. Resume game. 5. Exit.
[INFO] Enter an integer [1-5]:
```

### Main Menu Options:

1.  **New game:** Start a fresh game. You will be prompted to choose a level (1-4).
2.  **Save game:** Save your current game progress to a file. You will be asked to enter a filename (e.g., `my_game.txt`).
3.  **Load game:** Load a previously saved game from a file. You will be asked to enter the filename.
4.  **Resume game:** Continue playing your last active game.
5.  **Exit:** Quit the game application.

### In-Game Options:

When playing a level, you will see the game board and a list of options:

```
Current Level:X, Current Score:Y
#######
###G###
###B###
#GBABG#
###B###
###G###
#######
Options: 1. Up | 2. Right | 3. Down | 4. Left | 5. Show best move 6. Quit game
[INFO] Enter a game option [1-6]:
```

*   **1. Up / 2. Right / 3. Down / 4. Left:** Move the player (represented by 'A') in the chosen direction. The goal is to push all boxes ('B') onto the target locations ('G').
*   **5. Show best move:** (Functionality not detailed in example, but typically suggests an optimal move).
*   **6. Quit game:** Return to the main menu.