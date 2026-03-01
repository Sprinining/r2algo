#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

int** dp;
int* data;

int longestPalindromeSubseq(char* s) {
    int len = strlen(s);
    // dp[i][j] 返回 s[i, j] 的最长回文子序列的长度
    dp = malloc(sizeof(*dp) * len);
    data = calloc(len * len, sizeof(*data));
    for (int i = 0; i < len; i++) dp[i] = data + i * len;

    // 上三角矩阵
    for (int i = 0; i < len; i++) dp[i][i] = 1;
    for (int i = 0; i < len - 1; i++) dp[i][i + 1] = s[i] == s[i + 1] ? 2 : 1;

    for (int k = 2; k < len; k++) {
        for (int j = k; j < len; j++) {
            int i = j - k;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                // dp[i + 1][j - 1] 也被包含在两种情况之中了
                dp[i][j] = mmax(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[0][len - 1];
}