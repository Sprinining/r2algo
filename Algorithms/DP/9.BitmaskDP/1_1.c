#include <stdbool.h>
#include <stdlib.h>

int n, m;
// status[i] = 数字 i 是否已经被挑选过
bool* status;

// 在目前累加和为 sum，挑选状况为 status 的情况下一号玩家是否必胜
bool dfs(int sum) {
    for (int i = 1; i <= n; ++i) {
        if (status[i]) continue;
        status[i] = true;
        if (sum + i >= m || !dfs(sum + i)) {
            // return 只是跳出当前 dfs，一定要撤销修改
            status[i] = false;
            return true;
        }
        status[i] = false;
    }
    return false;
}

bool canIWin(int maxChoosableInteger, int desiredTotal) {
    n = maxChoosableInteger;
    m = desiredTotal;
    int total = n * (n + 1) / 2;
    if (total < m) return false;
    if (m == 0) return true;
    // 初始化为 false
    status = calloc(n + 1, sizeof(*status));
    return dfs(0);
}
