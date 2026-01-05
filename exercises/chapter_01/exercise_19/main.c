#include <stdio.h>
#include <stdlib.h>

/* Max input line length, including an ending null terminator*/
#define MAXLINE 1001 /* Maximum input line length. */

int my_getline(char s[], int lim);
void reverse(char s[]);

int main(void)
{
    int len;            /* Actual line text length (excluding '\n'). */
    char line[MAXLINE]; /* Stored line prefix (text only). */

    while ((len = my_getline(line, MAXLINE)) >= 0)
    {
        if (len > MAXLINE - 1)
        {
            printf("Too long string, max length is %d.\n", MAXLINE - 1);
        }
        else
        {
            reverse(line);
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

void reverse(char s[])
{
    int len;
    int index;

    /* Find the length of the string s.*/
    for (index = 0; s[index] != '\0'; ++index)
    {
        ; /* Do nothing */
    }
    len = index;

    int left;
    int right;

    /* Reverse by switching place of two characters at a time. */
    for (left = 0, right = len - 1; left < right; ++left, --right)
    {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
    }
}
