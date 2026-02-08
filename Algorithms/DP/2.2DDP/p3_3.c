#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

int** dp;

int longestPalindromeSubseq(char* s) {
    int len = strlen(s);
    // dp[i][j] 返回 s[i, j] 的最长回文子序列
    dp = (int**)malloc(sizeof(int*) * len);
    for (int i = 0; i < len; i++) {
        dp[i] = (int*)calloc(len, sizeof(int));
    }

    // 上三角矩阵
    for (int i = 0; i < len; i++) dp[i][i] = 1;
    for (int i = 0; i < len - 1; i++) dp[i][i + 1] = s[i] == s[i + 1] ? 2 : 1;

    for (int k = 2; k < len; k++) {
        for (int j = k; j < len; j++) {
            int i = j - k;
            int p1 = dp[i + 1][j - 1];
            int p2 = dp[i + 1][j];
            int p3 = dp[i][j - 1];
            int p4 = s[i] == s[j] ? p1 + 2 : 0;
            dp[i][j] = mmax(mmax(p1, p2), mmax(p3, p4));
        }
    }

    return dp[0][len - 1];
}