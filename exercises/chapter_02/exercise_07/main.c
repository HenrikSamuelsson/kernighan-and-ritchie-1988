#include <stdio.h>

/*
 * Returns x with the n bits ending at position p inverted.
 *
 * Bit positions are counted from the right, starting at 0.
 */
unsigned invert(unsigned x, int p, int n)
{
    unsigned shift = (unsigned)(p + 1 - n);
    unsigned field_mask = (1U << n) - 1U;
    unsigned positioned_mask = field_mask << shift;

    return x ^ positioned_mask;
}

int main(void)
{
    unsigned x, result;

    /* Test case 1: invert bits 4..2 */
    x = 0xAA; /* 10101010 */
    result = invert(x, 4, 3);
    printf("Test 1: 0x%02X\n", result); /* expected: 0xB6 (10110110) */

    /* Test case 2: invert bits 5..4 */
    x = 0xFF; /* 11111111 */
    result = invert(x, 5, 2);
    printf("Test 2: 0x%02X\n", result); /* expected: 0xCF (11001111) */

    /* Test case 3: invert lowest 3 bits */
    x = 0x00; /* 00000000 */
    result = invert(x, 2, 3);
    printf("Test 3: 0x%02X\n", result); /* expected: 0x07 (00000111)*/

    return 0;
}
