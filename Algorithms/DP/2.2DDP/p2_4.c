#include <stdlib.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

int longestCommonSubsequence(char* text1, char* text2) {
    int rows = strlen(text1) + 1;
    int columns = strlen(text2) + 1;
    // 多一行一列，避免特殊情况的讨论
    int** dp = malloc(sizeof(*dp) * rows);
    // 第一行第一列都为 0
    int* data = calloc(rows * columns, sizeof(*data));
    for (int i = 0; i < rows; i++) dp[i] = data + i * columns;

    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < columns; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                // 已经包含了 dp[i - 1][j - 1]
                dp[i][j] = mmax(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[rows - 1][columns - 1];
}