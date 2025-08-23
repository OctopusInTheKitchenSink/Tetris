#ifndef H_FILE_TETRIS
#define H_FILE_TETRIS

#define FIELD_WIDTH 11  // 22
#define FIELD_HEIGHT 22
#define ONE_LINE 100
#define TWO_LINES 300
#define THREE_LINES 700
#define FOUR_LINES 1500
#define SPEED_UP 600
#define HIGHEST_LINE 0
#define START_SPEED 500  // 100
#define COUNT_OF_FIGURES 7
#define START_TIMEOUT 1000
#define START_POSITION 0
#define INFO_START_POSITION 23
#define INFO_WIDTH 19
#define FIGURE_PART 4
#define MOVING_PLACE 8
#define EMPTY_PLACE 0
#define FIXED_PLACE 9
#define MOVE_LEFT 1
#define MOVE_RIGHT 2
#define MOVE_DOWN 3
#define ROTATING 4
#define MAX_SPEED 10
#define COUNT_OF_ROTATIONS 4
#define ZERO_X 0
#define ZERO_Y 0
#define REAL_FIELD_WIDTH 10

#include <stdlib.h>
#include <time.h>

/**
 * @brief Enumeration defining the possible states of the "Tetris" game.
 *
 * `game_state` is an enumeration that defines the various states
 * in which the game can be. Each state represents a specific
 * stage or mode of the gameplay:
 *   - `move_left`: Waiting for the figure to move left.
 *   - `move_right`: Waiting for the figure to move right.
 *   - `fall`: Waiting for the figure to fall down.
 *   - `rotation`: Waiting for the figure to rotate.
 *   - `pause`: The game is in a paused state.
 *   - `game_over`: The game is over (loss).
 *   - `terminate`: The game is terminated (user exit).
 *   - `ready_to_start`: The game is ready to start (waiting for the START key
 * to be pressed).
 *   - `no_signal`: No active signal from the user (waiting for input).
 *   - `shift`: The figure needs to shift down (automatic fall).
 *   - `next_figure`: A new figure needs to be created and placed on the game
 * field.
 *
 * This enumeration is used to manage the game logic and
 * determine the actions that need to be performed in each state.
 */
typedef enum {
  ready_to_start,
  pause,
  terminate,
  move_left,
  move_right,
  no_signal,
  fall,
  rotation,
  game_over,
  shift,  //
  next_figure,
} game_state;

#endif
