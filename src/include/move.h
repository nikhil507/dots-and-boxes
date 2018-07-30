#ifndef MOVE_T_
#define MOVE_T_

typedef struct move_t
{
    int x, y, val;
}Move;

void moveInit(Move *mv, int x, int y, int val);

#endif
