#ifndef H_FILE_BACKEND
#define H_FILE_BACKEND
#include <stdbool.h>
#include <stdio.h>

#include "./../../tetris.h"
#include "common.h"

/**
 * @brief Structure containing information about the position and state of the
 * current figure.
 *
 * The `Figure_position` structure is designed to store information about the
 * current figure in the "Tetris" game. It includes the following fields:
 *   - `x`: X coordinate, the figure's vertical displacement from its initial
 * position.
 *   - `y`: Y coordinate, the figure's horizontal displacement from its initial
 * position.
 *   - `rotation`: The current rotation of the figure (rotation index).
 *   - `figure`: The type of the current figure (figure type index).
 *   - `next_figure`: The type of the next figure (figure type index).
 *
 * This structure is used to store and update the position and
 * state of the figure during gameplay. The `x` and `y` fields define
 * the position of the figure on the game field, while `rotation` and `figure`
 * determine its appearance. The `next_figure` field stores information about
 * the next figure to be displayed in the information window.
 */
typedef struct {
  int x;
  int y;
  int rotation;
  int figure;
  int next_figure;
} Figure_position;

/**
 * @brief Checks the game field for completed lines, removes them, shifts upper
 * lines down, and updates the score.
 *
 * The `check_field` function performs the following actions:
 *   - Sets the game state to `next_figure` to indicate that the next figure
 * needs to be generated.
 *   - Iterates through each row of the game field and checks if it is
 * completely filled.
 *   - If a row is filled, it calls the `clear_and_shift` function to remove it
 * and shift the upper rows down.
 *   - Updates the player's score depending on the number of lines removed at
 * once.
 *   - Increases the game level when a certain number of points is reached.
 *   - Updates the high score if the current score exceeds it.
 *   - Checks if the figure has reached the upper boundary of the field, which
 * means the end of the game.
 *
 * @param game  A pointer to the `GameInfo_t` structure containing game
 * information.
 *              - `game->field`: A two-dimensional array representing the game
 * field.
 *              - `game->pause`: The current game state.
 *              - `game->score`: The player's current score.
 *              - `game->level`: The current game level.
 *              - `game->high_score`: The player's high score.
 *              - `game->next`: A two-dimensional array representing the initial
 * coordinates of the next figure
 *              - `game->speed`: The current speed of falling figures
 */
void check_field(GameInfo_t *game);

/**
 * @brief Removes the specified line in the game field and shifts all upper
 * lines down.
 *
 * The `clear_and_shift` function clears the specified line (`line`) in the game
 * field, shifting all lines above it down by one position. The top line is
 * filled with `EMPTY_PLACE` values.
 *
 * @param game  A pointer to the `GameInfo_t` structure containing game
 * information.
 *              - `game->field`: A two-dimensional array representing the game
 * field.
 * @param line  The index of the line to clear and shift.
 *              Line numbering starts from 0 (the top line).
 */
void clear_and_shift(GameInfo_t *game, int line);

/**
 * @brief Returns the coordinate of a specified part of a figure, given its type
 * and rotation.
 *
 * The `figures_mass` function provides access to the coordinates of individual
 * parts of various Tetris figures. The coordinates are stored in an internal
 * array called `figures`. The function takes the figure type, rotation, part
 * number, and coordinate index (x or y) as input parameters and returns the
 * corresponding coordinate value.
 *
 * @param type_figure  The type of figure (index in the `figures` array).
 * @param rotation     The rotation of the figure (index in the array of
 * rotations for this figure). Must be in the range of 0 to 4.
 * @param part         The number of the figure's part (index in the array of
 * parts for this rotation). Must be in the range of 0 to 4.
 * @param coord        The index of the coordinate (0 for x, 1 for y).
 */
int figures_mass(int type_figure, int rotation, int part, int coord);

/**
 * @brief Shifts the current figure down one position if possible.
 *
 * The `shift_figure` function attempts to shift the current figure (`figure`)
 * down one position in the game field (`field`). If the shift is possible
 * (there are no obstacles below), the function performs the following actions:
 *   - Clears the figure's current position on the field (fills with
 * `EMPTY_PLACE` values).
 *   - Updates the figure's `x` coordinate (shifts it down).
 *   - Displays the figure in the new position (fills with `MOVING_PLACE`
 * values).
 *
 * If the shift is not possible (the figure has reached the bottom or collided
 * with another figure), the function calls `fix_figure` to fix the figure on
 * the field and sets `flag` to `false`.
 *
 * @param figure  A pointer to the `Figure_position` structure containing
 * information about the figure's position and rotation.
 *                - `figure->x`: The X coordinate of the figure.
 *                - `figure->y`: The Y coordinate of the figure.
 *                - `figure->figure`: The type of figure.
 *                - `figure->rotation`: The rotation of the figure.
 * @param game    A pointer to the `GameInfo_t` structure containing game
 * information.
 *                - `game->field`: A two-dimensional array representing the game
 * field.
 */
