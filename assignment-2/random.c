#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int max = atoi(argv[1]);

    for (int i = 0; i < max; ++i)
    {
        printf("%d ", rand() % 100);
    }

    return 0;
}