#include <board.h>
#include <globals.h>
#include <stdio.h>
#include <string.h>

// constructs the baord object

void init(Board *b)
{
    memset(b->bd, 0, sizeof(char) * N * N);
    b->p1 = b->p2 = 0;
}

// player score at any time
int playerScore(Board *b, int p)
{
    if(p == P1)
        return b->p1;
    else if(p == P2)
        return b->p2;
    else
        return -1;
}


// make a move on the board based on the coordinates  provided
int makeMove(Board *b, int x, int y, int p, int pos)
{
	
    int a = 0;
    //point gained or not
	
	
	//checks the bounds wrt table
	if(x < 0 || y < 0 || x >= N || y >= N)
        return 0;
        
        
    // if that move was already made in the past
    if((b->bd[x][y] & pos) != 0)
        return 0;
        
    //make that move    
    b->bd[x][y] = b->bd[x][y] | pos;
    
    //if a box is completed give points the respective player
    if(b->bd[x][y] == COMPLETE)
    {
        b->bd[x][y] = p, a++;
        
        // 'a' is like a switch that denotes whether any player scored
    }
    
    
    // check if the player made a double point 
    if(pos == UP && y > 0)
    {
        b->bd[x][y - 1] |= DOWN;
        if(b->bd[x][y - 1] == COMPLETE)
            b->bd[x][y - 1] = p, a++;
    }
    else if(pos == DOWN && y < N - 1)
    {
        b->bd[x][y + 1] |= UP;
        if(b->bd[x][y + 1] == COMPLETE)
            b->bd[x][y + 1] = p, a++;
    }
    else if(pos == LEFT && x > 0)
    {
        b->bd[x - 1][y] |= RIGHT;
        if(b->bd[x - 1][y] == COMPLETE)
            b->bd[x - 1][y] = p, a++;
    }
    else if(pos == RIGHT && x < N - 1)
    {
        b->bd[x + 1][y] |= LEFT;
        if(b->bd[x + 1][y] == COMPLETE)
            b->bd[x + 1][y] = p, a++;
    }
    
    
    // give points
    if(p == P1)
        b->p1 += a;
    else if(p == P2)
        b->p2 += a;
    
	// if someone scored
	if(a > 0)
        return 2;
        
    // else   
    return 1;
    
    
}

// Util: 
int evaluateBoard(Board *b)
{
	
    return playerScore(b, P1) - playerScore(b, P2);
}



void printBoard(Board *b)
{
    int i, j;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            printf("%d ", (int)b->bd[j][i]);
        }
        putchar('\n');
    }
    printf("Score: %d %d\n", b->p1, b->p2);
}


//unused: future work
void setBoard(Board *b, const char *path)
{
    int i = 0;
    FILE *fp = fopen(path, "r");
    int num;
    while(fscanf(fp, "%d", &num) && i < N * N)
    {
        b->bd[i % N][i / N] = num;
        if(num == P1)
            b->p1++;
        else if(num == P2)
            b->p2++;
        i++;
    }
    fclose(fp);
}

void saveBoard(Board *b, const char *path)
{
    FILE *fp = fopen(path, "w");
    int i, j;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            fprintf(fp, "%d ", b->bd[j][i]);
        }
        fputc('\n', fp);
    }
    fclose(fp);
}


//game finished ?

int isEnd(Board *b)
{
    if(b->p1 + b->p2 == N * N)
        return TRUE;
    else
        return FALSE;
}



//for minimax
void undoMove(Board *b, int x, int y, int pos)
{
    char kapa = ~pos & 0x0F;
    if(b->bd[x][y] == P1)
        b->p1--;
    else if(b->bd[x][y] == P2)
        b->p2--;
    b->bd[x][y] &= kapa;
    if(pos == UP && y > 0)
    {
        kapa = ~DOWN & 0x0F;
        if(b->bd[x][y - 1] == P1)
            b->p1--;
        else if(b->bd[x][y - 1] == P2)
            b->p2--;
        b->bd[x][y - 1] &= kapa;
    }
    else if(pos == DOWN && y < N - 1)
    {
        kapa = ~DOWN & 0x0F;
        kapa = ~UP & 0x0F;
        if(b->bd[x][y + 1] == P1)
            b->p1--;
        else if(b->bd[x][y + 1] == P2)
            b->p2--;
        b->bd[x][y + 1] &= kapa;
    }
    else if(pos == LEFT && x > 0)
    {
        kapa = ~RIGHT & 0x0F;
        if(b->bd[x - 1][y] == P1)
            b->p1--;
        else if(b->bd[x - 1][y] == P2)
            b->p2--;
        b->bd[x - 1][y] &= kapa;
    }
    else if(pos == RIGHT && x < N - 1)
    {
        kapa = ~LEFT & 0x0F;
        if(b->bd[x + 1][y] == P1)
            b->p1--;
        else if(b->bd[x + 1][y] == P2)
            b->p2--;
        b->bd[x + 1][y] &= kapa;
    }
}




void displayBoard(Board *b)
{
    int i, j;
    puts("Board: ");
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            printf("o");
            if((b->bd[j][i] & UP) != 0)
                printf("---");
            else
                printf("   ");
            if(j == N - 1)
                printf("o\n");
        }
        for(j = 0; j < N; j++)
        {
            if((b->bd[j][i] & LEFT) != 0)
                printf("| ");
            else
                printf("  ");
            if(b->bd[j][i] == P1)
                printf("1 ");
            else if(b->bd[j][i] == P2)
                printf("2 ");
            else
                printf("  ");
        }
        if((b->bd[N - 1][i] & RIGHT))
            printf("|");
        puts("");
        if(i == N - 1)
        {
            for(j = 0; j < N; j++)
            {
                printf("o");
                if((b->bd[j][i] & DOWN) != 0)
                    printf("---");
                else
                    printf("   ");
                if(j == N - 1)
                    printf("o\n");
            }
        }
    }
    printf("Score:\n\tP1: %d P2: %d\n", b->p1, b->p2);
}
