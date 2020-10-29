#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }

        }

        record_preferences(ranks);

        printf("\n");
    }


    // DEBUG, print out preferences matrix
    /*
    printf("Preferences 2d array\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d", preferences[i][j]);
        }
        printf("\n");
    }
    */

    add_pairs();

    // DEBUG, print out pairs
    /*
    printf("Number of candidate pairs: %d\n", pair_count);
    for (int i = 0; i < pair_count; i++)
    {
        printf("W: %d L: %d V: %d\n", pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser]);
    }
    */

    sort_pairs();

    // DEBUG, print out sorted pairs
    /*
    printf("\n");
    for (int i = 0; i < pair_count; i++)
    {
        printf("W: %d L: %d V: %d\n", pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser]);
    }
    */

    lock_pairs();

    // DEBUG, print out locked pairs matrix
    /*
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d", locked[i][j]);
        }
        printf("\n");
    }
    */

    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // use linear search algorithm to determine if name is valid
    // if found then update voter rank array with candidate index number
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;

            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // preferences is a 2d array where both axii are candidates and where i would be preferred over j by n voters
    // iterate over every pair combination
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            // add a voter to the candidate pair (ignoring self)
            if (i != j)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int n = 0;
    // traverse thru 2d array row by row looking for column values that are > 0
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // when found check that inverse doesn't have a greater vote count
            // ties are not to be added to pairs array
            if (preferences[i][j] > preferences[j][i])
            {
                // add winner and loser
                pairs[n].winner = i;
                pairs[n].loser = j;
                n++;
            }
        }
    }

    // update pair_count to how many pairs we found
    pair_count = n;

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble sort algorithm, sort pairs by win strength
    // use temp value to switch values
    pair temp;
    bool sorted = false;

    while (sorted == false)
    {
        // default state is sorted
        sorted = true;

        for (int i = 0; i < pair_count; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                temp = pairs[i + 1];
                pairs[i + 1] = pairs[i];
                pairs[i] = temp;

                // if a switch was done then sorted is false, iterate atleast one more time
                sorted = false;
            }
        }
    }

    return;
}

// cycle_check, return true if graph creates a cycle
bool cycle_check(int w, int l, int iter)
{
    // if the loser is a winner in existing lock pair look at that pair
    // keep going down the rabbit hole until pair_count steps taken

    // when pair_count iters are done we've gone as far as the rabbit hole goes
    if (iter == 0)
    {
        return false;
    }

    // if at any point winner being tested is loser in existing locked pair then it creates a cycle
    if (w == l)
    {
        return true;
    }

    // call function recursively if loser is a winner in existing lock pair
    for (int k = 0; k < pair_count; k++)
    {
        if (locked[l][k] == true && cycle_check(w, k, iter - 1))
        {
            return true;
        }
    }

    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // locked is a 2d array indicating that i is locked over j if n == true
    // start from pairs[0], the strongest pair that is
    for (int k = 0; k < pair_count; k++)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                // search for corresponding i and j pair, discard if j and i pair is already locked (this should
                // automatically be weaker if pairs we're sorted correctly) and it doesn't create a cycle
                if (pairs[k].winner == i && pairs[k].loser == j && locked[j][i] != true && cycle_check(i, j, pair_count) == false)
                {
                    // lock pair i and j
                    locked[i][j] = true;
                }
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int check = 0;
    // winner is the candidate who has no arrows pointed to himself
    // in other words, a candidate with it's column values all false is winner
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true && i != j)
            {
                check = 1;
                break;
            }
        }
        if (check == 0)
        {
            printf("%s\n", candidates[i]);
        }
        check = 0;
    }

    return;
}