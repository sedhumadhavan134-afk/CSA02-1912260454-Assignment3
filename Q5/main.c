#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

static int count_words(const char text[]) {
    int count = 0, inside_word = 0;
    for (size_t i = 0; text[i] != '\0'; ++i) {
        if (isspace((unsigned char)text[i])) inside_word = 0;
        else if (!inside_word) { ++count; inside_word = 1; }
    }
    return count;
}

/* Palindrome check ignores spaces, punctuation and letter case. */
static int is_palindrome(const char text[]) {
    size_t left = 0, right = 0;
    while (text[right] != '\0') ++right;
    if (right == 0) return 1;
    --right;
    while (left < right) {
        while (left < right && !isalpha((unsigned char)text[left])) ++left;
        while (left < right && !isalpha((unsigned char)text[right])) --right;
        if (tolower((unsigned char)text[left]) !=
            tolower((unsigned char)text[right])) return 0;
        ++left;
        if (right > 0) --right;
    }
    return 1;
}
static void to_uppercase(char text[]) {
    for (size_t i = 0; text[i] != '\0'; ++i)
        text[i] = (char)toupper((unsigned char)text[i]);
}
static void reverse_string(char text[]) {
    size_t n = 0;
    while (text[n] != '\0') ++n;
    for (size_t i = 0; i < n / 2; ++i) {
        char temp = text[i];
        text[i] = text[n - 1 - i];
        text[n - 1 - i] = temp;
    }
}
int main(void) {
    char message[] = " Meet at the library at 5 PM ";
    char sample[] = "C programming";
    printf("Word count: %d\n", count_words(message));
    printf("Palindrome test (Madam, I'm Adam): %s\n",
           is_palindrome("Madam, I'm Adam") ? "Yes" : "No");
    printf("Palindrome test (Hello): %s\n",
           is_palindrome("Hello") ? "Yes" : "No");
    to_uppercase(sample);
    printf("Uppercase: %s\n", sample);
    reverse_string(sample);
    printf("Reversed: %s\n", sample);
    printf("Tab-separated word count: %d\n", count_words("one\ttwo"));
    return 0;
}
