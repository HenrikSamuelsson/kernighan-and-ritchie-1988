#include <stdio.h>
#include <stdlib.h>

/* Max input line length, including an ending null terminator. */
#define MAXLINE 1001

/* Number of columns used for tab. */
#define TAB_WIDTH 4

int my_getline(char s[], int lim);
int next_tab_stop(int col);
void flush_spaces(int *col, int *r_idx, char dst[], int dst_cap,
                  int pending_spaces);
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

int next_tab_stop(int col)
{
    return col + (TAB_WIDTH - (col % TAB_WIDTH));
}

/* Flush pending spaces from current column, emitting minimal
   tabs/spaces. Updates col and r_idx accordingly. Never writes past
   dst_cap - 1. */
void flush_spaces(int *col, int *r_idx, char dst[], int dst_cap,
                  int pending_spaces)
{
    int target = *col + pending_spaces;

    while ((*col < target) && (*r_idx < (dst_cap - 1)))
    {
        int next = next_tab_stop(*col);

        /* Emit a tab if it moves us forward and does not overshoot the
         * target. */
        if ((next <= target) && (next > *col))
        {
            dst[*r_idx] = '\t';
            (*r_idx)++;
            *col = next;
        }
        else
        {
            dst[*r_idx] = ' ';
            (*r_idx)++;
            (*col)++;
        }
    }
}

void entab(const char src[], char dst[], int src_len, int dst_cap)
{
    int s_idx = 0;
    int r_idx = 0;
    int col = 0;
    int pending_spaces = 0;

    if ((dst_cap <= 0) || (dst == NULL))
    {
        return;
    }

    /* If src is NULL, produce empty string. */
    if (src == NULL)
    {
        dst[0] = '\0';
        return;
    }

    while ((s_idx < src_len) && (r_idx < (dst_cap - 1)))
    {
        char c = src[s_idx];

        if (c == ' ')
        {
            pending_spaces++;
            s_idx++;
            continue;
        }

        /* We hit a non-space: flush any pending spaces first. */
        if (pending_spaces > 0)
        {
            flush_spaces(&col, &r_idx, dst, dst_cap, pending_spaces);
            pending_spaces = 0;

            /* If flushing filled the output buffer, stop. */
            if (r_idx >= (dst_cap - 1))
            {
                break;
            }
        }

        /* Copy the non-space char and update column. */
        dst[r_idx] = c;
        r_idx++;

        if (c == '\n')
        {
            col = 0;
        }
        else if (c == '\t')
        {
            col = next_tab_stop(col);
        }
        else
        {
            col++;
        }

        s_idx++;
    }

    /* End of input or output full: flush trailing spaces if any. */
    if ((pending_spaces > 0) && (r_idx < (dst_cap - 1)))
    {
        flush_spaces(&col, &r_idx, dst, dst_cap, pending_spaces);
    }

    dst[r_idx] = '\0';
}
