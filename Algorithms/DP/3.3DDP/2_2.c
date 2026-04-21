#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

int *p, *g;
int len;
int*** dp;
int** plane;
int* data;

// 从 i 号工作开始，还剩 n 个人，还需完成的最小利润 m 的情况下的计划数
int dfs(int i, int n, int m) {
    if (i == len) return m > 0 ? 0 : 1;
    if (dp[i][n][m] != -1) return dp[i][n][m];
    int p1 = dfs(i + 1, n, m);
    int p2 = 0;
    if (n >= g[i]) {
        // **防止下标越界
        int pNext = m - p[i] >= 0 ? m - p[i] : 0;
        p2 = dfs(i + 1, n - g[i], pNext);
    }

    dp[i][n][m] = ((long long)p1 + p2) % MOD;
    return dp[i][n][m];
}

int profitableSchemes(int n, int minProfit, int* group, int groupSize, int* profit,
                      int profitSize) {
    p = profit;
    g = group;
    len = groupSize;
    int layers = groupSize;
    int rows = n + 1;
    int cols = minProfit + 1;
    dp = malloc(sizeof(*dp) * layers);
    plane = malloc(sizeof(*plane) * layers * rows);
    data = malloc(sizeof(*data) * layers * rows * cols);
    memset(data, -1, sizeof(*data) * layers * rows * cols);
    for (int i = 0; i < layers; ++i) {
        dp[i] = plane + i * rows;
        for (int j = 0; j < rows; ++j) {
            dp[i][j] = data + (i * rows * cols + j * cols);
        }
    }

    return dfs(0, n, minProfit);
}