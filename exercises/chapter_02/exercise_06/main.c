#include <stdio.h>

/*
 * Returns x with the n bits ending at position p replaced by
 * the rightmost n bits of y.
 *
 * Bit positions are counted from the right, starting at 0.
 */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned shift = (unsigned)(p + 1 - n);
    unsigned field_mask = (1U << n) - 1U;

    unsigned y_n = y & field_mask;
    unsigned positioned_mask = field_mask << shift;

    unsigned x_cleared = x & ~positioned_mask;
    unsigned y_positioned = y_n << shift;

    return x_cleared | y_positioned;
}

int main(void)
{
    unsigned x, y, result;

    /* Test case 1: insert the lowest 3 bits of y into x at
     * positions 4..2 */
    x = 0xAA; /* 10101010 */
    y = 0x0F; /* 00001111 */
    result = setbits(x, 4, 3, y);
    printf("Test 1: 0x%02X\n", result); /* expected: 0xBE */

    /* Test case 2: clear bits 5..4 of x by inserting zero bits from y
     */
    x = 0xFF; /* 11111111 */
    y = 0x00; /* 00000000 */
    result = setbits(x, 5, 2, y);
    printf("Test 2: 0x%02X\n", result); /* expected: 0xE7 */

    /* Test case 3: insert the lowest 3 bits of y into positions 3..1 of
     * x */
    x = 0x00;
    y = 0x05; /* 00000101 */
    result = setbits(x, 3, 3, y);
    printf("Test 3: 0x%02X\n", result); /* expected: 0x14 */

    return 0;
}
