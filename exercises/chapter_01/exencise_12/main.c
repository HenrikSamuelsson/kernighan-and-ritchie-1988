#include <stdio.h>
#include <stdlib.h>

/* For tracking state of word input. */
#define INSIDE_OF_WORD 1
#define OUTSIDE_OF_WORD 0

/* Function that takes input and prints it back one word per line. */
int main(void)
{
    int input_char;
    int state = OUTSIDE_OF_WORD;

    while (EOF != (input_char = getchar()))
    {
        int input_is_whitespace = input_char == '\n' ||
                                  input_char == '\t' ||
                                  input_char == ' ';

        if (input_is_whitespace)
        {
            if (INSIDE_OF_WORD == state)
            {
                /* Move cursor down when a word ends. */
                putchar('\n');
                state = OUTSIDE_OF_WORD;
            }
        }
        else
        {
            if (OUTSIDE_OF_WORD == state)
            {
                state = INSIDE_OF_WORD;
            }
            putchar(input_char);
        }
    }

    if (INSIDE_OF_WORD == state)
    {
        /* Move cursor down if inside word when program terminates. */
        putchar('\n');
    }

    return EXIT_SUCCESS;
}
