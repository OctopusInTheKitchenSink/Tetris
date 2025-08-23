#include "backend.h"

// проверка поля: генерирование новой фигуры, уничтожение заполненных линий
// (+сдвиг), подсчет уничтоженных линий, обновление счета и рекорда, повышение
// скорости, проверка на окончание игры (проверка верхней строки)
void check_field(GameInfo_t *game) {
  game->pause = next_figure;
  int counter_of_completed_place = 0, flag_for_counter = 1,
      counter_for_score = 0;
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    counter_of_completed_place = 0, flag_for_counter = 1;
    for (int j = 0; j < FIELD_WIDTH && flag_for_counter; ++j) {
      if (game->field[i][j] != EMPTY_PLACE) {
        counter_of_completed_place++;
      } else {
        flag_for_counter = 0;
      }
    }
    if (counter_of_completed_place == REAL_FIELD_WIDTH) {
      clear_and_shift(game, i);
      counter_for_score++;
    }
  }
  switch (counter_for_score) {
    case 1:
      game->score += ONE_LINE;
      break;
    case 2:
      game->score += TWO_LINES;
      break;
    case 3:
      game->score += THREE_LINES;
      break;
    case 4:
      game->score += FOUR_LINES;
      break;
  }
  if (game->score / SPEED_UP <= MAX_SPEED) {
    game->level = game->score / SPEED_UP + 1;
  }
  if (game->score > game->high_score) {
    game->high_score = game->score;
  }
  // check the highest line
  for (int i = 0; i < FIELD_WIDTH; ++i) {
    if (game->field[0][i] != 0) {
      game->pause = game_over;
    }
  }
}

// уничтожение полностью заполненного ряда со сдвигом всех тетромино, лежащих
// выше, на позицию вниз
void clear_and_shift(GameInfo_t *game, int line) {
  for (int i = line; i > 0; --i) {
    for (int j = 0; j < FIELD_WIDTH; ++j) {
      game->field[i][j] = game->field[i - 1][j];
    }
  }
  for (int i = 0; i < FIELD_WIDTH; ++i) {  // fill the highest line by zeros
    game->field[0][i] = EMPTY_PLACE;
  }
}

// массив с базовыми положениями фигур
int figures_mass(int type_figure, int rotation, int part, int coord) {
  int figures[COUNT_OF_FIGURES][COUNT_OF_ROTATIONS][FIGURE_PART][2] = {
      {{{0, 3}, {0, 4}, {0, 5}, {0, 6}},
       {{-1, 5}, {0, 5}, {1, 5}, {2, 5}},
       {{1, 3}, {1, 4}, {1, 5}, {1, 6}},
       {{-1, 4}, {0, 4}, {1, 4}, {2, 4}}},  // I
      {{{0, 4}, {1, 4}, {2, 4}, {2, 5}},
       {{2, 3}, {1, 3}, {1, 4}, {1, 5}},
       {{0, 3}, {0, 4}, {1, 4}, {2, 4}},
       {{1, 3}, {1, 4}, {1, 5}, {0, 5}}},  // L
      {{{0, 4}, {1, 4}, {2, 4}, {2, 3}},
       {{0, 3}, {1, 3}, {1, 4}, {1, 5}},
       {{0, 5}, {0, 4}, {1, 4}, {2, 4}},
       {{1, 3}, {1, 4}, {1, 5}, {2, 5}}},  // J
      {{{0, 4}, {1, 4}, {0, 5}, {1, 5}},
       {{0, 4}, {1, 4}, {0, 5}, {1, 5}},
       {{0, 4}, {1, 4}, {0, 5}, {1, 5}},
       {{0, 4}, {1, 4}, {0, 5}, {1, 5}}},  // O
      {{{1, 3}, {1, 4}, {0, 4}, {0, 5}},
       {{0, 4}, {1, 4}, {1, 5}, {2, 5}},
       {{2, 3}, {2, 4}, {1, 4}, {1, 5}},
       {{0, 3}, {1, 3}, {1, 4}, {2, 4}}},  // S
      {{{0, 3}, {0, 4}, {1, 4}, {1, 5}},
       {{0, 5}, {1, 5}, {1, 4}, {2, 4}},
       {{1, 3}, {1, 4}, {2, 4}, {2, 5}},
       {{0, 4}, {1, 4}, {1, 3}, {2, 3}}},  // Z
      {{{0, 4}, {1, 4}, {1, 3}, {1, 5}},
       {{0, 4}, {1, 4}, {2, 4}, {1, 5}},
       {{1, 3}, {1, 4}, {1, 5}, {2, 4}},
       {{0, 4}, {1, 4}, {2, 4}, {1, 3}}}  // T
  };
  return figures[type_figure][rotation][part][coord];
}

