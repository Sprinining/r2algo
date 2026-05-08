#include <stdio.h>
#include <string.h>

#define MAXN 20
#define INF 0x3f3f3f3f
#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int n;
int dis[MAXN][MAXN];
int dp[1 << MAXN][MAXN];

// stat 从最低位到高位 0～n-1 对应 n 个村庄，0 表示访问过了，1 表示待访问
int dfs(int stat, int cur) {
    if (stat == 0) return dis[cur][0];
    if (dp[stat][cur] != INF) return dp[stat][cur];
    int res = INF;
    for (int i = 0; i < n; ++i) {
        if (((stat >> i) & 1) == 0) continue;
        res = MMIN(res, dis[cur][i] + dfs(stat ^ (1 << i), i));
    }
    dp[stat][cur] = res;
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) scanf("%d", &dis[i][j]);

    memset(dp, 0x3f, sizeof(dp));
    // 初始状态 1...1 1 1 0
    printf("%d\n", dfs((1 << n) - 2, 0));
}
