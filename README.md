# snake_game_cli

This is a simple, terminal-based Snake Game written in C. It uses low-level terminal I/O to capture real-time keyboard input and moves the snake within a grid, eating food and growing longer with each bite. 

## Game Features

- **Real-Time Controls**: Control the snake's direction with `W`, `A`, `S`, and `D` keys, and press `Q` to quit the game.
- **Dynamic Gameplay**: The snake grows in length each time it eats a piece of food (`*`), increasing the challenge.
- **Game Over**: The game ends if the snake collides with the walls or itself.

## Getting Started

### Prerequisites

To build and run this project, you’ll need:
- **C Compiler**: Tested with `clang` and `gcc`.
- **Linux/Unix Terminal**: The game uses system calls (`select()` and `termios`) that are standard on Unix-like systems.

### Compilation and Running

Use `make` to compile and run the game:

```bash
# Clone the repository
git clone https://github.com/Akshat6133/snake_game_cli.git
cd snake_game_cli

# Build the project
make

# Run the game
./snake
```

To clean up compiled files:

```bash
make clean
```

### Controls

- `W` - Move Up
- `A` - Move Left
- `S` - Move Down
- `D` - Move Right
- `Q` - Quit the game

### Example Game Display

```
######################
#                    #
#                    #
#        *           #
#                    #
#                    #
#                    #
#                    #
#        Ooo         #
#                    #
#                    #
#                    #
#                    #
#                    #
######################
Score: 3
```

## Code Overview

### Files

- **`main.c`**: Contains the main game loop, drawing function, logic for movement, collision detection, and input handling.
- **`Makefile`**: Manages the build process with convenient targets for compiling and cleaning the project.

### Key Functions

- **`setup()`**: Initializes the snake, food position, and score.
- **`draw()`**: Renders the game board, snake, and score to the terminal.
- **`input()`**: Captures keyboard input to change the snake’s direction.
- **`logic()`**: Updates the snake’s position and checks for collisions or if the snake has eaten food.

## Notes

- **Raw Mode**: The game sets the terminal to raw mode to capture each keystroke without requiring Enter. This is restored to normal mode when the game exits.
- **Cross-Platform Compatibility**: This project is currently tested on Linux; modifications may be necessary for compatibility with other OS terminals.


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

