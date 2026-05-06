#include <stdbool.h>
#include <stdlib.h>

int n, m;

// 在目前累加和为 sum，挑选状况为 stat 的情况下一号玩家是否必胜
// stat 从低 1 位到高位对应 1～n，最低位弃用
bool dfs(int stat, int sum) {
    for (int i = 1; i <= n; ++i) {
        if ((stat >> i) & 1) continue;
        if (sum + i >= m || !dfs(stat | (1 << i), sum + i)) return true;
    }
    return false;
}

bool canIWin(int maxChoosableInteger, int desiredTotal) {
    n = maxChoosableInteger;
    m = desiredTotal;
    int total = n * (n + 1) / 2;
    if (total < m) return false;
    if (m == 0) return true;
    return dfs(0, 0);
}
