#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <cs50.h>

// number of alphabets, constant
const int ALPHA_COUNT = 26;

// function to check if argument string is valid (containing only alphabets and each letter only once)
// returns 1 if true
int isStringValid(string s)
{
    // test if string is 26 characters long
    if (strlen(s) != 26)
    {
        return 0;
    }

    // make an alphabet array and reset it
    int alphabets[ALPHA_COUNT];
    for (int i = 0; i < ALPHA_COUNT; i++)
    {
        alphabets[i] = 0;
    }

    // check that string contains only alphabets and each alphabet only once
    // if character is found with no alphabet decimal value then false
    // if alphabet is found then determine it's order and save to it's index
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // test if character is alphabet, if it is then determine it's order and save to index
        if (isalpha(s[i]))
        {
            alphabets[(int) toupper(s[i]) - 65] += 1;
        }
        // if char didn't satisfy above conditionals then it's not an alphabet
        else
        {
            return 0;
        }
    }

    // go thru the alphabet array, if value is other than 1 then that alphabet was in the string more than once or not at all
    for (int i = 0; i < ALPHA_COUNT; i++)
    {
        if (alphabets[i] != 1)
        {
            return 0;
        }
    }

    return 1;
}

string translateToCipher (string plaintext, string key)
{
    string ciphertext = plaintext;

    // replace plaintext string char by char with corresponding cipher char
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // only apply to alphabets
        if (isalpha(plaintext[i]))
        {
            // uppercase letter alphabet index is %c - 65, search for that index from the key and make it uppercase
            if (isupper(plaintext[i]))
            {
                ciphertext[i] = toupper(key[plaintext[i] - 65]);
            }
            // lowercase letter alphabet index is %c - 97, search for that index from the key and make it lowercase
            else if (islower(plaintext[i]))
            {
                ciphertext[i] = tolower(key[plaintext[i] - 97]);
            }
        }
    }

    return ciphertext;
}

// argc = argument count
// argv[0] = program name, then come the rest
int main(int argc, string argv[])
{
    // check that only 1 argument is given, it's 26 characters long and contains each alphabet only once
    if (argc != 2 || isStringValid(argv[1]) != 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // get user input
    string plaintext = get_string("plaintext: ");

    // output ciphertext
    printf("ciphertext: %s\n", translateToCipher(plaintext, argv[1]));

    return 0;
}