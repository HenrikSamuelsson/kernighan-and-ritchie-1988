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

/* Note examples shown as 8-bit values for clarity */
int main(void)
{
    unsigned x, result;

    /* Test case 1: invert bits 4..2
     *
     * x                = 0xAA = 1010_1010
     *
     * p = 4, n = 3
     * shift            = p + 1 - n = 4 + 1 - 3 = 2
     *
     * field_mask       = (1U << 3) - 1U
     *                  = 0000_0111
     *
     * positioned_mask  = field_mask << 2
     *                  = 0001_1100
     *
     * result           = x ^ positioned_mask
     *                  = 1010_1010
     *                  ^ 0001_1100
     *                  = 1011_0110 = 0xB6
     *
     */
    x = 0xAA; /* 1010_1010 */
    result = invert(x, 4, 3);
    printf("Test 1: 0x%02X\n", result); /* expected: 0xB6 (1011_0110) */

    /* Test case 2: invert bits 5..4 */
    x = 0xFF; /* 1111_1111 */
    result = invert(x, 5, 2);
    printf("Test 2: 0x%02X\n", result); /* expected: 0xCF (1100_1111) */

    /* Test case 3: invert lowest 3 bits */
    x = 0x00; /* 0000_0000 */
    result = invert(x, 2, 3);
    printf("Test 3: 0x%02X\n", result); /* expected: 0x07 (0000_0111)*/

    return 0;
}
