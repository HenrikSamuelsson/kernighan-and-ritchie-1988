/*
 * K&R 3-1 benchmark: compare book-style binsearch vs
 * one-test-per-iteration.
 *
 * Build (PowerShell):
 *   gcc -O2 -Wall -Wextra -std=c17 main.c -o bench.exe
 *
 * Run:
 *   .\bench.exe
 */

#include <stdio.h>
#include <windows.h>

/* High-resolution timer (seconds) */
static double now_seconds(void)
{
    static LARGE_INTEGER freq;
    static int init = 0;
    LARGE_INTEGER t;

    if (!init)
    {
        QueryPerformanceFrequency(&freq);
        init = 1;
    }

    QueryPerformanceCounter(&t);
    return (double)t.QuadPart / (double)freq.QuadPart;
}

/* Function prototypes */
int binsearch_book(int x, const int v[], int n);
int binsearch_one_test(int x, const int v[], int n);

static double bench_book(const int *v, int n, int iters,
                         volatile int *sink);
static double bench_one(const int *v, int n, int iters,
                        volatile int *sink);

/* --------------------------------------------------------------------------
 */
/* Implementations */
/* --------------------------------------------------------------------------
 */

/* K&R "book" version */
int binsearch_book(int x, const int v[], int n)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (x < v[mid])
        {
            high = mid - 1;
        }
        else if (x > v[mid])
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }

    return -1;
}

/* One test per loop iteration (final equality check after loop) */
int binsearch_one_test(int x, const int v[], int n)
{
    int low = 0;
    int high = n; /* exclusive */

    while (low < high)
    {
        int mid = low + (high - low) / 2;

        /* One comparison against v[mid] per iteration */
        if (x <= v[mid])
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
    }

    if (low < n && v[low] == x)
    {
        return low;
    }
    return -1;
}

/* --------------------------------------------------------------------------
 */
/* Benchmark */
/* --------------------------------------------------------------------------
 */

static double bench_book(const int *v, int n, int iters,
                         volatile int *sink)
{
    double t0 = now_seconds();

    /* Deterministic pseudo-random workload for more stable branch
     * behavior */
    unsigned state = 0x12345678u;

    for (int i = 0; i < iters; i++)
    {
        state = state * 1103515245u + 12345u;      /* LCG */
        int x = (int)(state % (2u * (unsigned)n)); /* mix hits/misses */
        *sink += binsearch_book(x, v, n);
    }

    double t1 = now_seconds();
    return t1 - t0;
}

static double bench_one(const int *v, int n, int iters,
                        volatile int *sink)
{
    double t0 = now_seconds();

    unsigned state = 0x12345678u;

    for (int i = 0; i < iters; i++)
    {
        state = state * 1103515245u + 12345u;
        int x = (int)(state % (2u * (unsigned)n));
        *sink += binsearch_one_test(x, v, n);
    }

    double t1 = now_seconds();
    return t1 - t0;
}

int main(void)
{
    enum
    {
        N = 100000
    };
    static int v[N];

    /* Sorted array (even numbers) */
    for (int i = 0; i < N; i++)
    {
        v[i] = i * 2;
    }

    const int iters = 25000000; /* increase for lower noise if needed */
    const int repeats = 6;

    volatile int sink = 0;
    double book_sum = 0.0;
    double one_sum = 0.0;

    for (int r = 0; r < repeats; r++)
    {
        /* A/B */
        double t_book_1 = bench_book(v, N, iters, &sink);
        double t_one_1 = bench_one(v, N, iters, &sink);

        /* B/A */
        double t_one_2 = bench_one(v, N, iters, &sink);
        double t_book_2 = bench_book(v, N, iters, &sink);

        double t_book = (t_book_1 + t_book_2) / 2.0;
        double t_one = (t_one_1 + t_one_2) / 2.0;

        book_sum += t_book;
        one_sum += t_one;

        printf("run %d: book=%.6f s, one-test=%.6f s\n", r + 1, t_book,
               t_one);
    }

    printf("sink=%d\n", sink);
    printf("avg: book=%.6f s, one-test=%.6f s\n", book_sum / repeats,
           one_sum / repeats);

    return 0;
}
