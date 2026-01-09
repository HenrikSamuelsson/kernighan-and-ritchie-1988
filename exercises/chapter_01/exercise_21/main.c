#include <stdio.h>
#include <stdlib.h>

/* Max input line length, including an ending null terminator. */
#define MAXLINE 1001

/* Number of columns used for tab. */
#define TAB_WIDTH 4

/* States depending on current input character is a space or not. */
#define NO_SPACE 0
#define SPACE 1

int my_getline(char s[], int lim);
void entab(const char src[], char dst[], int src_len, int dst_cap);

int main(void)
{
    int len;            /* Input line text length (excluding '\n'). */
    char line[MAXLINE]; /* Stored line prefix (text only). */
    char tab_line[MAXLINE];

    while ((len = my_getline(line, MAXLINE)) >= 0)
    {
        entab(line, tab_line, len, MAXLINE);
        printf("%s\n", tab_line);
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

void entab(const char src[], char dst[], int src_len, int dst_cap)
{
    int s_idx = 0;
    int r_idx = 0;
    int first_space_idx = 0;
    int n_space;
    int state = NO_SPACE;

    if (dst_cap <= 0)
    {
        return;
    }

    while ((s_idx < src_len) && (r_idx < (dst_cap - 1)))
    {
        if (' ' != src[s_idx])
        {
            state = NO_SPACE;
            dst[r_idx] = src[s_idx];
            r_idx++;
        }
        else
        {
            if (NO_SPACE == state)
            {
                first_space_idx = r_idx;
            }
            state = SPACE;
        }
        // Another character in the source have been handled.
        s_idx++;
    }

    dst[r_idx] = '\0';
}
