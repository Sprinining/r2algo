#include <stdio.h>
#include <stdlib.h>

int MOD = 1e9 + 7;
int m, n;
int** dp;

long long func(int n, int m) {
    if (dp[n][m] != -1) return dp[n][m];
    if (n == 0) return 1;
    if (m == 0) return 0;
    // 根节点用掉了一个
    // 剩下 n - 1 个节点，分给左右子树
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res = (res + (func(i, m - 1) * func(n - 1 - i, m - 1) % MOD)) % MOD;
    }
    dp[n][m] = (int)res;
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    dp = (int**)malloc(sizeof(int*) * (n + 1));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc(sizeof(int) * (m + 1));
        memset(dp[i], -1, sizeof(int) * (m + 1));
    }
    printf("%d", (int)func(n, m));
    return 0;
}