bool shift_figure(Figure_position *figure, GameInfo_t *game);

/**
 * @brief Fixes the current figure on the game field.
 *
 * The `fix_figure` function sets the values of the elements in the game field
 * (`game->field`) according to the type of the current figure
 * (`figure->figure`). This means that the figure is no longer "moving" and
 * becomes part of the static landscape of the game field.
 *
 * @param figure  A pointer to the `Figure_position` structure containing
 * information about the figure's position and rotation.
 *                - `figure->x`: The X coordinate of the top-left corner of the
 * figure.
 *                - `figure->y`: The Y coordinate of the top-left corner of the
 * figure.
 *                - `figure->figure`: The type of figure.
 *                - `figure->rotation`: The rotation of the figure.
 * @param game    A pointer to the `GameInfo_t` structure containing game
 * information.
 *                - `game->field`: A two-dimensional array representing the game
 * field.
 */
void fix_figure(Figure_position *figure, GameInfo_t *game);  //

/**
 * @brief Forces the current figure to fall down until it reaches the bottom.
 *
 * The `fall_figure` function repeatedly calls the `shift_figure` function to
 * move the figure down until it reaches the bottom of the game field or
 * collides with another figure. The function also contains an iteration counter
 * to limit the number of shift attempts in case of unforeseen situations.
 *
 * @param figure  A pointer to the `Figure_position` structure containing
 * information about the figure's position and rotation.
 * @param game    A pointer to the `GameInfo_t` structure containing game
 * information.
 */
void fall_figure(Figure_position *figure, GameInfo_t *game);

/**
 * @brief Checks if it is possible to move or rotate the figure in the specified
 * direction.
 *
 * The `can_move` function determines whether the figure (`figure`) can be moved
 * or rotated in the specified direction (`type_move`) without colliding with
 * the boundaries of the game field (`game`) or other figures.
 *
 * @param figure    A pointer to the `Figure_position` structure containing
 * information about the figure's position and rotation.
 *                  - `figure->x`: The X coordinate of the top-left corner of
 * the figure.
 *                  - `figure->y`: The Y coordinate of the top-left corner of
 * the figure.
 *                  - `figure->figure`: The type of figure.
 *                  - `figure->rotation`: The rotation of the figure.
 * @param game      A pointer to the `GameInfo_t` structure containing game
 * information.
 *                  - `game->field`: A two-dimensional array representing the
 * game field.
 * @param type_move The type of movement:
 *                  - `MOVE_LEFT`: Check if it's possible to move left.
 *                  - `MOVE_RIGHT`: Check if it's possible to move right.
 *                  - `MOVE_DOWN`: Check if it's possible to move down.
 *                  - `ROTATING`: Check if it's possible to rotate.
 *
 * @return `true` if the movement or rotation is possible. `false` if the
 * movement or rotation is not possible due to collision with the field
 * boundaries or other figures.
 */
bool can_move(Figure_position *figure, GameInfo_t *game, int type_move);

/**
 * @brief Rotates the current figure on the game field.
 *
 * The `rotate` function attempts to rotate the current figure (`figure`) on the
 * game field (`game`). The function first checks if it is possible to perform
 * the rotation without colliding with the field boundaries or other figures,
 * using the `can_move` function and, if necessary, `can_shift_and_rotate`. If
 * the rotation is possible, the function performs the following actions:
 *   - Saves the current coordinates of the figure.
 *   - Calculates the new rotation of the figure.
 *   - Clears the figure's current position on the field.
 *   - Displays the figure in the new position, taking into account the new
 * rotation.
 *
 * @param figure  A pointer to the `Figure_position` structure containing
 * information about the figure's position and rotation.
 *                - `figure->x`: The X coordinate of the top-left corner of the
 * figure.
 *                - `figure->y`: The Y coordinate of the top-left corner of the
 * figure.
 *                - `figure->figure`: The type of figure.
 *                - `figure->rotation`: The rotation of the figure.
 * @param game    A pointer to the `GameInfo_t` structure containing game
 * information.
 *                - `game->field`: A two-dimensional array representing the game
 * field.
 */
void rotate(Figure_position *figure, GameInfo_t *game);

