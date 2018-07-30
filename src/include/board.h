#ifndef BOARD_H_
#define BOARD_H_
#include <globals.h>

typedef struct board_t
{
    char bd[N][N];
    int p1, p2;
}Board;

void init(Board *b);
int playerScore(Board *b, int p);
int makeMove(Board *b, int x, int y, int p, int pos);
int evaluateBoard(Board *b);
void printBoard(Board *b);
void displayBoard(Board *b);
void setBoard(Board *b, const char *path);
void saveBoard(Board *b, const char *path);
int makeOptimalMove(Board *b);
int isEnd(Board *b);
void undoMove(Board *b, int x, int y, int pos);

#endif
