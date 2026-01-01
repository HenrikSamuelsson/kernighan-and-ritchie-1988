#include <stdio.h>
#include <stdlib.h>

/* For tracking state of word input. */
#define INSIDE_OF_WORD 1
#define OUTSIDE_OF_WORD 0

/* Number of different word lengths that we track. */
#define MAX_WORD_LENGTH 10

/* Print a histogram of word lengths in the input. */
int main(void)
{
    int input_char;
    int char_count = 0;
    int state = OUTSIDE_OF_WORD;
    int char_counts[MAX_WORD_LENGTH] = {0};

    while (EOF != (input_char = getchar()))
    {
        int input_is_whitespace = input_char == '\n' ||
                                  input_char == '\t' ||
                                  input_char == ' ';

        if (input_is_whitespace)
        {
            if (INSIDE_OF_WORD == state)
            {
                if (char_count > 0 && char_count <= MAX_WORD_LENGTH)
                {
                    char_counts[char_count - 1]++;
                }
                else
                {
                    printf("ERROR Too long word entered.\n");
                }
                state = OUTSIDE_OF_WORD;
                char_count = 0;
            }
        }
        else
        {
            if (OUTSIDE_OF_WORD == state)
            {
                state = INSIDE_OF_WORD;
                char_count = 0;
            }
            char_count++;
        }
    }

    /* Handle the case that there is no whitespace after last word.*/
    if (INSIDE_OF_WORD == state)
    {
        if (char_count > 0 && char_count <= MAX_WORD_LENGTH)
        {
            char_counts[char_count - 1]++;
        }
        else
        {
            printf("ERROR Too long word entered.\n");
        }
    }

    for (int index = 0; index < MAX_WORD_LENGTH; index++)
    {
        int label = index + 1;
        printf(" %2d |", label);
        for (int length = 0; length < char_counts[index]; length++)
        {
            printf("#");
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
