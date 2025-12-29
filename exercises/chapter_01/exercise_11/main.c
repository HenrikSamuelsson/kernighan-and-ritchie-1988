#include <stdio.h>
#include <stdlib.h>

#define IN 1  /* Inside of a word. */
#define OUT 0 /* Outside of a word. */

/* Count lines, words, and characters in input. */
int main(void)
{
    int c;
    int nl = 0;
    int nw = 0;
    int nc = 0;
    int state = OUT;

    while ((c = getchar()) != EOF)
    {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT)
        {
            state = IN;
            ++nw;
        }
    }

    printf("Number of lines = %d\n", nl);
    printf("Number of words = %d\n", nw);
    printf("Number of characters = %d\n", nc);

    return EXIT_SUCCESS;
}
