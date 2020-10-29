#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <cs50.h>

// function to check if argument string is number, returns 1 if true
int isStringNumber(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return 0;
        }
    }
    return 1;
}

// function to convert string of numbers to an int
int convertStringToInt(string s)
{
    int d = 0;

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        d += (s[i] - 48) * pow(10, n - i - 1);
    }

    return d;
}

string translateToCipher(string plaintext, int key)
{
    string ciphertext = plaintext;

    // calculate real key (eliminate "full rotations")
    int k = key % 26;

    // rotate chars in plaintext string by k (if past last char then rotate to beginning) and return result
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // only rotate alphabets
        if (isalpha(plaintext[i]))
        {
            // if key would be rotated past last char then do a full rotation
            if ((isupper(plaintext[i]) && plaintext[i] + k > 'Z') || (islower(plaintext[i]) && plaintext[i] + k > 'z'))
            {
                ciphertext[i] -= 26;
            }
            ciphertext[i] += k;
        }
    }

    return ciphertext;
}

// argc = argument count
// argv[0] = program name, then come the rest
int main(int argc, string argv[])
{
    // check that only 1 argument is given and that it's a number
    if (argc != 2 || isStringNumber(argv[1]) != 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // get user input
    string plaintext = get_string("plaintext: ");

    // convert string to number
    int key = convertStringToInt(argv[1]);

    // output ciphertext
    printf("ciphertext: %s\n", translateToCipher(plaintext, key));

    return 0;
}