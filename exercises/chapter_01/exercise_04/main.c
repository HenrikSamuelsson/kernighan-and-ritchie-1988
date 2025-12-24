#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const int celsius_min = -20;
    const int celsius_max = 150;
    const int step = 20;

    int celsius = celsius_min;
    float fahrenheit;

    printf(" C      F  \n");
    printf("---   -----\n");

    while (celsius <= celsius_max)
    {
        fahrenheit = (float)celsius * (9.0f / 5.0f) + 32.0f;
        printf("%3d   %5.1f\n", celsius, fahrenheit);
        celsius = celsius + step;
    }

    return EXIT_SUCCESS;
}
