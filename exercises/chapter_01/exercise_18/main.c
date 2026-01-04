#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 /* Maximum input line length. */

int my_getline(char s[], int lim);

/* Purpose: Print input lines after removing trailing blanks and tabs.
 * Entirely blank lines (empty or whitespace-only) are not printed. */
int main(void)
{
    int len;            /* Actual line text length (excluding '\n'). */
    char line[MAXLINE]; /* Stored line prefix (text only). */

    while ((len = my_getline(line, MAXLINE)) >= 0)
    {
        int stored_len;
        int index;
        int trimming;

        (void)len; /* len is still useful for other exercises; not
                      needed here. */

        /* Compute length of the stored prefix (up to '\0'). */
        stored_len = 0;
        while (line[stored_len] != '\0')
        {
            ++stored_len;
        }

        /* Remove trailing spaces and tabs from the stored prefix. */
        index = stored_len - 1;
        trimming = 1;

        while (index >= 0 && trimming)
        {
            if (line[index] == ' ' || line[index] == '\t')
            {
                line[index] = '\0';
                --index;
            }
            else
            {
                trimming = 0;
            }
        }

        /* Print line if not empty after trimming. */
        if (line[0] != '\0')
        {
            printf("%s\n", line);
        }
    }
    return EXIT_SUCCESS;
}

/*
 * my_getline: Read one line of text into s, return the line length.
 *
 * Contract:
 * - Stores up to (lim - 1) characters of text in s, always '\0'
 * terminated.
 * - Does not store '\n'.
 * - Returns the full text length (excluding '\n'), even if longer than
 * the buffer.
 * - Returns 0 for an empty line.
 * - Returns -1 if EOF occurs before any characters are read (no more
 * lines).
 */
int my_getline(char s[], int lim)
{
    int c;
    int len = 0;     /* Total text length (excluding '\n'). */
    int idx = 0;     /* Number of characters stored into s. */
    int reading = 1; /* Loop-control flag. */

    if (lim <= 0)
    {
        return -1;
    }

    while (reading)
    {
        c = getchar();

        if (c == EOF)
        {
            reading = 0;
        }
        else if (c == '\n')
        {
            reading = 0;
        }
        else
        {
            ++len;

            if (idx < (lim - 1))
            {
                s[idx] = c;
                ++idx;
            }
        }
    }

    s[idx] = '\0';

    /* EOF before any text and before any newline => no more lines. */
    if ((c == EOF) && (len == 0))
    {
        return -1;
    }

    return len;
}
