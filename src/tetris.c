#include "tetris.h"

#include "gui/cli/frontend.h"

/**
 * @brief The main function of the program, managing the game's lifecycle.
 *
 * The `main` function is the entry point for the "Tetris" program. It performs
 * the following actions:
 *  - Initializes the `ncurses` library for console interface interaction.
 *  - Configures input and output, hides the cursor.
 *  - Initializes the random number generator.
 *  - Enables handling of special keys (arrow keys, etc.).
 *  - Sets up non-blocking input.
 *  - Initializes the color system.
 *  - Starts the main game loop by calling the `game_loop()` function. The loop
 * continues as long as `game_loop()` returns `TRUE`.
 *  - Terminates the `ncurses` library.
 *
 * @return 0 if the program completes successfully.
 */
int main(void) {
  srand(time(NULL));
  bool continue_game = TRUE;
  while (continue_game) {
    continue_game = game_loop();  // запуск игры
  }
  return 0;
}
