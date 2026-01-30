#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 记忆化搜索（自顶向下、递归）
int* dp;

int func(int n) {
    if (dp[n] != -1) return dp[n];
    if (n < 2) {
        dp[n] = n;
    } else {
        // 从原问题出发，递归向下求解
        dp[n] = func(n - 1) + func(n - 2);
    }
    return dp[n];
}

int fib(int n) {
    // 初始化为 -1
    dp = (int*)malloc(sizeof(int) * 32);
    memset(dp, -1, sizeof(int) * 32);
    return func(n);
}