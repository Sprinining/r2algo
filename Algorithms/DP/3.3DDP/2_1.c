#include <stdlib.h>
#define MOD 1000000007

int *p, *g;
int len;

// 从 i 号工作开始，还剩 n 个人，还需完成的最小利润 m 的情况下的计划数
int dfs(int i, int n, int m) {
    // 工作用尽，判断利润是否达标
    if (i == len) return m > 0 ? 0 : 1;
    // 要当前工作
    int p1 = dfs(i + 1, n, m);
    // 不要当前工作
    int p2 = 0;
    if (n >= g[i]) p2 = dfs(i + 1, n - g[i], m - p[i]);
    return ((long long)p1 + p2) % MOD;
}

int profitableSchemes(int n, int minProfit, int* group, int groupSize, int* profit,
                      int profitSize) {
    p = profit;
    g = group;
    len = groupSize;
    return dfs(0, n, minProfit);
}