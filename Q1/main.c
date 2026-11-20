#include <stdio.h>
#include <stddef.h>

/* Linear search: works on sorted or unsorted arrays. */
static long linear_search(const int a[], size_t n, int key, size_t *comparisons) {
    *comparisons = 0;
    for (size_t i = 0; i < n; ++i) {
        ++*comparisons;
        if (a[i] == key) return (long)i;
    }
    return -1;
}

/* Binary search requires the array to be sorted in ascending order. */
static long binary_search(const int a[], size_t n, int key, size_t *comparisons) {
    long low = 0, high = (long)n - 1;
    *comparisons = 0;
    while (low <= high) {
        long mid = low + (high - low) / 2;
        ++*comparisons;
        if (a[mid] == key) return mid;
        if (a[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main(void) {
    const int catalogue[] = {1021, 1048, 1103, 1190, 1222, 1305, 1377, 1402, 1460, 1533};
    const int keys[] = {1021, 1305, 1533, 1400};
    const size_t n = sizeof catalogue / sizeof catalogue[0];

    puts("Library catalogue search comparison");
    for (size_t i = 0; i < sizeof keys / sizeof keys[0]; ++i) {
        size_t linear_count, binary_count;
        long linear_pos = linear_search(catalogue, n, keys[i], &linear_count);
        long binary_pos = binary_search(catalogue, n, keys[i], &binary_count);
        printf("Book %d: linear index=%ld (%zu comparisons), binary index=%ld (%zu comparisons)\n",
               keys[i], linear_pos, linear_count, binary_pos, binary_count);
    }
    return 0;
}
