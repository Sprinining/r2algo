#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int t, m;
int** choice;
int* data;

int** dp;
int* data2;

int mmax(int a, int b) { return a > b ? a : b; }

// 后缀式 0/1 背包记忆化 DP
// 从 cur_idx 开始考虑，在剩余时间 time_left 的情况下，所能获得的最大价值
// dp[i][j] = 在物品 i ~ m-1 中选，总时间 ≤ j 时的最大价值
int func(int cur_idx, int time_left) {
    // 没得选或者背包满了
    if (cur_idx == m || time_left == 0) return 0;

    if (dp[cur_idx][time_left] != -1) return dp[cur_idx][time_left];

    // 不选 choice[cur_idx]
    int p1 = func(cur_idx + 1, time_left);
    // 选 choice[cur_idx]，前提不超过背包容量
    int p2 = 0;
    if (time_left >= choice[cur_idx][0])
        p2 = func(cur_idx + 1, time_left - choice[cur_idx][0]) + choice[cur_idx][1];

    dp[cur_idx][time_left] = mmax(p1, p2);
    return dp[cur_idx][time_left];
}

int main() {
    scanf("%d %d", &t, &m);
    choice = malloc(sizeof(*choice) * m);
    data = malloc(sizeof(*data) * m * 2);
    for (int i = 0; i < m; i++) choice[i] = data + i * 2;
    for (int i = 0; i < m; i++) scanf("%d %d", &choice[i][0], &choice[i][1]);

    dp = malloc(sizeof(*dp) * m);
    data2 = malloc(sizeof(*data2) * m * t);
    for (int i = 0; i < m; i++) {
        dp[i] = data2 + i * t;
        memset(dp[i], -1, sizeof(*dp[i]) * t);
    }

    printf("%d", func(0, t));
}