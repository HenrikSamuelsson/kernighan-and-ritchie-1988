/*
 * Exercise 4-1 (K&R)
 * Rightmost occurrence of t in s.
 */

#include <stdio.h>

int strrindex(const char s[], const char t[]);

/* ---------------- self-test main ---------------- */

int main(void)
{
    struct
    {
        const char *s;
        const char *t;
        int expected;
    } tests[] = {{"hello world", "world", 6},
                 {"could would should", "ould", 14},
                 {"aaaaa", "aa", 3},
                 {"abcdef", "xyz", -1},
                 {"abcdef", "", 0},
                 {"", "a", -1},
                 {"", "", 0}};

    int i;
    int result;

    for (i = 0; i < (int)(sizeof(tests) / sizeof(tests[0])); i++)
    {
        result = strrindex(tests[i].s, tests[i].t);

        printf("s=\"%s\", t=\"%s\" -> %d", tests[i].s, tests[i].t,
               result);

        if (result == tests[i].expected)
        {
            printf("  [OK]\n");
        }
        else
        {
            printf("  [FAIL, expected %d]\n", tests[i].expected);
        }
    }

    return 0;
}

/* ---------------- implementation ---------------- */

/* strrindex: return index of rightmost occurrence of t in s, -1 if none
 */
int strrindex(const char s[], const char t[])
{
    int i, j, k;
    int rightmost = -1;

    if (t[0] == '\0')
    {
        /* Empty pattern convention */
        return 0;
    }

    for (i = 0; s[i] != '\0'; i++)
    {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
        {
            ;
        }

        if (t[k] == '\0')
        {
            rightmost = i;
        }
    }

    return rightmost;
}
