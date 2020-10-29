#include <stdio.h>
#include <math.h>
#include <cs50.h>

// a function to get number of digits in an int
// keeps diving the int by 10 until number is <= 0
int get_int_digits(long long int d)
{
    int count = 0;
    while (d > 0)
    {
        d = d / 10;
        count++;
    }
    return count;
}

int main(void)
{
    // query for user input
    long long int number = get_long_long("Number: ");

    int number_of_digits = get_int_digits(number);

    // create an array with number of digits in number
    int cc_number[number_of_digits];

    // place invidual digits of numbers in array
    for (int i = number_of_digits; i > 0; i--)
    {
        long long int digit = pow(10, i - 1);
        cc_number[i] = (number / digit) % 10;
    }

    // sum of every even digit's multiplied by two digits, saved to a variable
    int sum_of_even = 0;
    for (int i = 2; i <= number_of_digits; i = i + 2)
    {
        int res = cc_number[i] * 2;
        // if product is double digits, then deconstruct those digits and sum them up
        if (res >= 10)
        {
            sum_of_even = sum_of_even + res % 10 + (res / 10) % 10;
        }
        else
        {
            sum_of_even = sum_of_even + res;
        }
    }

    // sum of every odd digit, saved to a variable
    int sum_of_odd = 0;
    for (int i = 1; i <= number_of_digits; i = i + 2)
    {
        sum_of_odd = sum_of_odd + cc_number[i];
    }

    // calculate and print checksum
    int checksum = sum_of_odd + sum_of_even;
    printf("Checksum: %d\n", checksum % 10);

    // if checksum is valid then determine which credit card company it belongs to
    // if checksum is valid but suitable credit card company not found then card is INVALID
    if (checksum % 10 == 0)
    {
        // VISA 16 or 13 digits and starting with 4
        if ((number_of_digits == 16 || number_of_digits == 13) && cc_number[number_of_digits] == 4)
        {
            printf("VISA\n");
        }
        // MASTERCARD 16 digits and starting with 51 to 55
        else if (number_of_digits == 16 && cc_number[number_of_digits] == 5 && cc_number[number_of_digits - 1] >= 1 && cc_number[number_of_digits - 1] <= 5)
        {
            printf("MASTERCARD\n");
        }
        // AMEX 15 digits and starting with 34 or 37
        else if (number_of_digits == 15 && cc_number[number_of_digits] == 3 && (cc_number[number_of_digits - 1] == 4 || cc_number[number_of_digits - 1] == 7))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // if checksum was other than valid then card is INVALID
    else
    {
        printf("INVALID\n");
    }

    return 0;
}