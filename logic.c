#include "game.h"
#include <stdbool.h>
#include <stddef.h>

/// Logic of the game.

static void switch_player(struct Game *game) {
    if (game->player == CELL_PLAYER_X) game->player = CELL_PLAYER_O;
    else if (game->player == CELL_PLAYER_O) game->player = CELL_PLAYER_X;
}

size_t count_cells(const int *board, enum Cell_State any_cell) {
    size_t counter = 0;
    for (size_t i = 0, n = N_GRID * N_GRID; i < n; i++) {
        if (board[i] == any_cell) { counter += 1; }
    }
    return counter;
}

bool check_player_won(struct Game *game, enum Cell_State player) {
    size_t row_count = 0, col_count = 0;
    size_t diag1_count = 0, diag2_count = 0;

    for (size_t x = 0; x < N_GRID; x++) {      // Traverse column.
        for (size_t y = 0; y < N_GRID; y++) {  // Traverse row.
            if (game->board[(x * N_GRID) + y] == player) { row_count += 1; }
            if (game->board[(y * N_GRID) + x] == player) { col_count += 1; }
        }

        // Check non-diagonals.
        if (row_count >= N_GRID || col_count >= N_GRID) return true;
        row_count = 0, col_count = 0;

        // Check diagonals.
        if (game->board[(x * N_GRID) + x] == player) diag1_count += 1;
        if (game->board[(x * N_GRID) + N_GRID - x - 1] == player)
            diag2_count += 1;
    }

    return (diag1_count == N_GRID) || (diag2_count == N_GRID);
}

void game_over_condition(struct Game *game) {
    if (check_player_won(game, CELL_PLAYER_X)) {
        game->state = GAME_STATE_PLAYER_X_WON;
    } else if (check_player_won(game, CELL_PLAYER_O)) {
        game->state = GAME_STATE_PLAYER_O_WON;
    } else if (count_cells(game->board, CELL_EMPTY) == 0) {
        game->state = GAME_STATE_TIE;
    }
}

static void player_turn(struct Game *game, int row, int col) {
    if (game->board[row * N_GRID + col] == CELL_EMPTY) {
        game->board[row * N_GRID + col] = game->player;
        switch_player(game);
        game_over_condition(game);
    }
}

static void reset_game(struct Game *game) {
    game->player = CELL_PLAYER_X;
    game->state  = GAME_STATE_RUNNING;

    for (size_t i = 0, n = N_GRID * N_GRID; i < n; i += 1)
        game->board[i] = CELL_EMPTY;
}

// Handle a single game turn.
void click_on_cell(struct Game *game, int row, int col) {
    if (game->state == GAME_STATE_RUNNING) {
        player_turn(game, row, col);
    } else {  // GAME_STATE_TIE.
        reset_game(game);
    }
}
