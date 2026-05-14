#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 9

int num;

// dp[len][pre][free]
// len: 还有多少位没有确定
// pre: 上一位填的数字，10 表示之前还没有填过数字
// free:
//      0 -> 当前前缀与 num 完全一致，后续不能超过 num
//      1 -> 当前前缀已经比 num 小了，后续随便填
// 实际上只有 free == 1 时才是真正独立子问题。
// 但由于 free == 0 的状态只会沿唯一一条路径递归，
// 所以这里直接一起记忆化也不会出错。
int dp[MAXL + 1][11][2];

int dfs(int len, int offset, int pre, int free) {
    if (len == 0) return 1;
    if (dp[len][pre][free] != -1) return dp[len][pre][free];

    int cur = (num / offset) % 10;
    int res = 0;
    // p1：之前已经比 num 小
    if (free == 1) {
        // 之前还没填过数字
        if (pre == 10) {
            // 当前位继续不填
            res += dfs(len - 1, offset / 10, 10, 1);
            // 当前位作为数字开头，首位不能为 0
            for (int i = 1; i <= 9; ++i) res += dfs(len - 1, offset / 10, i, 1);
        } else {
            // 已经填过数字，后续可以随便填
            for (int i = 0; i <= 9; ++i) {
                if (abs(i - pre) < 2) continue;
                res += dfs(len - 1, offset / 10, i, 1);
            }
        }
    } else {
        // p2：之前前缀与 num 相同
        if (pre == 10) {
            res += dfs(len - 1, offset / 10, 10, 1);
            // 当前位填比 cur 小的数字，后面也自由了
            for (int i = 1; i < cur; ++i) res += dfs(len - 1, offset / 10, i, 1);
            // 当前位填 cur，继续保持与 num 相同
            res += dfs(len - 1, offset / 10, cur, 0);
        } else {
            for (int i = 0; i <= 9; ++i) {
                if (abs(i - pre) < 2) continue;
                if (i < cur) {
                    res += dfs(len - 1, offset / 10, i, 1);
                } else if (i == cur) {
                    res += dfs(len - 1, offset / 10, i, 0);
                }
            }
        }
    }

    return dp[len][pre][free] = res;
}

// 返回 [0, x] 中 Windy 数个数
int windyFromZero(int x) {
    // 0 本身视为 Windy 数
    if (x == 0) return 1;

    num = x;
    int len = 1, offset = 1, temp = x / 10;
    while (temp > 0) {
        ++len;
        offset *= 10;
        temp /= 10;
    }

    memset(dp, -1, sizeof(dp));
    return dfs(len, offset, 10, 0);
}

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    // [0, b] - [0, a-1]
    printf("%d\n", windyFromZero(b) - windyFromZero(a - 1));
    return 0;
}
