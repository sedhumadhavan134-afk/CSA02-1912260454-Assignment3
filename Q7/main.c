#include <stdio.h>

#define MAX_CANDIDATES 12

typedef struct {
    int candidate_id;
    int votes;
} CandidateResult;

static void sort_results(CandidateResult results[], int count) {
    for (int i = 1; i < count; ++i) {
        CandidateResult key = results[i];
        int j = i - 1;
        while (j >= 0 && results[j].votes < key.votes) {
            results[j + 1] = results[j];
            --j;
        }
        results[j + 1] = key;
    }
}

int main(void) {
    const int candidate_count = 4;
    const int ballots[] = {1, 2, 2, 3, 0, 5, -1, 4, 4, 2, 3, 1, 4, 4};
    const int ballot_count = (int)(sizeof ballots / sizeof ballots[0]);
    int vote_count[MAX_CANDIDATES + 1] = {0};
    int valid = 0, invalid = 0;

    if (candidate_count < 1 || candidate_count > MAX_CANDIDATES) {
        puts("Invalid candidate count.");
        return 1;
    }
    for (int i = 0; i < ballot_count; ++i) {
        if (ballots[i] < 1 || ballots[i] > candidate_count) ++invalid;
        else { ++vote_count[ballots[i]]; ++valid; }
    }

    CandidateResult results[MAX_CANDIDATES];
    for (int i = 0; i < candidate_count; ++i) {
        results[i].candidate_id = i + 1;
        results[i].votes = vote_count[i + 1];
    }
    sort_results(results, candidate_count);

    printf("Valid votes: %d\nInvalid votes: %d\n", valid, invalid);
    puts("Results (highest votes first):");
    for (int i = 0; i < candidate_count; ++i)
        printf("Candidate %d: %d votes\n",
               results[i].candidate_id, results[i].votes);

    if (valid == 0) {
        puts("No valid votes; no winner.");
        return 0;
    }
    int tie = 0;
    for (int i = 1; i < candidate_count; ++i)
        if (results[i].votes == results[0].votes) tie = 1;
    if (tie) printf("Tie for first place: %d votes each.\n", results[0].votes);
    else printf("Winner: Candidate %d with %d votes.\n",
                results[0].candidate_id, results[0].votes);
    return 0;
}
