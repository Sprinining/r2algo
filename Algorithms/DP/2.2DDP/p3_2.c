#include <stdio.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

int** dp;

// 返回 s[left, right] 的最长回文子序列
int func(char* s, int left, int right) {
    if (dp[left][right] != -1) return dp[left][right];
    if (left > right) {
        dp[left][right] = 0;
    } else if (left == right) {
        dp[left][right] = 1;
    } else {
        // 由 s[left+1, right-1] 得到，与两端字符无关
        int p1 = func(s, left + 1, right - 1);
        // 与其中一端的字符有关
        int p2 = func(s, left + 1, right);
        int p3 = func(s, left, right - 1);
        // 两端相对
        int p4 = s[left] == s[right] ? p1 + 2 : 0;
        dp[left][right] = mmax(mmax(p1, p2), mmax(p3, p4));
    }
    return dp[left][right];
}

int longestPalindromeSubseq(char* s) {
    int len = strlen(s);
    dp = (int**)malloc(sizeof(int*) * len);
    for (int i = 0; i < len; i++) {
        dp[i] = (int*)malloc(sizeof(int) * len);
        memset(dp[i], -1, sizeof(int) * len);
    }
    return func(s, 0, len - 1);
}