#include <stdlib.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

int longestCommonSubsequence(char* text1, char* text2) {
    int rows = strlen(text1);
    int columns = strlen(text2);
    // 多一行一列，避免特殊情况的讨论
    int** dp = (int**)malloc(sizeof(int*) * (rows + 1));
    // 第一行第一列都为 0
    for (int i = 0; i <= rows; i++) {
        dp[i] = (int*)calloc(columns + 1, sizeof(int));
    }

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= columns; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                // 已经包含了 dp[i - 1][j - 1]
                dp[i][j] = mmax(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[rows][columns];
}