#include <stdlib.h>
#include <string.h>

#define IDX(i, j, k) ((i) * (J) * (K) + (j) * (K) + (k))
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int I, J, K;
int* dp;

// 在区间 [l, r] 内消除盒子的最大得分
// 前提：a[l] 左边有 k 个与 a[l] 相同的盒子
int dfs(int* a, int l, int r, int k) {
    if (l > r) return 0;
    if (dp[IDX(l, r, k)] != -1) return dp[IDX(l, r, k)];

    int s = l;
    // 把连续相同的 a[l] 往右合并
    while (s + 1 <= r && a[l] == a[s + 1]) ++s;

    // cnt = 当前可以一起消掉的数量 = 左边带来的 k + 当前连续段长度
    int cnt = k + (s - l + 1);

    // 策略1：直接把这一段消掉
    int res = cnt * cnt + dfs(a, s + 1, r, 0);

    // 策略2：尝试“延迟消除”
    // 在后面找相同颜色，把它们合并起来一起消
    for (int m = s + 2; m <= r; ++m) {
        if (a[l] == a[m] && a[m - 1] != a[m]) {
            int candidate = dfs(a, s + 1, m - 1, 0) + dfs(a, m, r, cnt);
            res = MMAX(res, candidate);
        }
    }

    dp[IDX(l, r, k)] = res;
    return res;
}

int removeBoxes(int* boxes, int boxesSize) {
    I = boxesSize;
    J = I;
    K = I;

    dp = malloc(sizeof(*dp) * I * J * K);
    memset(dp, -1, sizeof(*dp) * I * J * K);

    return dfs(boxes, 0, boxesSize - 1, 0);
}
