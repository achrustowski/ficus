#ifndef ENUMS_H_
#define ENUMS_H_

typedef enum Side
{
    P_TOP,
    P_RIGHT,
    P_BOTTOM,
    P_LEFT,
    P_NONE
} Side;

typedef enum Collision_Side
{
    NONE,
    TOP,
    RIGHT,
    BOTTOM,
    LEFT,
    CORNER_TOP_RIGHT,
    CORNER_BOTTOM_RIGHT,
    CORNER_BOTTOM_LEFT,
    CORNER_TOP_LEFT,
    TOP_BOTTOM,
    LEFT_RIGHT,
    TOP_RIGHT_BOTTOM,
    RIGHT_BOTTOM_LEFT,
    BOTTOM_LEFT_TOP
} Collision_Side;

#endif
