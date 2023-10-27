#ifndef GAME_H_
#define GAME_H_

/// Global constants and variables for game.

#define N_GRID        3                        // Number of each rows & columns.
#define SCREEN_WIDTH  640                      // Width of window.
#define SCREEN_HEIGHT 480                      // Height of window.
#define CELL_WIDTH    (SCREEN_WIDTH / N_GRID)  // (float)
#define CELL_HEIGHT   (SCREEN_HEIGHT / N_GRID)  // (float)

enum Cell_State {  // Each sub-grid can be either "empty" or have one player.
    CELL_EMPTY    = 0,
    CELL_PLAYER_X = 1,
    CELL_PLAYER_O = 2,
};

enum Game_State {  // Enumeration of each states of the game.
    GAME_STATE_RUNNING      = 0,
    GAME_STATE_PLAYER_X_WON = 1,
    GAME_STATE_PLAYER_O_WON = 2,
    GAME_STATE_TIE          = 3,
    GAME_STATE_QUIT         = 4,
};

struct Game {
    int board[N_GRID * N_GRID];
    int player;
    int state;
};

#endif  // GAME_H_
