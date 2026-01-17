#include <stdio.h>

/*
 * Returns x rotated to the right by n bit positions.
 *
 * Rotation is performed on an unsigned int.
 */
unsigned rightrot(unsigned x, int n)
{
    unsigned word_bits = sizeof(unsigned) * 8U;
    unsigned r = (unsigned)n % word_bits;

    if (r == 0U)
    {
        return x;
    }

    unsigned mask = (1U << r) - 1U;
    unsigned lower_bits = x & mask;
    unsigned shifted = x >> r;
    unsigned wrapped = lower_bits << (word_bits - r);
    unsigned result = shifted | wrapped;

    return result;
}

int main(void)
{
    unsigned x, result;

    /* Test case 1: rotate right by 3 */
    x = 0xAA; /* 1010_1010 */
    result = rightrot(x, 3);
    printf("Test 1: 0x%08X\n", result); /* expected: 0x40000015 */

    /* Test case 2: rotate right by 1 */
    x = 0x01; /* 0000_0001 */
    result = rightrot(x, 1);
    printf("Test 2: 0x%08X\n", result); /* expected: 0x80000000 */

    /* Test case 3: rotate right by word size (no change) */
    x = 0xF0;
    result = rightrot(x, sizeof(unsigned) * 8);
    printf("Test 3: 0x%08X\n", result); /* expected: 0x000000F0 */

    return 0;
}
