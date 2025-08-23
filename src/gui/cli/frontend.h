#ifndef H_FILE_FRONT
#define H_FILE_FRONT
#include <locale.h>
#include <math.h>
#include <ncurses.h>

#include "../../brick_game/tetris/common.h"
#include "./../../tetris.h"

/**
 * @brief The main game loop.
 *
 * The `game_loop` function represents the main game loop, which
 * manages game logic, graphics rendering, and user input processing.
 *
 * The function performs the following actions:
 *   - Initializes the ncurses library for working with the terminal.
 *   - Initializes the `action` variable to store the user's action.
 *   - Creates a local variable `game` of type `GameInfo_t` and initializes it
 *     with zeros.
 *   - Creates two ncurses windows: `field` for displaying the game field and
 * `info` for displaying game information (score, level, etc.).
 *   - Starts the main game loop `while (game_flag)`.
 *     - If the game is in the `terminate` or `game_over` state,
 *       it sets `game_flag` to `FALSE` to terminate the game loop.
 *     - Calls the `print_game` function to display the current game state in
 * the `field` and `info` windows.
 *     - Calls the `process_signal` function to process user input and
 *       determine the action (`action`).
 *     - Calls the `userInput` function to handle the user's action and
 *       change the game state.
 *     - If `game_flag` remains `TRUE` (the game is not over), it calls the
 *       `updateCurrentState` function to update the game state.
 *
 * @return `TRUE` if the game ended in the `game_over` state, `FALSE` otherwise.
 */
bool game_loop();

/**
 * @brief Processes user input and determines the corresponding action.
 *
 * The `process_signal` function reads a character entered by the user and,
 * based on that character, determines the corresponding action, which is then
 * passed for further processing.
 *
 * The function performs the following actions:
 *   - Reads a character entered by the user using the `getch` function.
 *   - Depending on the character entered, it sets the value of the `action`
 *     pointer to the corresponding action (defined in the `UserAction_t`
 *     enumeration).
 *
 * @param action  A pointer to a variable of type `UserAction_t` in which the
 *                determined user action will be written.
 *
 * The function uses the `getch` function to read user
 * input.
 */
void process_signal(UserAction_t *action);

/**
 * @brief Displays the game field, game information, and status messages in
 * ncurses windows.
 *
 * The `print_game` function draws various game elements in the specified
 * ncurses windows (`field` and `info`), depending on the current game state.
 *
 * The function performs the following actions:
 *   - Clears the windows and draws borders.
 *   - Depending on the current game state (`game.pause`), draws the
 * corresponding game state or the field with figures, updates or deletes
 * windows, and makes a delay.
 *
 * @param game    The `GameInfo_t` structure containing game information.
 * @param field   A pointer to the ncurses window intended for displaying the
 * game field.
 * @param info    A pointer to the ncurses window intended for displaying game
 * information.
 */
void print_game(GameInfo_t game, WINDOW *field, WINDOW *info);

/**
 * @brief Displays a start game message in the specified ncurses window.
 *
 * The `print_start_status` function displays text prompting the user to press
 * the ENTER key to start the game in the specified ncurses window (`field`).
 *
 * @param field A pointer to the ncurses window in which the message will be
 * displayed.
 */
void print_start_status(WINDOW *field);

/**
 * @brief Displays a pause message in the game in the specified ncurses window.
 *
 * The `print_pause_status` function displays text prompting the user to press
 * the ENTER key to continue the game in the specified ncurses window (`field`).
 *
 * @param field A pointer to the ncurses window in which the message will be
 * displayed.
 */
void print_pause_status(WINDOW *field);

/**
 * @brief Displays a game over message and the final score in the specified
 * ncurses window.
 *
 * The `print_end_status` function displays text informing about the end of the
 * game, the player's final score, and information about whether a new record
 * has been set in the specified window ncurses (`field`).
 *
 * @param field A pointer to the ncurses window in which the message will be
 * displayed.
 * @param game  The `GameInfo_t` structure containing game information,
 * including score and high score.
 */
void print_end_status(WINDOW *field, GameInfo_t game);

/**
 * @brief Displays information about the game control keys in the specified
 * ncurses window.
 *
 * The `print_start_info` function displays text explaining which control keys
 * are used in the game, in the specified ncurses window (`info`). This is
 * usually used to display information on the game's start screen.
 *
 * @param info A pointer to the ncurses window in which the information will be
 * displayed.
 */
void print_start_info(WINDOW *info);

/**
 * @brief Displays the game field in the specified ncurses window.
 *
 * The `print_game_field` function draws the contents of the game field in the
 * specified ncurses window (`field`). The colors of the field cells depend on
 * their values.
 *
 * @param game  The `GameInfo_t` structure containing game information,
 * including the game field.
 * @param field A pointer to the ncurses window in which the game field will be
 * displayed.
 */
void print_game_field(GameInfo_t game, WINDOW *field);

/**
 * @brief Displays game information (next figure, score, high score, level) in
 * the specified ncurses window.
 *
 * The `print_info` function displays information about the current game state
 * in the specified ncurses window (`info`). Displays the next figure, the
 * current score, high score, level, and control keys.
 *
 * @param info A pointer to the ncurses window in which the information will be
 * displayed.
 * @param game The `GameInfo_t` structure containing game information.
 */
void print_info(WINDOW *info, GameInfo_t game);

/**
 * @brief Initializes the ncurses library and configures terminal settings.
 *
 * The `init_ncurses` function performs the following actions:
 *   - Initializes the ncurses library, starting work with the terminal.
 *   - Disables the display of entered characters on the screen.
 *   - Hides the cursor.
 *   - Enables the processing of special keys (arrows, Home, End, Page Up, Page
 * Down, etc.).
 *   - Sets localized settings for correct handling of characters and text.
 *   - Sets non-blocking mode for `stdscr` so that `getch` returns `ERR` if
 * there is no input.
 *   - Initializes the ncurses color system and defines color pairs for use in
 * the game.
 */
void init_ncurses(void);

#endif