#include <stdbool.h>
#include <string.h>

#define MOD 1000000007
#define MAXL 23
#define MAXS 401

typedef long long ll;

int min, max;
char* num;
int len;
int I, J, K;
int dp[MAXL][MAXS][2];

// num 从高位往地位，也就是从左往右，从 idx 下标开始进行数字选择
// 前边的数位已经确定，且各位数字之和是 sum
// free 为 1 说明前面数位已经导致当前拼凑的数字最终一定比 num 小，后续的可以随便选
// free 为 0 说明前面的数位与 num 的完全一致
// 返回 [0, num] 上数位和在 [min, max] 的数字总个数（结果取余）
int dfs(int idx, int sum, int free) {
    // 数位和越界了
    if (sum > max) return 0;
    // 就算后面所有位都选 9，数位和也小于 min
    if (sum + (len - idx) * 9 < min) return 0;
    if (idx == len) return 1;

    if (dp[idx][sum][free] != -1) return dp[idx][sum][free];

    int res = 0;
    int cur = num[idx] - '0';
    if (free == 1) {
        // p1: 当前位可以自由选择
        for (int i = 0; i <= 9; ++i) res = ((ll)res + dfs(idx + 1, sum + i, true)) % MOD;
    } else {
        // p2: 当前位不能随便选
        // 当前位选 [0, cur) 后续位置就能随便选
        for (int i = 0; i < cur; ++i) res = ((ll)res + dfs(idx + 1, sum + i, true)) % MOD;
        // 当前位置也选 cur，下个位置就不能随便选
        res = ((ll)res + dfs(idx + 1, sum + cur, false)) % MOD;
    }
    return dp[idx][sum][free] = res;
}

int digit_sum(char* s) {
    int n = strlen(s);
    int sum = 0;
    for (int i = 0; i < n; ++i) sum += s[i] - '0';
    return sum;
}

int count(char* num1, char* num2, int min_sum, int max_sum) {
    min = min_sum;
    max = max_sum;

    num = num2;
    len = strlen(num);
    memset(dp, -1, sizeof(dp));
    int big = dfs(0, 0, false);

    num = num1;
    len = strlen(num);
    memset(dp, -1, sizeof(dp));
    int small = dfs(0, 0, false);

    // 如果 num1 的数位和在范围内，那么就要加上在 big-small 中多减掉的那一次
    int num1_sum = digit_sum(num1);
    int extra = (num1_sum >= min && num1_sum <= max) ? 1 : 0;
    return (big - small + extra + MOD) % MOD;
}
