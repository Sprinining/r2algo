#include <stdbool.h>
#include <string.h>

#define MAXV 1000
#define MAXL 50
#define MAXN 10

int val[MAXL + 1];
int val_cnt;
int sz[MAXL + 1];
int n;
int* need;
// 记录每种 stat 所需要的数值总个数
int total[1 << MAXN];
int dp[MAXL][1 << MAXN];

// 去掉没出现的数字，记录出现的数字和次数
void filter(int* nums, int numsSize) {
    int cnts[MAXV + 1];
    memset(cnts, 0, sizeof(cnts));
    for (int i = 0; i < numsSize; ++i) ++cnts[nums[i]];
    val_cnt = 0;
    for (int i = 1; i <= MAXV; ++i) {
        if (cnts[i] == 0) continue;
        val[val_cnt] = i;
        sz[val_cnt++] = cnts[i];
    }
}

void generateTotal() {
    memset(total, 0, sizeof(total));
    int stat = (1 << MAXN) - 1;
    // **便利 stat 的所有非空子集
    for (int s = stat; s > 0; s = (s - 1) & stat)
        // 看看 s 里到底哪些人需要数字，累计总需求
        for (int i = 0; i < n; ++i)
            if (((s >> i) & 1) == 1) total[s] += need[i];
}

// val[cur, val_cnt) 能否满足订单状态 stat
// stat 从最低位到高位对应每个人，为 1 说明没得到满足
bool dfs(int cur, int stat) {
    if (stat == 0) return true;
    if (cur >= val_cnt) return false;
    if (dp[cur][stat] != -1) return dp[cur][stat];
    // p1: 当其的值谁也不给
    if (dfs(cur + 1, stat)) return dp[cur][stat] = true;
    // p2: 尝试把当前的值满足一部分人
    int num = val[cur];
    int cnt = sz[cur];
    // **便利 stat 的所有非空子集
    for (int s = stat; s > 0; s = (s - 1) & stat) {
        // cnt 个 num 满足不了 s
        if (cnt < total[s]) continue;
        // 能满足
        if (dfs(cur + 1, stat ^ s)) return dp[cur][stat] = true;
    }
    return dp[cur][stat] = false;
}

bool canDistribute(int* nums, int numsSize, int* quantity, int quantitySize) {
    filter(nums, numsSize);
    need = quantity;
    n = quantitySize;

    memset(dp, -1, sizeof(dp));
    generateTotal();
    return dfs(0, (1 << n) - 1);
}
