#include <stdio.h>
#include <cs50.h>

const int MIN_HEIGHT = 1;
const int MAX_HEIGHT = 8;

int main(void)
{
    int height = 0;

    while (height > MAX_HEIGHT || height < MIN_HEIGHT)
    {
        height = get_int("Enter pyramid height: ");
    }

    // i is row number from top
    for (int i = 1; i <= height; i++)
    {
        // FIRST PYRAMID
        // number of blanks in row is height - i
        for (int j = 1; j <= (height - i); j++)
        {
            printf(" ");
        }
        // number of blocks in row is i
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        // GAP
        printf("  ");

        // SECOND PYRAMID
        // number of blocks in row is i
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        // END OF ROW
        printf("\n");
    }

    return 0;
}