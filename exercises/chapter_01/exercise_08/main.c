#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int next_character;
    int number_of_blanks = 0;
    int number_of_tabs = 0;
    int number_of_newlines = 0;

    while ((next_character = getchar()) != EOF)
    {
        if (' ' == next_character)
        {
            ++number_of_blanks;
        }
        else if ('\t' == next_character)
        {
            ++number_of_tabs;
        }
        else if ('\n' == next_character)
        {
            ++number_of_newlines;
        }
        else
        {
            /* Character not counted - intentionally ignored. */
        }
    }

    printf("EOF seen: %d\n", next_character);
    printf("Number of blanks:   %4d\n", number_of_blanks);
    printf("Number of tabs:     %4d\n", number_of_tabs);
    printf("Number of newlines: %4d\n", number_of_newlines);

    return EXIT_SUCCESS;
}