// сдвиг фигуры вниз с проверкой на возможность совершения этого дейстия
bool shift_figure(Figure_position *figure, GameInfo_t *game) {
  bool flag = true;
  int curr_figure = figure->figure;
  if (can_move(figure, game, MOVE_DOWN)) {
    for (int i = 0; i < FIGURE_PART; ++i) {
      game->field[figure->x + figures_mass(curr_figure, figure->rotation, i, 0)]
                 [figure->y + figures_mass(curr_figure, figure->rotation, i,
                                           1)] = EMPTY_PLACE;
    }
    figure->x += 1;
    for (int i = 0; i < FIGURE_PART; ++i) {
      game->field[figure->x + figures_mass(curr_figure, figure->rotation, i, 0)]
                 [figure->y + figures_mass(curr_figure, figure->rotation, i,
                                           1)] = MOVING_PLACE + curr_figure + 1;
    }
  } else {
    fix_figure(figure, game);
    flag = false;
  }
  return flag;
}

// "фиксируем" фигуру на поле
void fix_figure(Figure_position *figure, GameInfo_t *game) {
  for (int i = 0; i < FIGURE_PART; ++i) {
    game->field[figure->x +
                figures_mass(figure->figure, figure->rotation, i, 0)]
               [figure->y + figures_mass(figure->figure, figure->rotation, i,
                                         1)] = figure->figure + 1;
  }
}

// максимальный сдвиг фигуры вниз (сброс)
void fall_figure(Figure_position *figure, GameInfo_t *game) {
  // если что-то пойдет не так, счетчик ограничит количество итераций
  int counter = 0;
  while (shift_figure(figure, game) && counter < 20) {
    counter++;
  }
}

// проверка на возможность сдвига влево/вправо/вниз/поворота
bool can_move(Figure_position *figure, GameInfo_t *game, int type_move) {
  bool flag = true;
  int change_x = 0, change_y = 0, rotation = figure->rotation;
  if (type_move == MOVE_LEFT) {
    change_y = -1;
  }
  if (type_move == MOVE_RIGHT) {
    change_y = 1;
  }
  if (type_move == MOVE_DOWN) {
    change_x = 1;
  }
  if (type_move == ROTATING) {
    rotation = (figure->rotation + 1) % COUNT_OF_ROTATIONS;
  }
  int curr_figure = figure->figure;
  for (int i = 0; i < FIGURE_PART && flag; ++i) {
    int new_x = figure->x + change_x;
    int new_y = figure->y + change_y;
    new_x += figures_mass(curr_figure, rotation, i, 0);
    new_y += figures_mass(curr_figure, rotation, i, 1);
    if (new_x >= FIELD_HEIGHT - 1 || new_x <= ZERO_X ||
        new_y >= FIELD_WIDTH - 1 || new_y < ZERO_Y ||
        (game->field[new_x][new_y] > EMPTY_PLACE &&
         game->field[new_x][new_y] <= COUNT_OF_FIGURES)) {
      flag = false;
    }
  }
  return flag;
}

// поворот с проверкой возможности действия на месте и со сдвигом
void rotate(Figure_position *figure, GameInfo_t *game) {
  int old_y = figure->y, old_x = figure->x;
  if (can_move(figure, game, ROTATING) || can_shift_and_rotate(figure, game)) {
    int curr_figure = figure->figure;
    int rotation = figure->rotation;
    figure->rotation = (figure->rotation + 1) % COUNT_OF_ROTATIONS;
    for (int i = 0; i < FIGURE_PART; ++i) {
      int x = old_x + figures_mass(curr_figure, rotation, i, 0);
      int y = old_y + figures_mass(curr_figure, rotation, i, 1);
      game->field[x][y] = EMPTY_PLACE;
    }
    for (int i = 0; i < FIGURE_PART; ++i) {
      int new_x = figure->x + figures_mass(curr_figure, figure->rotation, i, 0);
      int new_y = figure->y + figures_mass(curr_figure, figure->rotation, i, 1);
      game->field[new_x][new_y] = MOVING_PLACE + curr_figure + 1;
    }
  }
}

// сдвиг вправо/влево, учитывая возможность этого действия
void move_figure(Figure_position *figure, GameInfo_t *game, int type_move) {
  int change_y = 0;
  if (type_move == MOVE_RIGHT) {
    change_y = 1;
  }
  if (type_move == MOVE_LEFT) {
    change_y = -1;
  }
  if (can_move(figure, game, type_move)) {
    int curr_figure = figure->figure;
    for (int i = 0; i < FIGURE_PART; ++i) {
      game->field[figure->x + figures_mass(curr_figure, figure->rotation, i, 0)]
                 [figure->y + figures_mass(curr_figure, figure->rotation, i,
                                           1)] = EMPTY_PLACE;
    }
    figure->y += change_y;
    for (int i = 0; i < FIGURE_PART; ++i) {
      game->field[figure->x + figures_mass(curr_figure, figure->rotation, i, 0)]
                 [figure->y + figures_mass(curr_figure, figure->rotation, i,
                                           1)] = MOVING_PLACE + curr_figure + 1;
    }
  }
}

