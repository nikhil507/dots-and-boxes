#include <board.h>
#include <globals.h>
#include <util.h>
#include <limits.h>
#include <move.h>
#include <stdio.h>

int A[] = {UP, RIGHT, DOWN, LEFT};
Move optimal;

int miniMax(Board *b, int alpha, int beta, int p, int kapa, int h);

int makeOptimalMove(Board *b)
{
    int sc = playerScore(b, P1);
    miniMax(b, INT_MIN, INT_MAX, P1, 1, 0);
    if(playerScore(b, P1) != sc)
        return 1;
    return 0;
}

int miniMax(Board *b, int alpha, int beta, int p, int kapa, int h)
{
    int i, j, k;
    if(isEnd(b) || h >= 9)
    {
        return evaluateBoard(b);
    }
    if(p == P1)
    {
        int maxy = INT_MIN, napa = 0, zeta;
        for(i = 0; i < N; i++)
        {
            for(j = 0; j < N; j++)
            {
                for(k = 0; k < 4; k++)
                {
                    if(napa = makeMove(b, i, j, p, A[k]))
                    {
                        if(napa == 2)
                            /*maxy = max(miniMax(b, alpha, beta, P1, 0), maxy);*/
                            zeta = miniMax(b, alpha, beta, P1, 0, h + 1);
                        else
                            /*maxy = max(miniMax(b, alpha, beta, P2, 0), maxy);*/
                            zeta = miniMax(b, alpha, beta, P2, 0, h + 1);
                        if(maxy < zeta)
                        {
                            maxy = zeta;
                            if(kapa == 1)
                                moveInit(&optimal, i, j, A[k]);
                        }
                        alpha = max(alpha, maxy);
                        undoMove(b, i, j, A[k]);
                        if(beta <= alpha)
                        {
                            if(kapa == 1)
                                makeMove(b, optimal.x, optimal.y, p, optimal.val);
                            return maxy;
                        }
                    }
                }
            }
        }
        if(kapa == 1)
            makeMove(b, optimal.x, optimal.y, p, optimal.val);
            /*b->bd[optimal->x][optimal->y] = optimal->val;*/
        return maxy;
    }
    else if(p == P2)
    {
        int mini = INT_MAX, napa, zeta;
        for(i = 0; i < N; i++)
        {
            for(j = 0; j < N; j++)
            {
                for(k = 0; k < 4; k++)
                {
                    if(napa = makeMove(b, i, j, p, A[k]))
                    {
                        if(napa == 2)
                            /*mini = min(miniMax(b, alpha, beta, P2, 0), mini);*/
                            zeta = miniMax(b, alpha, beta, P2, 0, h + 1);
                        else
                            /*mini = min(miniMax(b, alpha, beta, P1, 0), mini);*/
                            zeta = miniMax(b, alpha, beta, P1, 0, h + 1);
                        if(zeta < mini)
                        {
                            mini = zeta;
                            if(kapa == 1)
                                moveInit(&optimal, i, j, A[k]);
                        }
                        beta = min(beta, mini);
                        undoMove(b, i, j, A[k]);
                        if(beta <= alpha)
                        {
                            if(kapa == 1)
                                makeMove(b, optimal.x, optimal.y, p, optimal.val);
                            return mini;
                        }
                    }
                }
            }
        }
        if(kapa == 1)
            makeMove(b, optimal.x, optimal.y, p, optimal.val);
        return mini;
    }
}
