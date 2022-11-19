#include <stdio.h>
#include <pthread.h>

void main()
{
    for (int i = 0; i < 10; i++)
    {
        printf("\033[%d;40Hj=%d", i, i);
        printf("\033[%d;60Hj=%d", i, i);
        printf("\033[%d;20Hi=%d", i, i);
        // printf("\033[2J");
    }
    printf("\n");
}