/**
 * @brief Moves the current figure left or right, if possible.
 *
 * The `move_figure` function attempts to move the current figure (`figure`)
 * left or right in the game field (`game`) depending on the value of the
 * `type_move` parameter. If the movement is possible (there are no collisions
 * with the field boundaries or other figures), the function performs the
 * following actions:
 *   - Determines the change in the Y coordinate depending on the type of
 * movement.
 *   - Clears the figure's current position on the field.
 *   - Updates the figure's Y coordinate.
 *   - Displays the figure in the new position.
 *
 * @param figure    A pointer to the `Figure_position` structure containing
 * information about the figure's position and rotation.
 *                  - `figure->x`: The X coordinate of the top-left corner of
 * the figure.
 *                  - `figure->y`: The Y coordinate of the top-left corner of
 * the figure.
 *                  - `figure->figure`: The type of figure.
 *                  - `figure->rotation`: The rotation of the figure.
 * @param game      A pointer to the `GameInfo_t` structure containing game
 * information.
 *                  - `game->field`: A two-dimensional array representing the
 * game field.
 * @param type_move The type of movement:
 *                  - `MOVE_LEFT`: Move left.
 *                  - `MOVE_RIGHT`: Move right.
 */
void move_figure(Figure_position *figure, GameInfo_t *game, int type_move);

/**
 * @brief Checks if it is possible to rotate the figure with a horizontal shift.
 *
 * The `can_shift_and_rotate` function determines whether it is possible to
 * rotate the figure
 * (`figure`) after first shifting it by one position to the right or left.
 * This is necessary for cases where the figure is close to the edge of the
 * field and rotation in the current position is not possible.
 *
 * The function checks the following options:
 *   1. Shift to the right by one position, then attempt rotation.
 *   2. Shift to the left by two positions (relative to the original position),
 * then attempt rotation.
 *   3. (Only for figure type 0) Shift to the right by two positions, then
 * attempt rotation.
 *   4. (Only for figure type 0) Shift to the left by four positions (relative
 * to the original position), then attempt rotation.
 *
 * @param figure  A pointer to the `Figure_position` structure containing
 * information about the figure's position and rotation.
 *                - `figure->y`: The Y coordinate of the top-left corner of the
 * figure.
 *                - `figure->figure`: The type of figure.
 * @param game    A pointer to the `GameInfo_t` structure containing game
 * information.
 *
 * @return `true` if rotation with a shift is possible. `false` if rotation is
 * not possible in any of the checked options.
 */
bool can_shift_and_rotate(Figure_position *figure, GameInfo_t *game);

/**
 * @brief Stores the coordinates of the parts of the next figure in the
 * `game->next` array.
 *
 * The `random_figure` function retrieves the coordinates of the parts of a
 * figure of the specified type
 * (`digit`) in its initial (zero) rotation and stores them in the `game->next`
 * array. This allows the next figure to be displayed in the game interface.
 *
 * @param digit The type of figure whose coordinates need to be stored.
 *              Must be in the range of 0 to `COUNT_OF_FIGURES - 1`.
 * @param game  A pointer to the `GameInfo_t` structure containing game
 * information.
 *              - `game->next`: A two-dimensional array intended for storing the
 * coordinates of the parts of the next figure.
 */
void random_figure(int digit, GameInfo_t *game);

/**
 * @brief Returns a pointer to a static variable storing information about the
 * figure.
 *
 * The `set_figure_info` function provides access to the static variable
 * `figure`, which stores information about the current figure (of type
 * `Figure_position`). Using a static variable ensures that the information
 * about the figure is preserved between function calls.
 *
 * @return A pointer to the static variable `figure` of type `Figure_position`.
 *
 * The function uses a static variable, so it retains its
 * value between calls.
 * Because the function returns a pointer to a static variable,
 * changes made through this pointer will affect the information about the
 * figure globally.
 */
Figure_position *set_figure_info(void);

/**
 * @brief Initializes the `GameInfo_t` and `Figure_position` structures to start
 * a new game.
 *
 * The `init_game` function performs the following actions:
 *   - Allocates memory for the game field (`game->field`) and initializes it
 * with default values (0).
 *   - Reads the high score from the "high_score.txt" file. If the file does not
 * exist, it creates it and sets the high score to 0.
 *   - Initializes the position and rotation of the first figure (`figure`).
 *   - Generates a random type for the next figure (`figure->next_figure`).
 *   - Sets the initial game level (`game->level`) to 1.
 *   - Allocates memory for the `game->next` array, which will be used to store
 * information about the next figure.
 *   - Fills the `game->next` array with the coordinates of the parts of the
 * next figure, obtained using the `random_figure` function.
 *   - Sets the initial game speed (`game->speed`).
 *   - Sets the game state to `ready_to_start`.
 *   - Initializes the initial value for the delay (`delay`) and the last update
 * time (`last_update`).
 *
 * @param game    A pointer to the `GameInfo_t` structure to be initialized.
 *                - `game->field`: A two-dimensional array representing the game
 * field.
 *                - `game->score`: The player's current score.
 *                - `game->high_score`: The player's high score.
 *                - `game->level`: The current game level.
 *                - `game->next`: An array intended for storing the coordinates
 * of the parts of the next figure.
 *                - `game->pause`: The current game state.
 *                - `game->speed`: The current game speed.
 * @param figure  A pointer to the `Figure_position` structure to be
 * initialized.
 *                - `figure->x`: The X coordinate of the top-left corner of the
 * figure.
 *                - `figure->y`: The Y coordinate of the top-left corner of the
 * figure.
 *                - `figure->rotation`: The rotation of the figure.
 *                - `figure->figure`: The type of figure.
 *                - `figure->next_figure`: The type of the next figure.
 */
