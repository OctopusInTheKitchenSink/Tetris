#include "common.h"

#include "backend.h"

// преобразование ввода пользователя в новое состояние игры
void userInput(UserAction_t action, bool hold) {
  GameInfo_t *game = set_game_info();
  static int init = 1;
  Figure_position *figure = set_figure_info();
  if (init == 1) {
    init = 0;
    init_game(game, figure);
  }
  if (game->pause == game_over) init = 1;  ///////
  (void)hold;
  if (game->pause != terminate && game->pause != game_over &&
      game->pause != pause) {
    switch (action) {
      case Start:
        if (game->pause == ready_to_start) game->pause = shift;
        break;
      case Pause:
        game->pause = pause;
        break;
      case Terminate:
        game->pause = terminate;
        break;
      case Left:
        game->pause = move_left;
        break;
      case Right:
        game->pause = move_right;
        break;
      case Down:
        game->pause = fall;
        break;
      case Action:
        game->pause = rotation;
        break;
      default:
        if (game->pause != ready_to_start) game->pause = no_signal;
        break;
    }
  }
  if (action == Start && game->pause == pause) {
    game->pause = no_signal;
  }
  if (action == Terminate && game->pause == pause) {
    game->pause = terminate;
  }
}

// все манипуляции с полем: сдвиги и проверка на обновление счета, рекорда,
// скорости, уровня, состояния игры. Проверка на возможность убрать строки
// происходит только в том случае, если предыдущая фигура достигла нижней
// возможной позиции
GameInfo_t updateCurrentState() {
  GameInfo_t *game = set_game_info();
  Figure_position *figure = set_figure_info();
  game_active(game, figure);
  if (game->pause == no_signal && !can_move(figure, game, MOVE_DOWN)) {
    fix_figure(figure, game);
    check_field(game);
  }
  if (game->pause == next_figure) {
    figure->figure = figure->next_figure;
    figure->next_figure = rand() % COUNT_OF_FIGURES;
    random_figure(figure->next_figure, game);
    game->next[2][2] = figure->figure + 1,
    game->next[3][2] = figure->next_figure + 1;
    figure->x = 0, figure->y = 0, figure->rotation = 0;
    game->pause = shift;
  }
  if (game->pause == terminate || game->pause == game_over) {
    free_game(game);
  }
  return *game;
}
