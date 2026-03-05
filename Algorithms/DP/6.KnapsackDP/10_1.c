#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long mmax(long long a, long long b) { return a > b ? a : b; }

int main() {
    int t, m;
    scanf("%d%d", &t, &m);

    int (*choice)[2] = malloc(sizeof(*choice) * m);
    for (int i = 0; i < m; ++i) scanf("%d%d", &choice[i][0], &choice[i][1]);

    int rows = m + 1;
    int cols = t + 1;
    long long** dp = malloc(sizeof(*dp) * rows);
    long long* data = calloc(rows * cols, sizeof(*data));
    for (int i = 0; i < rows; ++i) dp[i] = data + i * cols;

    for (int i = 1; i < rows; ++i) {
        int cost = choice[i - 1][0];
        int val = choice[i - 1][1];
        for (int j = 1; j < cols; ++j) {
            // 当前物品一个都不要
            dp[i][j] = dp[i - 1][j];
            // 当前物品要 k 个
            for (int k = 1; k * cost <= j; ++k) {
                dp[i][j] = mmax(dp[i][j], dp[i - 1][j - k * cost] + k * val);
            }
        }
    }

    printf("%lld", dp[rows - 1][cols - 1]);
}