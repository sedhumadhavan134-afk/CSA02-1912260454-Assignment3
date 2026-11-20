#include <stdio.h>

#define ROWS 3
#define COLS 4

static void analyse_rainfall(const double rain[ROWS][COLS]) {
    double district_total[ROWS] = {0};
    double month_total[COLS] = {0};
    double grand_total = 0.0, maximum = -1.0;
    int wettest_row = 0, wettest_col = 0;

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            double value = rain[r][c];
            district_total[r] += value;
            month_total[c] += value;
            grand_total += value;
            if (value > maximum) {
                maximum = value; wettest_row = r; wettest_col = c;
            }
        }
    }

    printf("Average rainfall across all records: %.2f mm\n",
           grand_total / (ROWS * COLS));
    printf("Wettest record: district %d, month %d = %.1f mm\n",
           wettest_row + 1, wettest_col + 1, maximum);
    for (int r = 0; r < ROWS; ++r)
        printf("District %d total: %.1f mm\n", r + 1, district_total[r]);
    for (int c = 0; c < COLS; ++c)
        printf("Month %d average: %.2f mm\n", c + 1, month_total[c] / ROWS);
}

int main(void) {
    const double rainfall[ROWS][COLS] = {
        {80, 45, 60, 90},
        {30, 40, 35, 50},
        {100, 120, 110, 95}
    };
    analyse_rainfall(rainfall);
    printf("Row-major element offset of rainfall[2][3]: %d\n",
           2 * COLS + 3);
    return 0;
}
