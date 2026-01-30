#include <stdio.h>

// 自底向上（迭代）
int fib(int n) {
    if (n < 2) return n;

    int dp[32];
    // 从最简单的子问题开始，算到原问题
    dp[0] = 0;
    dp[1] = 1;

    int k = 2;
    while (k <= n) {
        dp[k] = dp[k - 1] + dp[k - 2];
        k++;
    }
    return dp[n];
}