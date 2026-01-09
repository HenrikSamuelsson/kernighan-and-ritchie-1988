#include <stdio.h>
#include <stdlib.h>

/* Max input line length, including an ending null terminator. */
#define MAXLINE 1001

/* Number of columns used for tab. */
#define N 4

int my_getline(char s[], int lim);
void detab(char source[], char result[], int length, int limit);

int main(void)
{
    int len;            /* Actual line text length (excluding '\n'). */
    char line[MAXLINE]; /* Stored line prefix (text only). */
    char no_tab_line[MAXLINE];

    while ((len = my_getline(line, MAXLINE)) >= 0)
    {
        detab(line, no_tab_line, len, MAXLINE);
        printf("%s\n", no_tab_line);
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
 * - Returns the full text length (excluding '\n'), even if longer
 * than the buffer.
 * - Returns 0 for an empty line.
 * - Returns -1 if EOF occurs before any characters are read (no
 * more lines).
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

    /* EOF before any text and before any newline => no more lines.
     */
    if ((c == EOF) && (len == 0))
    {
        return -1;
    }

    return len;
}

void detab(char source[], char result[], int length, int limit)
{
    int s_idx = 0;
    int r_idx = 0;
    int n_space;

    if (limit <= 0)
    {
        return;
    }

    while ((s_idx < length) && (r_idx < (limit - 1)))
    {
        if ('\t' != source[s_idx])
        {
            result[r_idx++] = source[s_idx++];
        }
        else
        {
            n_space = N - (r_idx % N);
            while ((n_space-- > 0) && (r_idx < (limit - 1)))
            {
                result[r_idx++] = ' ';
            }
            s_idx++;
        }
    }

    result[r_idx] = '\0';
}
