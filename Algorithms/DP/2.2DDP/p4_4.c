#include <stdio.h>
#include <stdlib.h>

int main() {
    int MOD = 1000000007;
    int m, n;
    scanf("%d %d", &n, &m);

    // m + 1 行，n + 1 列
    int dp[51] = {1, 0};

    for (int i = 1; i <= m; i++) {
        for (int j = n; j >= 1; j--) {
            int res = 0;
            for (int k = 0; k < j; k++)
                res = ((long long)res + ((long long)dp[k] * dp[j - 1 - k]) % MOD) % MOD;
            dp[j] = res;
        }
    }

    printf("%d", dp[n]);
    return 0;
}