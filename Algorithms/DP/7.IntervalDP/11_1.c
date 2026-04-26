#include <stdio.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int k;
// dp[l][r]：区间 [l, r] 合并到“不能再合并”为止的最小代价
int **dp;
int *data;
int *preSums;

// 区间 [l, r] 的总石头数
int rangeSum(int l, int r) { return preSums[r + 1] - preSums[l]; }

int dfs(int *stones, int l, int r) {
    // 只有一堆，无法再合并，不产生代价
    if (l == r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    int res = 0x7fffffff;
    // 枚举分割点
    // 注意不是随便切，而是每次跳 k-1
    // ——因为每次合并会减少 k-1 堆，这样才能保证子问题结构合法
    for (int m = l; m < r; m += (k - 1)) {
        int left = dfs(stones, l, m);
        int right = dfs(stones, m + 1, r);
        if (left == 0x7fffffff || right == 0x7fffffff) continue;
        res = MMIN(res, left + right);
    }

    // 如果 [l, r] 上注定能合并成一份，那么要算上最后一次的合并代价
    if ((r - l) % (k - 1) == 0) res += rangeSum(l, r);
    dp[l][r] = res;
    return res;
}
int mergeStones(int *stones, int stonesSize, int _k) {
    if ((stonesSize - 1) % (_k - 1) != 0) return -1;
    k = _k;
    int n = stonesSize;
    dp = malloc(sizeof(*dp) * n);
    data = malloc(sizeof(*data) * n * n);
    memset(data, -1, sizeof(*data) * n * n);
    for (int i = 0; i < n; ++i) dp[i] = data + i * n;

    // 计算前缀和
    preSums = calloc(n + 1, sizeof(*preSums));
    for (int i = 0; i < n; ++i) {
        preSums[i + 1] = preSums[i] + stones[i];
    }

    return dfs(stones, 0, n - 1);
}
