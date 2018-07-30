#include <board.h>
#include <stdio.h>
#include <globals.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    Board bd;
    init(&bd);
    
	int i = 0;  // who's turn even-P2 odd-P1
    
    /*setBoard(&bd, argv[1]);*/
    
    while(!isEnd(&bd))
    {
        if(i % 2 == 0)
        {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            int kapa = makeMove(&bd, a, b, P2, c);
            if(kapa == 2)
                i--;
        }
        
		else
        {
            if(makeOptimalMove(&bd))
                i--;
        }
        
        displayBoard(&bd);
        i++;
    }
    /*saveBoard(&bd, argv[1]);*/
} 

/*
 * 0 0 0 0 0
 * 0 0 0 0 0
 * 0 0 0 0 0
 * 0 0 0 0 0
 * 0 0 0 0 0
 *
 */
