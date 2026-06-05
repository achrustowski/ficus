#ifndef DEFS_H_
#define DEFS_H_

#define W_WIDTH    900
#define W_HEIGHT   800

#define FPS 58

#define GRAVITY 900.0f

#define PLAYER_SPEED_X 100.0f
#define PLAYER_SPEED_Y 100.0f
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 48

#define TILE_SIZE 32
#define TILE_SET_GROUND_WIDTH 384
#define TILE_SET_GROUND_HEIGHT 384
#define TILE_SCALE 1.5f

#define DEBUG_WIDTH 300
#define DEBUG_HEIGHT 280

#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : (v) > (hi) ? (hi) : (v))

#endif
