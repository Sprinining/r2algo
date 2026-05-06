#include <stdbool.h>
#include <stdlib.h>

int edge;
int* dp;
int n;
int* nums;

// stat 从最低位到高位对应下标 0～n-1 的木棍，0 表示没被选取过
// cur 是当前这条边已经拼出来的长度
// left 是正方形没处理完的边数
bool dfs(int stat, int cur, int left) {
    if (left == 0) return true;
    // dp 只有一维，因为 stat 能唯一确定出 cur 和 left
    if (dp[stat] != 0) return dp[stat] == 1;
    bool res = false;
    for (int i = 0; i < n; ++i) {
        if ((stat >> i) & 1) continue;
        if (cur + nums[i] > edge) continue;
        if (cur + nums[i] == edge) res = res || dfs(stat | (1 << i), 0, left - 1);
        if (cur + nums[i] < edge) res = res || dfs(stat | (1 << i), cur + nums[i], left);
    }
    dp[stat] = res ? 1 : -1;
    return res;
}

bool makesquare(int* matchsticks, int matchsticksSize) {
    nums = matchsticks;
    n = matchsticksSize;
    int sum = 0;
    for (int i = 0; i < n; ++i) sum += matchsticks[i];
    edge = sum / 4;
    if (sum % 4 != 0) return false;
    // 0：没处理过，1：成功，-1：失败
    dp = calloc(1 << n, sizeof(*dp));
    return dfs(0, 0, 4);
}