// проверка на возможность поворота со сдвигом
bool can_shift_and_rotate(Figure_position *figure, GameInfo_t *game) {
  bool flag = false;
  figure->y += 1;
  if (can_move(figure, game, ROTATING)) {
    flag = true;
  } else {
    figure->y -= 2;
    if (can_move(figure, game, ROTATING)) {
      flag = true;
    } else {
      figure->y += 1;
    }
  }
  if (figure->figure == 0 && flag == false) {
    figure->y += 2;
    if (can_move(figure, game, ROTATING)) {
      flag = true;
    } else {
      figure->y -= 4;
      if (can_move(figure, game, ROTATING)) {
        flag = true;
      } else {
        figure->y += 2;
      }
    }
  }
  return flag;
}

// извлекаем из массива со всеми фигурами рандомную
void random_figure(int digit, GameInfo_t *game) {
  for (int i = 0; i < FIGURE_PART; ++i) {
    game->next[i][0] = figures_mass(digit, 0, i, 0);
    game->next[i][1] = figures_mass(digit, 0, i, 1);
  }
}

// для хранения состояния фигуры
Figure_position *set_figure_info(void) {
  static Figure_position figure;
  return &figure;
}

double *delay(void) {
  static double delay;
  return &delay;
}

clock_t *last_update(void) {
  static clock_t time_update;
  return &time_update;
}

// инициализируем структуру, в которой хранится состояние игры базовыми
// значениями
void init_game(GameInfo_t *game, Figure_position *figure) {
  game->field = (int **)calloc(FIELD_HEIGHT, sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    game->field[i] = (int *)calloc(FIELD_WIDTH, sizeof(int));
  }
  game->score = 0;
  FILE *file = fopen("high_score.txt", "r");
  if (file) {
    char score[20] = {0}, symbol;
    int symbol_counter = 0;
    while ((symbol = fgetc(file)) != EOF) {
      score[symbol_counter++] = symbol;
    }
    score[symbol_counter] = '\0';
    game->high_score = atoi(score);
    fclose(file);
  } else {
    FILE *new_file = fopen("high_score.txt", "w");
    if (new_file) {
      fclose(new_file);
    }
    game->high_score = 0;
  }
  figure->x = 0, figure->y = 0, figure->rotation = 0,
  figure->figure = rand() % COUNT_OF_FIGURES,
  figure->next_figure = rand() % COUNT_OF_FIGURES;
  game->level = 1;
  game->next = (int **)calloc(FIGURE_PART, sizeof(int *));
  for (int i = 0; i < FIGURE_PART; ++i) {
    game->next[i] = (int *)calloc(3, sizeof(int));  // 2
  }
  random_figure(figure->next_figure, game);
  game->next[2][2] = figure->figure + 1,
  game->next[3][2] = figure->next_figure + 1;
  game->pause = 0;
  game->speed = START_SPEED / game->level;
  game->pause = ready_to_start;
  double *start_delay = delay();
  *start_delay = (double)START_TIMEOUT / game->level * 0.5;
  clock_t *time_update = last_update();
  *time_update = clock();
}

// очищаем игру
void free_game(GameInfo_t *game) {
  if (game->score >= game->high_score) {
    FILE *file = fopen("high_score.txt", "w");
    if (file) {
      fprintf(file, "%d", game->high_score);
      fclose(file);
    }
  }
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    free(game->field[i]);
  }
  free(game->field);
  game->field = NULL;
  for (int i = 0; i < FIGURE_PART; ++i) {
    free(game->next[i]);
  }
  free(game->next);
  game->next = NULL;
}

bool time_passed(int level) {
  bool flag = false;
  double *time_delay = delay();
  clock_t *time_update = last_update();
  clock_t now = clock();  // запоминаем нынешнее время
  double elapsed_time_ms =
      (double)(now - *time_update) / CLOCKS_PER_SEC * START_TIMEOUT;
  if (elapsed_time_ms >= *time_delay) {
    *time_update = now;
    flag = true;
  }
  *time_delay = (double)START_TIMEOUT / level;
  return flag;
}

// для хранения состояния игры
GameInfo_t *set_game_info(void) {
  static GameInfo_t game;
  return &game;
}

void game_active(GameInfo_t *game, Figure_position *figure) {
  bool check_flag = (game->pause != pause && game->pause != ready_to_start &&
                     game->pause != terminate && game->pause != game_over);
  if (check_flag && time_passed(game->level)) {
    game->pause = shift;
  }
  switch (game->pause) {
    case move_left:
      move_figure(figure, game, MOVE_LEFT);
      game->pause = no_signal;
      break;
    case move_right:
      move_figure(figure, game, MOVE_RIGHT);
      game->pause = no_signal;
      break;
    case fall:
      fall_figure(figure, game);
      game->pause = no_signal;
      break;
    case rotation:
      rotate(figure, game);
      game->pause = no_signal;
      break;
    case shift:
      shift_figure(figure, game);  // move figure, if its possible
      game->pause = no_signal;
      break;
    default:
      if (check_flag) {
        game->pause = no_signal;
      }
      break;
  }
}
