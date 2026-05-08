#include <string.h>

#define MOD 1000000007
#define MAXN 10
#define HAT_SIZE 41

typedef long long ll;

// who[i][j] 想要 i 号帽子
int who[HAT_SIZE][MAXN];
// sz[i] 想要 i 号帽子的人数
int sz[HAT_SIZE];
int n;
int dp[1 << MAXN][HAT_SIZE];

// 因为人只有 10 个而帽子有 40 个，状态压缩要压数量少的那一维，否则 2^40 会直接爆炸
// stat 从最低位到高位对应每个人，为 1 说明还没有分配到帽子
// cur 是当前准备分配的帽子序号
int dfs(int stat, int cur) {
    if (stat == 0) return 1;
    if (cur > 40) return 0;
    if (dp[stat][cur] != -1) return dp[stat][cur];
    // 没人要
    int res = dfs(stat, cur + 1);
    // 有人要
    for (int i = 0; i < sz[cur]; ++i) {
        int p = who[cur][i];
        if (((stat >> p) & 1) == 0) continue;
        res = ((ll)res + dfs(stat ^ (1 << p), cur + 1)) % MOD;
    }
    dp[stat][cur] = res;
    return res;
}

int numberWays(int** hats, int hatsSize, int* hatsColSize) {
    n = hatsSize;
    memset(sz, 0, sizeof(sz));
    for (int p = 0; p < n; ++p) {
        for (int j = 0; j < hatsColSize[p]; ++j) {
            int h = hats[p][j];
            who[h][sz[h]++] = p;
        }
    }
    memset(dp, -1, sizeof(dp));
    return dfs((1 << n) - 1, 1);
}
