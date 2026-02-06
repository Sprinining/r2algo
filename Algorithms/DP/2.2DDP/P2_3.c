#include <stdlib.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

int longestCommonSubsequence(char* text1, char* text2) {
    int rows = strlen(text1);
    int columns = strlen(text2);
    int** dp = (int**)malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++) {
        dp[i] = (int*)malloc(sizeof(int) * columns);
    }

    // 第一行
    dp[0][0] = (text1[0] == text2[0]) ? 1 : 0;
    for (int j = 1; j < columns; j++) {
        dp[0][j] = (text1[0] == text2[j]) ? 1 : dp[0][j - 1];
    }

    for (int i = 1; i < rows; i++) {
        // 第一列
        dp[i][0] = (text1[i] == text2[0]) ? 1 : dp[i - 1][0];
        for (int j = 1; j < columns; j++) {
            int p1 = dp[i - 1][j - 1];
            int p2 = dp[i - 1][j];
            int p3 = dp[i][j - 1];
            int p4 = text1[i] == text2[j] ? dp[i - 1][j - 1] + 1 : 0;
            dp[i][j] = mmax(mmax(p1, p2), mmax(p3, p4));
        }
    }

    return dp[rows - 1][columns - 1];
}