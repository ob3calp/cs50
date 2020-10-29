#include <stdio.h>
#include <math.h>
#include <cs50.h>

// every coin as cents
const int QUARTER = 25;
const int DIME = 10;
const int NICKEL = 5;
const int PENNY = 1;

int main(void)
{
    int count = 0;
    float dollar_amount = 0;

    while (dollar_amount <= 0)
    {
        dollar_amount = get_float("Change owed: ");
    }

    // convert to cents, from float to int
    int cent_amount = round(dollar_amount * 100);

    // iterate over coins as per greedy algorithm, could probably make this neater
    while (cent_amount >= QUARTER)
    {
        cent_amount = cent_amount - QUARTER;
        count++;
    }

    while (cent_amount >= DIME)
    {
        cent_amount = cent_amount - DIME;
        count++;
    }

    while (cent_amount >= NICKEL)
    {
        cent_amount = cent_amount - NICKEL;
        count++;
    }

    while (cent_amount >= PENNY)
    {
        cent_amount = cent_amount - PENNY;
        count++;
    }

    // print out amount of coins resulted
    printf("%i\n", count);

    return 0;
}