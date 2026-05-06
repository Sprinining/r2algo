#include <stdbool.h>
#include <stdlib.h>

int n, m;
// dp 只需要记录 stat 一个变量就行
// stat 就能决定结果，sum 可以根据 stat 计算得到
int* dp;

// 用一个整数的二进制位，替代数组记录每个数字是否被选取
// 把复杂状态变成普通整数下标，支持记忆化、省内存、免手动回溯
bool dfs(int stat, int sum) {
    if (dp[stat] != 0) return dp[stat] == 1;
    bool res = false;
    for (int i = 1; i <= n; ++i) {
        if ((stat >> i) & 1) continue;
        if (sum + i >= m || !dfs(stat | (1 << i), sum + i)) {
            res = true;
            break;
        }
    }
    dp[stat] = res ? 1 : -1;
    return res;
}

bool canIWin(int maxChoosableInteger, int desiredTotal) {
    n = maxChoosableInteger;
    m = desiredTotal;
    if (n * (n + 1) / 2 < m) return false;
    if (m == 0) return true;
    // 0：未设置，1：赢，-1：输
    dp = calloc(1 << (n + 1), sizeof(*dp));
    return dfs(0, 0);
}
