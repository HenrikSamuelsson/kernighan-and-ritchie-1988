#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int res_expr;

    while ((res_expr = (getchar() != EOF)))
    {
        printf("%d", res_expr);
    }
    printf("%d", res_expr); /* prints the final 0 */

    return EXIT_SUCCESS;
}
