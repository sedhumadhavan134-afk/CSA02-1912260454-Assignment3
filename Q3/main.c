#include <stdio.h>
#include <stddef.h>

/* Merge two descending lists. On equal marks, take from the first list
   so the merge is stable with respect to the input-list order. */
static size_t merge_descending(const int a[], size_t na, const int b[], size_t nb,
                               int out[], size_t *comparisons) {
    size_t i = 0, j = 0, k = 0;
    *comparisons = 0;
    while (i < na && j < nb) {
        ++*comparisons;
        if (a[i] >= b[j]) out[k++] = a[i++];
        else out[k++] = b[j++];
    }
    while (i < na) out[k++] = a[i++];
    while (j < nb) out[k++] = b[j++];
    return k;
}
int main(void) {
    const int department_a[] = {98, 91, 85, 72};
    const int department_b[] = {95, 91, 80};
    int merged[7];
    size_t comparisons;
    size_t n = merge_descending(department_a, 4, department_b, 3,
                                merged, &comparisons);
    printf("Combined merit list: ");
    for (size_t i = 0; i < n; ++i) printf("%d ", merged[i]);
    printf("\nComparisons: %zu\n", comparisons);

    /* Boundary test: one input list is empty. */
    const int single[] = {77};
    int boundary[1];
    n = merge_descending(NULL, 0, single, 1, boundary, &comparisons);
    printf("Empty-list test: %d (comparisons=%zu)\n", boundary[0], comparisons);
    return 0;
}
