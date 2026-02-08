#include <stdio.h>
#include <stdlib.h>

int main() {
    int MOD = 1000000007;
    int m, n;
    scanf("%d %d", &n, &m);

    // m + 1 行，n + 1 列
    int dp[51][51];

    // 第一列
    for (int i = 0; i <= m; i++) dp[i][0] = 1;
    // 第一行
    for (int j = 1; j <= n; j++) dp[0][j] = 0;
    long long res;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            res = 0;
            for (int k = 0; k < j; k++) {
                res = (res +
                       ((long long)dp[i - 1][k] * dp[i - 1][j - 1 - k]) % MOD) %
                      MOD;
            }
            dp[i][j] = res;
        }
    }

    printf("%d", dp[m][n]);
    return 0;
}