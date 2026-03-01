#include <stdlib.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

int longestCommonSubsequence(char* text1, char* text2) {
    int rows = strlen(text1) + 1;
    int columns = strlen(text2) + 1;
    int* dp = calloc(columns, sizeof(*dp));

    for (int i = 1; i < rows; i++) {
        int left_up = dp[0];
        int temp;
        for (int j = 1; j < columns; j++) {
            temp = dp[j];
            if (text1[i - 1] == text2[j - 1]) {
                dp[j] = left_up + 1;
            } else {
                dp[j] = mmax(dp[j], dp[j - 1]);
            }
            left_up = temp;
        }
    }

    return dp[columns - 1];
}