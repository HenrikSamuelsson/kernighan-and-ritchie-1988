#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_DIGITS 10
#define NUM_OF_LETTERS 26

int main(void)
{
    int digits[NUM_OF_DIGITS] = {0};
    int uppercase_letters[NUM_OF_LETTERS] = {0};
    int lowercase_letters[NUM_OF_LETTERS] = {0};

    int input_char;

    while ((input_char = getchar()) != EOF)
    {
        if (input_char >= '0' && input_char <= '9')
        {
            ++digits[input_char - '0'];
        }
        else if (input_char >= 'A' && input_char <= 'Z')
        {
            ++uppercase_letters[input_char - 'A'];
        }
        else if (input_char >= 'a' && input_char <= 'z')
        {
            ++lowercase_letters[input_char - 'a'];
        }
    }

    for (int index = 0; index < NUM_OF_DIGITS; ++index)
    {
        int count = digits[index];
        if (count > 0)
        {
            putchar('0' + index);
            putchar('|');
            for (int i = 0; i < count; ++i)
            {
                putchar('#');
            }
            putchar('\n');
        }
    }

    for (int index = 0; index < NUM_OF_LETTERS; ++index)
    {
        int count = uppercase_letters[index];
        if (count > 0)
        {
            putchar('A' + index);
            putchar('|');
            for (int i = 0; i < count; ++i)
            {
                putchar('#');
            }
            putchar('\n');
        }
    }

    for (int index = 0; index < NUM_OF_LETTERS; ++index)
    {
        int count = lowercase_letters[index];
        if (count > 0)
        {
            putchar('a' + index);
            putchar('|');
            for (int i = 0; i < count; ++i)
            {
                putchar('#');
            }
            putchar('\n');
        }
    }

    return EXIT_SUCCESS;
}
