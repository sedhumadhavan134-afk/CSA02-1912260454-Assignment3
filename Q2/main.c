#include <stdio.h>
#include <string.h>

typedef struct { long comparisons; long moves; } Stats;

static void bubble_sort(int a[], int n, Stats *s) {
    for (int end = n - 1; end > 0; --end) {
        int changed = 0;
        for (int j = 0; j < end; ++j) {
            ++s->comparisons;
            if (a[j] > a[j + 1]) {
                int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
                s->moves += 3; changed = 1;
            }
        }
        if (!changed) break;
    }
}
static void selection_sort(int a[], int n, Stats *s) {
    for (int i = 0; i < n - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < n; ++j) {
            ++s->comparisons;
            if (a[j] < a[min]) min = j;
        }
        if (min != i) {
            int t = a[i]; a[i] = a[min]; a[min] = t;
            s->moves += 3;
        }
    }
}
static void insertion_sort(int a[], int n, Stats *s) {
    for (int i = 1; i < n; ++i) {
        int key = a[i], j = i - 1;
        while (j >= 0) {
            ++s->comparisons;
            if (a[j] <= key) break;
            a[j + 1] = a[j]; ++s->moves; --j;
        }
        a[j + 1] = key; ++s->moves;
    }
}
static void run_sort(const char *name, const int source[], int n,
                     void (*sort_fn)(int *, int, Stats *)) {
    int a[32];
    memcpy(a, source, (size_t)n * sizeof a[0]);
    Stats s = {0, 0};
    sort_fn(a, n, &s);
    printf("%-10s comparisons=%ld moves=%ld result:", name, s.comparisons, s.moves);
    for (int i = 0; i < n; ++i) printf(" %d", a[i]);
    putchar('\n');
}
int main(void) {
    const int sorted[] = {1,2,3,4,5,6};
    const int nearly[] = {1,2,4,3,5,6};
    const int reverse[] = {6,5,4,3,2,1};
    const int random[] = {4,1,6,2,5,3};
    const int *inputs[] = {sorted, nearly, reverse, random};
    const char *labels[] = {"sorted", "nearly sorted", "reverse", "mixed"};
    for (int k = 0; k < 4; ++k) {
        printf("\n%s input\n", labels[k]);
        run_sort("Bubble", inputs[k], 6, bubble_sort);
        run_sort("Selection", inputs[k], 6, selection_sort);
        run_sort("Insertion", inputs[k], 6, insertion_sort);
    }
    return 0;
}