void init_game(GameInfo_t *game, Figure_position *figure);

/**
 * @brief Returns a pointer to a static variable storing the delay value.
 *
 * The `delay` function provides access to the static variable `delay`,
 * which stores the delay value (of type `double`). Using a static
 * variable ensures that the delay value is preserved between function
 * calls. Returns the delay between figure shifts down by the timer.
 *
 * @return A pointer to the static variable `delay` of type `double`.
 */
double *delay(void);

/**
 * @brief Returns a pointer to a static variable storing the time of the last
 * update.
 *
 * The `last_update` function provides access to the static variable
 * `time_update`, which stores the time of the last update (of type `clock_t`).
 * Using a static variable ensures that the time of the last
 * update is preserved between function calls.
 *
 * @return A pointer to the static variable `time_update` of type `clock_t`.
 */
clock_t *last_update(void);

/**
 * @brief Frees the memory allocated for the game field and other game
 * resources.
 *
 * The `free_game` function performs the following actions:
 *   - Checks if the current score (`game->score`) exceeds the high score
 * (`game->high_score`). If so, it writes the current score to the
 * "high_score.txt" file.
 *   - Frees the memory allocated for each row of the game field
 * (`game->field`).
 *   - Frees the memory allocated for the game field array (`game->field`).
 *   - Assigns `NULL` to the `game->field` pointer to prevent accidental use of
 * the freed memory.
 *   - Frees the memory allocated for each row of the `game->next` array.
 *   - Frees the memory allocated for the `game->next` array.
 *   - Assigns `NULL` to the `game->next` pointer to prevent accidental use of
 * the freed memory.
 *
 * @param game  A pointer to the `GameInfo_t` structure for which memory needs
 * to be freed.
 *                - `game->field`: A two-dimensional array representing the game
 * field.
 *                - `game->score`: The player's current score.
 *                - `game->high_score`: The player's high score.
 *                - `game->next`: An array intended for storing the coordinates
 * of the parts of the next figure.
 */
void free_game(GameInfo_t *game);

/**
 * @brief Checks if enough time has passed since the last update.
 *
 * The `time_passed` function determines whether the specified delay time
 * (`*time_delay`) has elapsed since the last update (`*time_update`). If the
 * time has passed, the function updates the last update time and returns
 * `true`. The function also recalculates the value of `*time_delay` based on
 * the game level `level`.
 *
 * @param level The current game level. Used to calculate the delay time.
 *
 * @return `true` if the delay time has elapsed. `false` if the delay time has
 * not yet elapsed. The function modifies the values of the static variables
 * `delay` and `last_update`.
 */
bool time_passed(int level);

/**
 * @brief Performs active actions in the game based on the current game state.
 *
 * The `game_active` function manages the game logic in the active state. It
 * performs the following actions:
 *   - Checks if the game is in a state where active actions are required
 *     (not paused, not ready to start, not finished,
 *     not game over).
 *   - If the game is in an active state, it checks if enough time has passed
 * since the last update, using the `time_passed` function.
 *   - If time has passed, it sets the game state to `shift` (need to
 *     shift the figure down).
 *   - Depending on the current game state (`game->pause`), it performs the
 *     corresponding action:
 *     - `move_left`: Moves the figure to the left.
 *     - `move_right`: Moves the figure to the right.
 *     - `fall`: Forces the figure to fall down.
 *     - `rotation`: Rotates the figure.
 *     - `shift`: Shifts the figure down by one position.
 *   - After performing the action, it sets the game state to `no_signal`.
 */
void game_active(GameInfo_t *game, Figure_position *figure);

/**
 * @brief Returns a pointer to a static variable storing game information.
 *
 * The `set_game_info` function provides access to the static variable `game`,
 * which stores game information (of type `GameInfo_t`). Using a
 * static variable ensures that the game information is preserved between
 * function calls.
 *
 * @return A pointer to the static variable `game` of type `GameInfo_t`.
 */
GameInfo_t *set_game_info(void);

#endif