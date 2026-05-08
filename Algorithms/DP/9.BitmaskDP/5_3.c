#include <string.h>

#define MOD 1000000007
#define MAXN 10
#define HAT_SIZE 41

typedef long long ll;

// who[h]：用 bitmask 表示“哪些人喜欢这个帽子”
int who[HAT_SIZE];
int n;
int dp[1 << MAXN][HAT_SIZE];

// stat：1 表示这个人还没帽子
// cur：当前帽子编号
int dfs(int stat, int cur) {
    if (stat == 0) return 1;
    if (cur > 40) return 0;
    if (dp[stat][cur] != -1) return dp[stat][cur];
    // 1. 不用当前帽子
    int res = dfs(stat, cur + 1);
    // 2. 用当前帽子分配给某个人
    int people = who[cur];
    while (people) {
        // Kernighan 提取最低位1
        int rightOne = people & -people;
        // 如果这个人还没被分配帽子
        if (stat & rightOne) res = (res + dfs(stat ^ rightOne, cur + 1)) % MOD;
        // 删除这个1
        people ^= rightOne;
    }

    return dp[stat][cur] = res;
}

int numberWays(int** hats, int hatsSize, int* hatsColSize) {
    n = hatsSize;
    memset(who, 0, sizeof(who));
    // 建图：帽子 -> 人（bitmask）
    for (int p = 0; p < n; p++) {
        for (int j = 0; j < hatsColSize[p]; j++) {
            int h = hats[p][j];
            who[h] |= (1 << p);
        }
    }
    memset(dp, -1, sizeof(dp));
    return dfs((1 << n) - 1, 1);
}
