#include <stdio.h>
#include <stdlib.h>

#define TAB_WIDTH 8

#define NO_SPACE 0
#define IN_SPACE 1

int next_tab_stop(int col);
void flush_spaces(int *col, int pending_spaces);

int main(void)
{
    int c;
    int col = 0;
    int pending_spaces = 0;
    int state = NO_SPACE;

    /* Read until newline; program ends after printing the transformed
     * line. */
    while (((c = getchar()) != '\n') && (c != EOF))
    {
        if (c == ' ')
        {
            if (state == NO_SPACE)
            {
                state = IN_SPACE;
                pending_spaces = 1;
            }
            else
            {
                pending_spaces++;
            }
        }
        else
        {
            if (state == IN_SPACE)
            {
                flush_spaces(&col, pending_spaces);
                pending_spaces = 0;
                state = NO_SPACE;
            }

            putchar(c);

            if (c == '\t')
            {
                col = next_tab_stop(col);
            }
            else
            {
                col++;
            }
        }
    }

    /* Flush trailing spaces before ending the line. */
    if (state == IN_SPACE)
    {
        flush_spaces(&col, pending_spaces);
    }

    putchar('\n');

    return EXIT_SUCCESS;
}

int next_tab_stop(int col)
{
    return col + (TAB_WIDTH - (col % TAB_WIDTH));
}

void flush_spaces(int *col, int pending_spaces)
{
    int target = *col + pending_spaces;

    while (*col < target)
    {
        int next = next_tab_stop(*col);

        if ((next <= target) && (next > *col))
        {
            putchar('\t');
            *col = next;
        }
        else
        {
            putchar(' ');
            (*col)++;
        }
    }
}
