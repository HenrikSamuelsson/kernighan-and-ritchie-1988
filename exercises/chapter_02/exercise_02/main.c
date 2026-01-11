#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 80

int main(void)
{
    char line[MAXLINE];
    int lim = MAXLINE;
    int c = 0;
    int i = 0;

    /* Read up to lim-1 chars, stopping at newline or EOF. */
    while (i < lim - 1)
    {
        c = getchar();

        if (c == EOF)
        {
            break;
        }

        if (c == '\n')
        {
            break;
        }

        line[i] = (char)c;
        ++i;
    }

    if (c == '\n')
    {
        line[i] = (char)c;
        ++i;
    }

    line[i] = '\0';

    printf("%s\n", line);
    return EXIT_SUCCESS;
}
