#include <stdlib.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

int** dp;

// 返回 s1[0...i] s2[0...j] 的最长公共子序列
int func(char* s1, char* s2, int i, int j) {
    if (i < 0 || j < 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    // 四种情况不重不漏
    // 最长公共子序列并没有包含两个末尾字符
    int p1 = func(s1, s2, i - 1, j - 1);
    // 包含了其中一个
    int p2 = func(s1, s2, i - 1, j);
    int p3 = func(s1, s2, i, j - 1);
    // 两个都包含了
    int p4 = s1[i] == s2[j] ? p1 + 1 : 0;
    dp[i][j] = mmax(mmax(p1, p2), mmax(p3, p4));
    return dp[i][j];
}

int longestCommonSubsequence(char* text1, char* text2) {
    int rows = strlen(text1);
    int columns = strlen(text2);
    dp = (int**)malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++) {
        dp[i] = (int*)malloc(sizeof(int) * columns);
        memset(dp[i], -1, sizeof(int) * columns);
    }
    return func(text1, text2, rows - 1, columns - 1);
}