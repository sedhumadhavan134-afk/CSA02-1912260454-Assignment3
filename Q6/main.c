#include <stdio.h>
#include <string.h>

#define MAX_NAMES 100
#define NAME_LEN 40

static void insertion_sort_names(char names[][NAME_LEN], int n,
                                 long *comparisons, long *character_copies) {
    *comparisons = 0;
    *character_copies = 0;
    for (int i = 1; i < n; ++i) {
        char key[NAME_LEN];
        strcpy(key, names[i]);
        *character_copies += (long)strlen(key) + 1;
        int j = i - 1;
        while (j >= 0) {
            ++*comparisons;
            if (strcmp(names[j], key) <= 0) break;
            strcpy(names[j + 1], names[j]);
            *character_copies += (long)strlen(names[j]) + 1;
            --j;
        }
        strcpy(names[j + 1], key);
        *character_copies += (long)strlen(key) + 1;
    }
}
static int binary_search_name(char names[][NAME_LEN], int n,
                              const char *key, long *comparisons) {
    int low = 0, high = n - 1;
    *comparisons = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        ++*comparisons;
        int result = strcmp(names[mid], key);
        if (result == 0) return mid;
        if (result < 0) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
int main(void) {
    char names[MAX_NAMES][NAME_LEN] = {"Sedhu", "Arun", "Meena", "Bala", "Meena"};
    int n = 5;
    long sort_comparisons, copies, search_comparisons;
    insertion_sort_names(names, n, &sort_comparisons, &copies);

    puts("Sorted resident directory:");
    for (int i = 0; i < n; ++i) puts(names[i]);
    printf("Sort comparisons: %ld; character copies: %ld\n",
           sort_comparisons, copies);

    int position = binary_search_name(names, n, "Meena", &search_comparisons);
    printf("Search Meena: index=%d; comparisons=%ld\n",
           position, search_comparisons);

    puts("Duplicate names:");
    for (int i = 1; i < n; ++i)
        if (strcmp(names[i - 1], names[i]) == 0) puts(names[i]);
    return 0;
}
