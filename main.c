// Libraries to import
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
// The snake can be represented by the coordinates of its body stored in two
// arrays: One Array for x-axis coordinates. One Array for y-axis coordinates.
// Random food Positioning

// ht and width of game
#define HEIGHT 20
#define WIDTH 20

// length of snake
int snakeLen;
// fruit coordinates
int fruitX, fruitY;
int fruitEaten; // flag to determine whhether the fruit is eaten or not
#define LEN 100
// array to store overall snake coordinates
int snakeX[LEN], snakeY[LEN];

int gameover = 0; // gameover flag
int key, score;   // keyboard key & total score
int headX, headY; // coordinates of the head of snake
int generateFruit() {
  // Generate a random position for the fruit, ensuring it's not on the edges
  fruitX = rand() % (WIDTH - 2) + 1;  // Fruit X in range [1, WIDTH-2]
  fruitY = rand() % (HEIGHT - 2) + 1; // Fruit Y in range [1, HEIGHT-2]

  return 0;
}

#include <termios.h>

// Save the original terminal attributes so we can restore them later
struct termios orig_termios;

void enableRawMode() {
  struct termios raw;

  // Get the current terminal settings
  tcgetattr(STDIN_FILENO, &orig_termios);
  raw = orig_termios;

  // Disable canonical mode and echo
  raw.c_lflag &= ~(ICANON | ECHO);

  // Set the terminal to the new settings immediately
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode() {
  // Restore the original terminal settings
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
// int setup() {
//      // Initialize snake starting position at the center
//      headX = WIDTH / 2;
//      headY = HEIGHT / 2;
//      snakeLen = 1; // Start with length 1
//      snakeX[0] = headX; // Set the initial head position
//      snakeY[0] = headY; // Set the initial head position
//      fruitEaten = 0; // Reset fruit eaten flag
//      score = 0;      // Reset score
//      generateFruit(); // Generate the first fruit
//      return 0;
//  }

int setup() {
  snakeLen = 1; // Start with length 1
  headX = WIDTH / 2;
  headY = HEIGHT / 2;
  snakeX[0] = headX; // Set the initial head position
  snakeY[0] = headY; // Set the initial head position
  fruitEaten = 0;
  generateFruit();
  score = 0;
  return 0;
}
void printLine() {
  for (int i = 0; i < WIDTH + 2; i++) {
    printf("#");
  }
}
int draw() {
  system("clear");
  printLine();
  printf("\n");
  for (int j = 0; j <= HEIGHT; j++) {
    for (int i = 0; i <= WIDTH; i++) {
      int empty = 0;
      if (i == 0 || i == WIDTH) {
        printf("#");
      }
      if (i == fruitX && j == fruitY) {
        empty = 1;
        printf("*");
      }
      if (i == headX && j == headY) {
        printf("O");
        empty = 1;
      } else {
        // empty = 0;
        for (int k = 0; k < snakeLen - 1; k++) {
          if (i == snakeX[k] && j == snakeY[k]) {
            printf("o");
            empty = 1;
          }
        }
      }
      if (!empty) {
        printf(" "); // prints whitespace
      }
    }
    printf("\n");
  }
  // printf("\n");
  printLine();
  printf("\n score: %d \n", score);
  return 0;
}

int input() {
  fd_set set;
  struct timeval timeout;

  // Set the timeout to 0 for non-blocking
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  // Initialize the set to include stdin (file descriptor 0)
  FD_ZERO(&set);
  FD_SET(0, &set);
  printf("hello from input()\n");
  // Check if input is available on stdin

  if (select(1, &set, NULL, NULL, &timeout) > 0) {
    char ch = getchar(); // Get the character from stdin
    printf("%c", ch);
    switch (tolower(ch)) {
      printf("%c", ch);
    case 'q':
      gameover = 1;
      break;
    case 'w':
      if (key != 1)
        key = 0; // Up, but prevent reversing direction
      printf("%d", key);
      break;
    case 's':
      if (key != 0)
        key = 1; // Down
      printf("%d", key);
      break;
    case 'a':
      if (key != 3)
        key = 2; // Left
      printf("%d", key);
      break;
    case 'd':
      if (key != 2)
        key = 3; // Right
      printf("%d", key);
      break;
    }
  }
  return 0;
}

int logic() {
  // Move the snake's body positions
  int prevX = snakeX[0];
  int prevY = snakeY[0];
  int tempX, tempY;

  // Update the head position in the array
  snakeX[0] = headX;
  snakeY[0] = headY;

  // Move the rest of the body
  for (int i = 1; i < snakeLen; i++) {
    tempX = snakeX[i];
    tempY = snakeY[i];
    snakeX[i] = prevX;
    snakeY[i] = prevY;
    prevX = tempX;
    prevY = tempY;
  }
  printf("%c\n", key);
  // Update the head's coordinates based on the direction (key)
  switch (key) {
  case 0: // Up
    headY--;
    break;
  case 1: // Down
    headY++;
    break;
  case 2: // Left
    headX--;
    break;
  case 3: // Right
    headX++;
    break;
  }

  // Check for collisions with the walls
  if (headX <= 0 || headX >= WIDTH || headY <= 0 || headY >= HEIGHT) {
    gameover = 1;
  }

  // Check for collision with the snake body
  for (int i = 1; i < snakeLen; i++) {
    if (snakeX[i] == headX && snakeY[i] == headY) {
      gameover = 1;
    }
  }

  // Check if the snake has eaten the fruit
  if (headX == fruitX && headY == fruitY) {
    generateFruit(); // Generate new fruit position
    score++;         // Increase score
    snakeLen++;      // Increase the snake length
  }

  return 0;
}

// main function
int main() {
  enableRawMode();
  // initial settings
  setup();

  float SLEEP_TIME;
  SLEEP_TIME = 10;

  // game loop
  while (!gameover) {
    draw();
    input();
    logic();
    SLEEP_TIME -= score;
    if (SLEEP_TIME == 0) {
      break;
      printf("game over you win completed the game\n");
    }
    usleep(SLEEP_TIME * 1e5); // sleep function from unistd.h
  }
}
