#include <stdio.h>
#include <stdlib.h>

int MOD = 1000000007;
int m, n;
int** dp;
int* data;

int func(int n, int m) {
    if (dp[n][m] != -1) return dp[n][m];
    if (n == 0) return 1;
    if (m == 0) return 0;
    // 根节点用掉了一个
    // 剩下 n - 1 个节点，分给左右子树
    int res = 0;
    for (int i = 0; i < n; i++) {
        res = ((long long)res + ((long long)func(i, m - 1) * func(n - 1 - i, m - 1) % MOD)) % MOD;
    }
    dp[n][m] = res;
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    int rows = n + 1;
    int columns = m + 1;
    dp = malloc(sizeof(*dp) * rows);
    data = malloc(sizeof(*data) * rows * columns);
    for (int i = 0; i < rows; i++) {
        dp[i] = data + i * columns;
        memset(dp[i], -1, sizeof(*dp[i]) * columns);
    }
    printf("%d", func(n, m));
    return 0;
}