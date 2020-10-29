#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

// Coleman-Liau's formula
// L = average number of letters per 100 words
// S = average number of sentences per 100 words
// index = 0.0588 * L - 0.296 * S - 15.8

int main(void)
{
    string text;
    int letters = 0;
    int words = 0;
    int sentences = 0;

    // get user input
    text = get_string("Insert text: ");

    // iterate thru array
    // every char decimal value of 65 to 90 and 97 to 122 are letters
    // every word is separated by a space (decimal value of 32)
    // every sentence is separated by a period, exclamation mark or question mark (46, 63 or 33)
    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        else if (isspace(text[i]))
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    // Every word is terminated by a space
    // We may assume that the last word doesn't end in space and thus we account for it
    words++;

    // calculate subvalues
    // int type values divided will return int, so convert int words to float
    float L = (100 / (float) words) * letters;
    float S = (100 / (float) words) * sentences;

    // Coleman-Liau's formula
    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        // calculate grade (nearest whole number)
        printf("Grade %d\n", (int) round(index));
    }

    return 0;
}