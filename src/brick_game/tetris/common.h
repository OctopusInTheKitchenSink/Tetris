#ifndef COMMON_H_FILE
#define COMMON_H_FILE
#include <stdbool.h>

#include "../../tetris.h"

/**
 * @brief Enumeration defining possible user actions.
 *
 * The `UserAction_t` enumeration defines a set of actions that a user can
 * perform in the game. Each action is assigned a unique
 * integer value.
 *
 * @var Start     Start the game.
 * @var Pause     Pause/resume the game.
 * @var Terminate Terminate the game.
 * @var Left      Move the figure left.
 * @var Right     Move the figure right.
 * @var Up        Placeholder (in this game).
 * @var Down      Accelerate the figure's fall.
 * @var Action    Rotate the figure.
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @brief Structure containing information about the game state.
 *
 * The `GameInfo_t` structure combines all the necessary data to represent the
 * current game state, including the game field, information about the next
 * figure, score, high score, level, speed, and pause state.
 *
 * @var field       A two-dimensional array representing the game field.
 *                  Each element of the array contains information about what is
 *                  in that cell of the field (empty, part of a figure, etc.).
 * @var next        A two-dimensional array containing the coordinates of the
 * parts of the next figure that should appear in the game.
 * @var score       The player's current score.
 * @var high_score  The player's high score (maximum score achieved).
 * @var level       The current game level.
 * @var speed       The current game speed (determines the speed at which
 * figures fall).
 * @var pause       The current game state (pause, playing, game over, etc.).
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * @brief Handles user input and modifies the game state.
 *
 * The `userInput` function processes actions performed by the user and
 * modifies the game state stored in the `GameInfo_t` structure accordingly.
 *
 * The function performs the following actions:
 *   - Initializes the game on the first call (if `init == 1`), calling the
 * `init_game` function.
 *   - Resets the initialization flag if the game is in the `game_over` state.
 *   - Depending on the user's action (`action`) and the current game state
 *     (`game->pause`), performs the corresponding actions:
 *     - `Start`: Starts the game if it is in the `ready_to_start` state.
 *     - `Pause`: Pauses the game.
 *     - `Terminate`: Terminates the game.
 *     - `Left`: Sets the game state to `move_left` (move the figure left).
 *     - `Right`: Sets the game state to `move_right` (move the figure right).
 *     - `Down`: Sets the game state to `fall` (force the figure to fall).
 *     - `Action`: Sets the game state to `rotation` (rotate the figure).
 *   - If the game was paused, then pressing `Start` again unpauses it, pressing
 * `Terminate` terminates the game.
 *
 * @param action  The user's action (defined in the `UserAction_t` enumeration).
 * @param hold    A flag indicating whether the button is being held down (not
 * used in this implementation).
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Updates the current game state.
 *
 * The `updateCurrentState` function performs the main steps of updating the
 * game state at each step of the game loop. It handles the logic of falling
 * figures, line checks, new figure generation, and game over.
 *
 * The function performs the following actions:
 *   - Obtains pointers to the `GameInfo_t` and `Figure_position` structures
 * using the `set_game_info` and `set_figure_info` functions, respectively.
 *   - Calls the `game_active` function to handle actions related to the
 *     current game state.
 *   - If the game is not in the `no_signal` state and the figure cannot
 *     move down, it fixes the figure on the field and calls the `check_field`
 * function to check and handle completed lines.
 *   - If the game state is equal to `next_figure` (the figure has reached the
 * bottom or has been fixed), it generates a new figure, updates information
 * about the next figure, and sets the game state to `shift` (need to shift the
 *     figure down).
 *   - If the game is over (`game->pause == terminate` or `game->pause ==
 *     game_over`), it frees the memory allocated for game resources by calling
 *     the `free_game` function.
 *
 * @return A copy of the `GameInfo_t` structure containing the updated game
 * state.
 */
GameInfo_t updateCurrentState();

#endif
