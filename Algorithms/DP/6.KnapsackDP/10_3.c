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

    // O(m * t)
    for (int i = 1; i < rows; ++i) {
        int cost = choice[i - 1][0];
        int val = choice[i - 1][1];
        for (int j = 0; j < cols; ++j) {
            // 当前物品一个都不要
            dp[i][j] = dp[i - 1][j];
            // 当前物品再要一个
            // 看起来好像没枚举 k，但实际上隐式地把所有 k 情况都考虑进去了
            if (cost <= j) dp[i][j] = mmax(dp[i][j], dp[i][j - cost] + val);
        }
    }

    printf("%lld", dp[rows - 1][cols - 1]);
}
/*
    二维完全背包，到底什么时候可以从 cost 开始遍历？
    只有 1 种情况 可以从 cost 开始：
        当前行 cost 之前都已经满足 dp[i][j] = dp[i - 1][j]，也就是说已经被初始化好了
    最好还是从 0 开始
*/